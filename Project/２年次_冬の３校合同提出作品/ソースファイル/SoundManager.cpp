#include "SoundManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <Windows.h>
#include <combaseapi.h>

#ifdef _XBOX
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#endif
#ifndef _XBOX
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#endif

//========================================
// Init
//========================================
bool SoundManager::Init()
{
    HRESULT hr;

    if (FAILED(CoInitializeEx(NULL, COINIT_MULTITHREADED)))
        return false;

    if (FAILED(XAudio2Create(&m_pXAudio2, 0)))
    {
        CoUninitialize();
        return false;
    }

    if (FAILED(m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice)))
    {
        m_pXAudio2->Release();
        CoUninitialize();
        return false;
    }

    // サウンドテーブルを読み込み、Voiceプール作成
    for (int i = 0; i < (int)SOUND_LABEL::SOUND_MAX; i++)
    {
        SOUND_LABEL label = (SOUND_LABEL)i;
        const SoundInfo& info = m_soundTable[i];

        if (info.filepath.empty()) continue;

        if (!LoadSound(label))
        {
            std::cerr << "Failed to load sound: " << info.filepath << std::endl;
            continue;
        }

        // SEの場合は Voice プール作成
        if (!info.loop)
        {
            std::vector<IXAudio2SourceVoice*>& pool = m_SEVoicePool[label];
            for (int v = 0; v < SE_MAX_VOICE; v++)
            {
                IXAudio2SourceVoice* pVoice = nullptr;
                hr = m_pXAudio2->CreateSourceVoice(&pVoice, &m_soundCache[label].wfx.Format);
                if (FAILED(hr) || !pVoice)
                {
                    std::cerr << "Failed to create SE Voice for label " << i << std::endl;
                    continue; // pool に追加せず次へ
                }
                pool.push_back(pVoice);
            }

            if (pool.empty())
                std::cerr << "Warning: SE Voice pool empty for label " << i << std::endl;
        }
    }

    return true;
}

//========================================
// Reset
//========================================
void SoundManager::UnInit()
{
    // SE Voice Pool
    for (auto& pair : m_SEVoicePool)
    {
        for (auto* v : pair.second)
        {
            if (v)
            {
                v->Stop(0);
                v->FlushSourceBuffers();
                v->DestroyVoice();
            }
        }
    }
    m_SEVoicePool.clear();

    // BGM Voice
    if (m_currentBGM != SOUND_LABEL::NONE)
    {
        StopBGM();
    }

    // Sound Cache 解放
    m_soundCache.clear();

    if (m_pMasteringVoice) m_pMasteringVoice->DestroyVoice();
    if (m_pXAudio2) m_pXAudio2->Release();

    CoUninitialize();
}

//========================================
// LoadSound（内部キャッシュ）
/* WAVロードしてキャッシュに保持 */
bool SoundManager::LoadSound(SOUND_LABEL label)
{
    SoundData& data = m_soundCache[label];
    if (data.loaded) return true;

    const SoundInfo& info = m_soundTable[(int)label];

    HANDLE hFile = CreateFileA(info.filepath.c_str(), GENERIC_READ, FILE_SHARE_READ,
        NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Failed to open sound file: " << info.filepath << std::endl;
        return false;
    }

    DWORD chunkSize;
    DWORD chunkPos;
    DWORD filetype;

    if (FAILED(FindChunk(hFile, fourccRIFF, chunkSize, chunkPos)))
        return false;
    if (FAILED(ReadChunkData(hFile, &filetype, sizeof(DWORD), chunkPos)))
        return false;
    if (filetype != fourccWAVE) return false;

    if (FAILED(FindChunk(hFile, fourccFMT, chunkSize, chunkPos)))
        return false;
    if (FAILED(ReadChunkData(hFile, &data.wfx, chunkSize, chunkPos)))
        return false;

    if (FAILED(FindChunk(hFile, fourccDATA, chunkSize, chunkPos)))
        return false;

    data.audioData.resize(chunkSize);
    if (FAILED(ReadChunkData(hFile, data.audioData.data(), chunkSize, chunkPos)))
        return false;

    CloseHandle(hFile);

    data.buffer.AudioBytes = chunkSize;
    data.buffer.pAudioData = data.audioData.data();
    data.buffer.Flags = XAUDIO2_END_OF_STREAM;
    data.buffer.LoopCount = info.loop ? XAUDIO2_LOOP_INFINITE : 0;

    data.loaded = true;
    return true;
}

