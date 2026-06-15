#include "ShooterComponent.h"
#include "IOManager.h"
#include "GameObject.h"
#include "ProjectileComponent.h"
#include "SceneBase.h"
#include <SceneManager.h>
#include <iostream>
#include <RhythmManager.h>
#include "SoundManager.h"
#include <Game.h>

using namespace DirectX::SimpleMath;

void ShooterComponent::Update()
{
    if (!m_pOwner || !m_Camera) return;

    float delta = Game::GetDeltaTime();

    // ===============================
    // リロード中処理
    // ===============================
    if (m_IsReloading)
    {
        m_ReloadTimer += delta;
        if (m_ReloadTimer >= m_ReloadTime)
        {
            m_IsReloading = false;
            m_CurrentAmmo = m_MaxAmmo;
            std::cout << "[Shooter] Reload complete\n";
        }
        return; // リロード中は撃てない
    }

    // ===============================
    // リロード入力
    // ===============================
    if (IO_MANAGER.GetKeyPressKeyBord(VK_R))
    {
        StartReload();
        return;
    }

    // ===============================
    // 弾切れ
    // ===============================
    if (m_CurrentAmmo <= 0)
    {
        StartReload();
        return;
    }

    // ===============================
    // 発射入力
    // ===============================
    if (!IO_MANAGER.GetMouseDown(VK_LBUTTON)) return;

    SceneBase* scene = SCENE_MANAGER.GetCurrentScene();
    if (!scene) return;

    // 弾プールから非アクティブの弾を探す
    auto bullets = scene->FindGameObjectsWithTag("Bullet");
    GameObject* freeBullet = nullptr;
    for (auto* b : bullets)
    {
        if (!b->IsActive())
        {
            freeBullet = b;
            break;
        }
    }

    if (!freeBullet) return;

    // 弾をアクティブ化
    freeBullet->SetActive(true);

    // ===============================
    // リズム判定
    // ===============================
    RhythmJudge judge = RHYTHM_MANAGER.JudgeTiming();
    RHYTHM_MANAGER.OnJudge(judge);

    auto* proj = freeBullet->GetComponent<ProjectileComponent>();
    proj->SetRhythm(judge);

    // 初期位置
    Vector3 pos = m_Camera->GetPosition();
    freeBullet->GetTransform().SetPosition(pos);

    // 発射方向
    Vector3 rayDir = m_Camera->GetTarget() - m_Camera->GetPosition();
    rayDir.Normalize();

    proj->Fire(rayDir, m_Damage);

    // 弾消費
    m_CurrentAmmo--;

    SOUND_MANAGER.PlaySE(SOUND_LABEL::SE_GUN);

    std::cout << "[Shooter] Fire! Ammo: "
        << m_CurrentAmmo << "/" << m_MaxAmmo << "\n";
}

// ===============================
// リロード開始
// ===============================
void ShooterComponent::StartReload()
{
    if (m_IsReloading) return;

    m_IsReloading = true;
    m_ReloadTimer = 0.0f;
    SOUND_MANAGER.PlaySE(SOUND_LABEL::SE_RELORD);

    std::cout << "[Shooter] Reload start\n";
}