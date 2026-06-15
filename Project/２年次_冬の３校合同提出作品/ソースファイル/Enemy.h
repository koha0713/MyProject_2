#pragma once
#include "Component.h"
#include <SimpleMath.h>

class WaveManager; // ‘O•ûéŒ¾

class Enemy : public Component
{
private:
    int m_HP = 0;
    int m_MaxHP = 0;
    bool m_IsDeadNotified = false;
    WaveManager* m_pWaveManager = nullptr;

public:
    void Init() override;
    void Update() override;

    // =====================
    // Wave—p ‰Šú‰»
    // =====================
    void Spawn(const DirectX::SimpleMath::Vector3& pos, int hp, WaveManager* wm);

    // =====================
    // HP
    // =====================
    void Damage(int damage);
    bool IsDead() const { return m_HP <= 0; }

    void SetWaveManager(WaveManager* wm) { m_pWaveManager = wm; }

};