//========================================
// PlayBGM
//========================================
void SoundManager::PlayBGM(SOUND_LABEL label)
{
    if (label == SOUND_LABEL::NONE) return;
    if (!LoadSound(label)) return;

    // すでにBGMが鳴っていたら止める
    StopBGM();

    HRESULT hr = m_pXAudio2->CreateSourceVoice(
        &m_pBGMVoice,
        &m_soundCache[label].wfx.Format
    );
    if (FAILED(hr) || !m_pBGMVoice)
        return;

    m_pBGMVoice->SubmitSourceBuffer(&m_soundCache[label].buffer);
    m_pBGMVoice->SetVolume(m_volumeBGM);
    m_pBGMVoice->Start(0);

    m_currentBGM = label;
}

//========================================
// StopBGM
//========================================
void SoundManager::StopBGM()
{
    if (!m_pBGMVoice)
        return;

    m_pBGMVoice->Stop(0);
    m_pBGMVoice->FlushSourceBuffers();
    m_pBGMVoice->DestroyVoice();
    m_pBGMVoice = nullptr;

    m_currentBGM = SOUND_LABEL::NONE;
}

//========================================
// PlaySE（Voiceプールを使用して多重再生可能）
//========================================
void SoundManager::PlaySE(SOUND_LABEL label)
{
    if (label == SOUND_LABEL::NONE) return;
    if (!LoadSound(label))
    {
        std::cout << "SE:FAILED";
        return; // 読み込み失敗なら再生不可
    }
    IXAudio2SourceVoice* pVoice = GetFreeSEVoice(label);
    if (!pVoice)
    {
        std::cerr << "No free SE Voice for label " << (int)label << std::endl;
        return; // 全部再生中
    }

    XAUDIO2_BUFFER& buffer = m_soundCache[label].buffer;
    HRESULT hr = pVoice->SubmitSourceBuffer(&buffer);
    if (FAILED(hr))
    {
        std::cerr << "Failed to submit buffer for SE label " << (int)label << std::endl;
        return;
    }

    hr = pVoice->Start(0);
    if (FAILED(hr))
        std::cerr << "Failed to start SE Voice for label " << (int)label << std::endl;

    pVoice->SetVolume(m_volumeSE);
}

//========================================
// StopSE
//========================================
void SoundManager::StopSE(SOUND_LABEL label)
{
    if (m_SEVoicePool.find(label) == m_SEVoicePool.end()) return;
    for (auto* v : m_SEVoicePool[label])
    {
        if (v)
        {
            v->Stop(0);
            v->FlushSourceBuffers();
        }
    }
}

//========================================
// ボリューム設定
//========================================
void SoundManager::SetVolumeBGM(float vol)
{
    m_volumeBGM = vol;
    if (m_currentBGM != SOUND_LABEL::NONE)
    {
        m_volumeBGM = vol;
        if (m_pBGMVoice)
            m_pBGMVoice->SetVolume(vol);
    }
}

void SoundManager::SetVolumeSE(float vol)
{
    m_volumeSE = vol;
}

//========================================
// SE用空きVoice取得
//========================================
IXAudio2SourceVoice* SoundManager::GetFreeSEVoice(SOUND_LABEL label)
{
    auto it = m_SEVoicePool.find(label);
    if (it == m_SEVoicePool.end() || it->second.empty()) return nullptr;

    for (auto* v : it->second)
    {
        if (!v) continue;

        XAUDIO2_VOICE_STATE state;
        v->GetState(&state);
        if (state.BuffersQueued == 0)
            return v;
    }

    return nullptr; // 全部埋まっている場合は nullptr
}

//========================================
// WAVユーティリティ
//========================================
HRESULT SoundManager::FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{
    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());

    DWORD dwChunkType;
    DWORD dwChunkDataSize;
    DWORD dwRIFFDataSize = 0;
    DWORD dwFileType;
    DWORD bytesRead = 0;
    DWORD dwOffset = 0;

    while (true)
    {
        DWORD dwRead;
        if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
            return HRESULT_FROM_WIN32(GetLastError());
        if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
            return HRESULT_FROM_WIN32(GetLastError());

        switch (dwChunkType)
        {
        case fourccRIFF:
            dwRIFFDataSize = dwChunkDataSize;
            dwChunkDataSize = 4;
            if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
                return HRESULT_FROM_WIN32(GetLastError());
            break;
        default:
            if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
                return HRESULT_FROM_WIN32(GetLastError());
        }

        dwOffset += sizeof(DWORD) * 2;
        if (dwChunkType == fourcc)
        {
            dwChunkSize = dwChunkDataSize;
            dwChunkDataPosition = dwOffset;
            return S_OK;
        }

        dwOffset += dwChunkDataSize;
        if (bytesRead >= dwRIFFDataSize) return S_FALSE;
    }
    return S_OK;
}

HRESULT SoundManager::ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset)
{
    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());

    DWORD dwRead;
    if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
        return HRESULT_FROM_WIN32(GetLastError());

    return S_OK;
}
