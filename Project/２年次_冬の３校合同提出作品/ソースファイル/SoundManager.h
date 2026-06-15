#pragma once
#include <xaudio2.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "singleton.h"

// サウンドラベル
enum class SOUND_LABEL
{
    NONE = -1,
    BGM_TITLE,
    BGM_GAME,
    BGM_RESULT,
    SE_SAMPLE000,
    SE_SELECT,
    SE_GUN,
    SE_DAMAGE,
    SE_WALK,
    SE_RUN,
    SE_RIZM,
    SE_RELORD,
    SOUND_MAX
};

// サウンド情報
struct SoundInfo
{
    std::string filepath;
    bool loop;
};

// SoundManager本体
class SoundManager
{
private:
    struct SoundData
    {
        WAVEFORMATEXTENSIBLE wfx{};
        XAUDIO2_BUFFER buffer{};
        std::vector<BYTE> audioData;
        bool loaded = false;
    };

    IXAudio2* m_pXAudio2 = nullptr;
    IXAudio2MasteringVoice* m_pMasteringVoice = nullptr;

    float m_volumeBGM = 1.0f;
    float m_volumeSE = 1.0f;

    SOUND_LABEL m_currentBGM = SOUND_LABEL::NONE;

    // SoundData キャッシュ
    std::unordered_map<SOUND_LABEL, SoundData> m_soundCache;

    // 同時再生可能なSE用のVoiceプール
    std::unordered_map<SOUND_LABEL, std::vector<IXAudio2SourceVoice*>> m_SEVoicePool;
    const int SE_MAX_VOICE = 10; // 同時再生数

    // サウンドテーブル
    SoundInfo m_soundTable[(int)SOUND_LABEL::SOUND_MAX] =
    {
        {"asset/BGM/TITLE.wav", true},  // BGM_SAMPLE000
        {"asset/BGM/GAME.wav", true},  // BGM_GAME
        {"asset/BGM/RESULT.wav", true}, // BGM_RESULT
        {"asset/SE/Kettei.wav", false},  // SE_SAMPLE000
        {"asset/SE/Select.wav", false},  // SE_SELECT
        {"asset/SE/Gun.wav", false},  // SE_GUN
        {"asset/SE/DAMAGE.wav", false},  // SE_DAMAGE
        {"asset/SE/WALK.wav", false},  // SE_WALK
        {"asset/SE/RUN.wav", false},  // SE_RUN
        {"asset/SE/RIZM.wav", false},  // SE_RIZM
        {"asset/SE/RELORD.wav", false}, // SE_RELORD
    };

public:
    // 初期化・解放
    bool Init();
    void UnInit();

    // 再生
    void PlayBGM(SOUND_LABEL label);
    void PlaySE(SOUND_LABEL label);
    void StopBGM();
    void StopSE(SOUND_LABEL label);

    // 音量
    void SetVolumeBGM(float vol);
    void SetVolumeSE(float vol);
    float GetVolumeBGM() const { return m_volumeBGM; }
    float GetVolumeSE() const { return m_volumeSE; }

private:
    bool LoadSound(SOUND_LABEL label);
    IXAudio2SourceVoice* GetFreeSEVoice(SOUND_LABEL label);
    IXAudio2SourceVoice* m_pBGMVoice = nullptr;
    HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
    HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);
};

// 唯一インスタンス取得マクロ
#define SOUND_MANAGER Singleton<SoundManager>::GetInstance()
