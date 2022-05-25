#include "Plane.h"

Plane::Plane()
{
}

Plane::Plane(float x, float y, float offset)
{
    this->N = Vector3{ x, y, 0 };
    this->offset = offset;
}

 Plane::Plane(Vector3 n, float offset)
{
    this->N = n;
    this->offset = offset;
}

Plane::Plane(Vector3 p1, Vector3 p2)
{
    // calculate normalised vector from p0 to p1 
    Vector3 v = Vector3Subtract(p2, p1);
    Vector3Normalize(v);

    // set normal perpendicular to the vector 
    this->N.x = -v.y;
    this->N.y = v.x;

    // calculate offset
    this->offset = -Vector3DotProduct(p1, this->N);
}

float Plane::DistanceTo(Vector3 p)
{
    // C# implementation: return p.Dot(N) + d;
    return Vector3DotProduct(p, this->N) + this->offset;
}

Vector3 Plane::ClosestPoint(Vector3 p)
{
    // C# implementation: return p - N * DistanceTo(p); 
    float distanceToP = DistanceTo(p);
    return Vector3Multiply(Vector3Subtract(p, this->N), Vector3{ distanceToP , distanceToP , distanceToP });
}

Vector2 Plane::GetPlaneDirection()
{
    return Vector2{ this->N.x , this->N.y };
}

Plane::ePlaneResult Plane::TestSide(Vector3 p)
{
    //C#: p.Dot(N) + d;
    float t = Vector3DotProduct(p, this->N) + offset;

    if (t < 0)
    {
        return ePlaneResult::BACK;
    }
    else if (t > 0)
    {
        return ePlaneResult::FRONT;
    }
    return ePlaneResult::INTERSECTS;
}

Plane::ePlaneResult Plane::TestSide(Vector3 spherePos, float sphereRadius)
{
    float t = DistanceTo(spherePos);

    if (t > sphereRadius)
    {
        return ePlaneResult::FRONT;
    }
    else if (t < -sphereRadius)
    {
        return ePlaneResult::BACK;
    }
    return ePlaneResult::INTERSECTS;
}

Plane::ePlaneResult Plane::TestSide(AABB aabb)
{
    bool side[2]{ false, false };
        Vector3 corners[4]{ aabb.min,
                            Vector3{ aabb.min.x, aabb.max.y, aabb.min.z },
                            aabb.max,
                            Vector3{ aabb.max.x, aabb.min.y, aabb.min.z } };

    for (Vector3 &c : corners)
    {
        ePlaneResult result = TestSide(c);
        if (result == ePlaneResult::FRONT)
            side[0] = true;
        else if (result == ePlaneResult::BACK)
            side[1] = true;
    }
    if (side[0] && !side[1])
    {
        return ePlaneResult::FRONT;
    }
    else if (!side[0] && side[1])
    {
        return ePlaneResult::BACK;
    }
    return ePlaneResult::INTERSECTS;
}
