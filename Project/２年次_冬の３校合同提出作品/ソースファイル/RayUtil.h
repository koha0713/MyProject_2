#pragma once
#include <DirectXMath.h>
#include <SimpleMath.h>

bool IntersectRaySphere(
    const DirectX::SimpleMath::Vector3& rayOrigin,
    const DirectX::SimpleMath::Vector3& rayDir,
    const DirectX::SimpleMath::Vector3& sphereCenter,
    float sphereRadius,
    float& outDistance
);
