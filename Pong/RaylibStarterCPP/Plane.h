#pragma once

#include "AABB.h"
#include "raymath.h"
#include <limits>


class Plane
{
private:

    Vector3 N;
    float offset;

public:

    enum class ePlaneResult : int
    {
        FRONT = 1,
        BACK = -1,
        INTERSECTS = 0
    };

    Plane();
    Plane(float x, float y, float offset);
    Plane(Vector3 n, float offset);
    Plane(Vector3 p1, Vector3 p2);

    float DistanceTo(Vector3 p);
    Vector3 ClosestPoint(Vector3 p);

    Vector2 GetPlaneDirection();

    ePlaneResult TestSide(Vector3 p);
    ePlaneResult TestSide(Vector3 spherePos, float sphereRadius);
    ePlaneResult TestSide(AABB aabb);
};

