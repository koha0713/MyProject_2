#include "RayUtil.h"
using namespace DirectX::SimpleMath;

bool IntersectRaySphere(
    const Vector3& rayOrigin,
    const Vector3& rayDir,
    const Vector3& sphereCenter,
    float sphereRadius,
    float& outDistance)
{
    Vector3 m = rayOrigin - sphereCenter;
    float b = m.Dot(rayDir);
    float c = m.Dot(m) - sphereRadius * sphereRadius;

    if (c > 0.0f && b > 0.0f) return false;

    float discr = b * b - c;
    if (discr < 0.0f) return false;

    outDistance = -b - sqrtf(discr);
    if (outDistance < 0.0f) outDistance = 0.0f;

    return true;
}
