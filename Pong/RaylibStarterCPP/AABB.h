#pragma once

#include "raymath.h"
#include <limits>


class AABB
{
public:

    const float negativeInfinity = -std::numeric_limits<float>::infinity();
    const float positiveInfinity = std::numeric_limits<float>::infinity();

    Vector3 min = Vector3{ negativeInfinity, negativeInfinity, negativeInfinity };

    Vector3 max = Vector3{ positiveInfinity, positiveInfinity, positiveInfinity };

    AABB();
    AABB(Vector3 min, Vector3 max);

    Vector3 Center();
    bool IsEmpty();
    void Empty();

    void Fit(Vector3* points, int numberOfPoints);
    void SetToTransformedBox(AABB box, Matrix m);
    AABB Transform(Matrix spriteTransform);

    static Vector3 Min(Vector3 a, Vector3 b);
    static Vector3 Max(Vector3 a, Vector3 b);

    Vector3 ClosestPoint(Vector3 p);
    bool Overlaps(Vector3 point);
    bool Overlaps(AABB other);

    void Draw(Color color);
};

