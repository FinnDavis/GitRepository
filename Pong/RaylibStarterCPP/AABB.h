#pragma once
#include "raylib.h"
#include "raygui.h"
#include "raymath.h"
#include <limits>

class AABB
{
public:

    const float negativeInfinity = -std::numeric_limits<float>::infinity();
    const float positiveInfinity = std::numeric_limits<float>::infinity();
    

    Vector3 min = Vector3{ negativeInfinity, negativeInfinity, negativeInfinity };

    Vector3 max = Vector3{ positiveInfinity, positiveInfinity, positiveInfinity };



    AABB()
    {
    }

    AABB(Vector3 min, Vector3 max)
    {
        this->min = min;
        this->max = max;
    }
    Vector3 Center()
    {
        return (Vector3Multiply(Vector3Add(min, max), Vector3{ 0.5f, 0.5f , 0.5f }));
    }
    bool IsEmpty()
    {
        if (negativeInfinity == min.x &&
            negativeInfinity == min.y &&
            negativeInfinity == min.z &&
            positiveInfinity == max.x &&
            positiveInfinity == max.y &&
            positiveInfinity == max.z)
            return true;
        return false;
    }
    
    void Empty()
    {
        min = Vector3{ negativeInfinity,
            negativeInfinity,
            negativeInfinity };

        max = Vector3{ positiveInfinity,
            positiveInfinity,
            positiveInfinity };
    }

    void SetToTransformedBox(AABB box, Matrix m)
    {
        // If we're empty, then exit (an empty box defined as having the min/max  
        // set to infinity) 
        if (box.IsEmpty())
        {
            Empty();
            return;
        }

        //Scale the box based on orientation of the x-axis of m.
        if (m.m0 > 0.0f)
        {
            min.x += m.m0 * box.min.x; max.x += m.m0 * box.max.x;
        }
        else
        {
            min.x += m.m0 * box.max.x; max.x += m.m0 * box.min.x;
        }

        if (m.m01 > 0.0f)
        {
            min.y += m.m01 * box.min.x; max.y += m.m01 * box.max.x;
        }
        else
        {
            min.y += m.m01 * box.max.x; max.y += m.m01 * box.min.x;
        }

        if (m.m02 > 0.0f)
        {
            min.z += m.m02 * box.min.x; max.z += m.m02 * box.max.x;
        }
        else
        {
            min.z += m.m02 * box.max.x; max.z += m.m02 * box.min.x;
        }

        //Scale the box based on orientation of the y-axis of m.
        if (m.m10 > 0.0f)
        {
            min.x += m.m10 * box.min.y; max.x += m.m10 * box.max.y;
        }
        else
        {
            min.x += m.m10 * box.max.y; max.x += m.m10 * box.min.y;
        }

        if (m.m11 > 0.0f)
        {
            min.y += m.m11 * box.min.y; max.y += m.m11 * box.max.y;
        }
        else
        {
            min.y += m.m11 * box.max.y; max.y += m.m11 * box.min.y;
        }

        if (m.m12 > 0.0f)
        {
            min.z += m.m12 * box.min.y; max.z += m.m12 * box.max.y;
        }
        else
        {
            min.z += m.m12 * box.max.y; max.z += m.m12 * box.min.y;
        }

        //Scale the box based on orientation of the z-axis of m.
        if (m.m20 > 0.0f)
        {
            min.x += m.m20 * box.min.z; max.x += m.m20 * box.max.z;
        }
        else
        {
            min.x += m.m20 * box.max.z; max.x += m.m20 * box.min.z;
        }

        if (m.m21 > 0.0f)
        {
            min.y += m.m21 * box.min.z; max.y += m.m21 * box.max.z;
        }
        else
        {
            min.y += m.m21 * box.max.z; max.y += m.m21 * box.min.z;
        }

        if (m.m22 > 0.0f)
        {
            min.z += m.m22 * box.min.z; max.z += m.m22 * box.max.z;
        }
        else
        {
            min.z += m.m22 * box.max.z; max.z += m.m22 * box.min.z;
        }
    }
    void Fit(Vector3[] points)
    {
        Empty();
        if (points.Length == 0)
            return;

        foreach(var point in points)
        {
            min = Min(min, point);
            max = Max(max, point);
        }
    }
    static Vector3 Min(Vector3 a, Vector3 b)
    {
        return Vector3(Math.Min(a.x, b.x), Math.Min(a.y, b.y), Math.Min(a.z, b.z));
    }
    static Vector3 Max(Vector3 a, Vector3 b)
    {
        return Vector3(Math.Max(a.x, b.x), Math.Max(a.y, b.y), Math.Max(a.z, b.z));
    }
    bool Overlaps(Vector3 point)
    {
        return !(point.x < min.x || point.y < min.y ||
            point.x > max.x || point.y > max.y);
    }
    bool Overlaps(AABB other)
    {
        return !(max.x < other.min.x || max.y < other.min.y ||
            min.x > other.max.x || min.y > other.max.y);
    }
    Vector3 ClosestPoint(Vector3 p)
    {
        return Vector3.Clamp(p, min, max);
    }
    void Draw(Color color)
    {
        DrawRectangleLines(
            min.x,
            min.y,
            Math.Abs(max.x - min.x),
            Math.Abs(max.y - min.y), color);
    }
    AABB Transform(Matrix spriteTransform)
    {
        AABB transformedBox = AABB();
        transformedBox.min = Vector3();
        transformedBox.max = Vector3();
        transformedBox.SetToTransformedBox(this, spriteTransform);
        return transformedBox;
    }
};

