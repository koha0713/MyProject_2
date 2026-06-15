#pragma once
#include "GameObject.h"
#include "Component.h"
#include "RhythmManager.h"
#include <Texture2D.h>

class RhythmUIComponent : public Component
{
public:
    void Update()
    {
        // 拍進捗（0.0 ～ 1.0）
        float beat = RHYTHM_MANAGER.GetBeatProgress();

        // 拍終端（1.0）に向かって単調に拡大
        float scale = m_MinScale + (m_MaxScale - m_MinScale) * beat;

        Vector3 newScale = { scale, scale, scale };
        m_pOwner->GetTransform().SetScale(newScale);

        if (RHYTHM_MANAGER.IsPerfectCenter() && RHYTHM_MANAGER.IsEasyMode() == true) {
            SOUND_MANAGER.SetVolumeSE(3.0f);
            SOUND_MANAGER.PlaySE(SOUND_LABEL::SE_RIZM);
            SOUND_MANAGER.SetVolumeSE(1.0f);
        }

    }

private:
    // スケール範囲
    float m_MinScale = 30.0f;
    float m_MaxScale = 80.0f;
};