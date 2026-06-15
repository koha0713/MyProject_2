#pragma once
#include "Component.h"
#include "GameObject.h"
#include "IOManager.h"
#include "Game.h"
#include "Camera.h"
#include <SimpleMath.h>
#include <SoundManager.h>

class CameraRelativeMoverComponent : public Component
{
private:
    Camera* m_Camera;           // カメラへの参照
    float m_MoveSpeed;          // 移動速度
    float m_RotationSpeed;      // 回転速度

    float m_Yaw = 0.0f;         // Playerモデルの横回転角度（ラジアン）

    float m_DashMultiplier = 1.8f;   // ダッシュ時の速度倍率

public:
    CameraRelativeMoverComponent(
        Camera* camera,
        float moveSpeed = 5.0f,
        float rotationSpeed = 3.0f)
        : m_Camera(camera)
        , m_MoveSpeed(moveSpeed)
        , m_RotationSpeed(rotationSpeed)
    {
    }

    void Update() override
    {
        if (!m_pOwner || !m_Camera) return;

        float deltaTime = Game::GetDeltaTime();
        Transform& transform = m_pOwner->GetTransform();
        using namespace DirectX::SimpleMath;

        // -------------------------------
        // カメラ前方・右方向ベクトル（水平のみ）
        // -------------------------------
        Vector3 cameraForward = m_Camera->GetTarget() - m_Camera->GetPosition();
        cameraForward.y = 0;
        if (cameraForward.LengthSquared() > 0.0001f) cameraForward.Normalize();
        else cameraForward = Vector3(0, 0, 1);

        Vector3 cameraRight = cameraForward.Cross(Vector3(0, 1, 0));
        if (cameraRight.LengthSquared() > 0.0001f) cameraRight.Normalize();
        else cameraRight = Vector3(1, 0, 0);

        // -------------------------------
        // 移動入力
        // -------------------------------
        Vector3 moveDir(0, 0, 0);

        if (IO_MANAGER.GetKeyPressKeyBord(VK_W)) moveDir += cameraForward;
        if (IO_MANAGER.GetKeyPressKeyBord(VK_S)) moveDir -= cameraForward;
        if (IO_MANAGER.GetKeyPressKeyBord(VK_A)) moveDir += cameraRight;
        if (IO_MANAGER.GetKeyPressKeyBord(VK_D)) moveDir -= cameraRight;

        if (moveDir.LengthSquared() > 0.0001f)
        {
            moveDir.Normalize();
            Vector3 pos = transform.GetPosition();
            // -------------------------------
            // ダッシュ判定（Shiftキー）
            // -------------------------------
            float speed = m_MoveSpeed;

            if (IO_MANAGER.GetKeyPressKeyBord(VK_SHIFT))
            {
                speed *= m_DashMultiplier;
            }
            else {
            }

            pos += moveDir * speed * deltaTime;
            transform.SetPosition(pos);

            // -------------------------------
            // Playerモデル横回転（yawのみ）
            // -------------------------------
            m_Yaw = atan2f(moveDir.x, moveDir.z);
            Vector3 rot = transform.GetRotation();
            rot.y = m_Yaw;
            transform.SetRotation(rot);
        }

        // -------------------------------
        // Q/Eによる手動回転
        // -------------------------------
        Vector3 rotation = transform.GetRotation();
        if (IO_MANAGER.GetKeyPressKeyBord(VK_Q)) m_Yaw -= m_RotationSpeed * deltaTime;
        if (IO_MANAGER.GetKeyPressKeyBord(VK_E)) m_Yaw += m_RotationSpeed * deltaTime;

        rotation.y = m_Yaw;
        transform.SetRotation(rotation);
    }

    // -------------------------------
    // PlayerモデルのYawを外部から設定可能
    // -------------------------------
    void SetYaw(float yaw) { m_Yaw = yaw; }
    float GetYaw() const { return m_Yaw; }

    void SetMoveSpeed(float speed) { m_MoveSpeed = speed; }
    float GetMoveSpeed() const { return m_MoveSpeed; }

    void SetRotationSpeed(float speed) { m_RotationSpeed = speed; }
    float GetRotationSpeed() const { return m_RotationSpeed; }

    void SetCamera(Camera* camera) { m_Camera = camera; }
    Camera* GetCamera() const { return m_Camera; }
};