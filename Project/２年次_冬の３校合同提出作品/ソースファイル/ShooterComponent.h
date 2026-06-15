#pragma once
#include "Component.h"
#include "Camera.h"

class ShooterComponent : public Component
{
private:
    Camera* m_Camera = nullptr;
    int m_Damage = 10;

    // ===============================
    // リロード関連
    // ===============================
    int   m_MaxAmmo = 6;        // マガジン最大弾数
    int   m_CurrentAmmo = 6;    // 現在の弾数

    float m_ReloadTime = 1.5f; // リロードにかかる時間
    float m_ReloadTimer = 0.0f;
    bool  m_IsReloading = false;

public:
    ShooterComponent(Camera* camera, int damage = 10)
        : m_Camera(camera), m_Damage(damage) {}

    void Update() override;

    int GetAmmo() { return m_CurrentAmmo; };

private:
    void StartReload();
};
