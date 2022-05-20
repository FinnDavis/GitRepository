#include "AABB.h"
#include <cstdlib>
#include <algorithm>

AABB::AABB()
{
}

AABB::AABB(Vector3 min, Vector3 max)
{
	this->min = min;
	this->max = max;
}

Vector3 AABB::Center()
{
	return (Vector3Multiply(Vector3Add(min, max), Vector3{ 0.5f, 0.5f , 0.5f }));
}

bool AABB::IsEmpty()
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

void AABB::Empty()
{
	min = Vector3{ negativeInfinity,
		negativeInfinity,
		negativeInfinity };

	max = Vector3{ positiveInfinity,
		positiveInfinity,
		positiveInfinity };
}

void AABB::SetToTransformedBox(AABB box, Matrix m)
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

	if (m.m1 > 0.0f)
	{
		min.y += m.m1 * box.min.x; max.y += m.m1 * box.max.x;
	}
	else
	{
		min.y += m.m1 * box.max.x; max.y += m.m1 * box.min.x;
	}

	if (m.m2 > 0.0f)
	{
		min.z += m.m2 * box.min.x; max.z += m.m2 * box.max.x;
	}
	else
	{
		min.z += m.m2 * box.max.x; max.z += m.m2 * box.min.x;
	}

	//Scale the box based on orientation of the y-axis of m.
	if (m.m4 > 0.0f)
	{
		min.x += m.m4 * box.min.y; max.x += m.m4 * box.max.y;
	}
	else
	{
		min.x += m.m4 * box.max.y; max.x += m.m4 * box.min.y;
	}

	if (m.m5 > 0.0f)
	{
		min.y += m.m5 * box.min.y; max.y += m.m5 * box.max.y;
	}
	else
	{
		min.y += m.m5 * box.max.y; max.y += m.m5 * box.min.y;
	}

	if (m.m6 > 0.0f)
	{
		min.z += m.m6 * box.min.y; max.z += m.m6 * box.max.y;
	}
	else
	{
		min.z += m.m6 * box.max.y; max.z += m.m6 * box.min.y;
	}

	//Scale the box based on orientation of the z-axis of m.
	if (m.m8 > 0.0f)
	{
		min.x += m.m8 * box.min.z; max.x += m.m8 * box.max.z;
	}
	else
	{
		min.x += m.m8 * box.max.z; max.x += m.m8 * box.min.z;
	}

	if (m.m9 > 0.0f)
	{
		min.y += m.m9 * box.min.z; max.y += m.m9 * box.max.z;
	}
	else
	{
		min.y += m.m9 * box.max.z; max.y += m.m9 * box.min.z;
	}

	if (m.m10 > 0.0f)
	{
		min.z += m.m10 * box.min.z; max.z += m.m10 * box.max.z;
	}
	else
	{
		min.z += m.m10 * box.max.z; max.z += m.m10 * box.min.z;
	}
}

void AABB::Fit(Vector3* points, int numberOfPoints)
{
	Empty();
	if (numberOfPoints == 0)
		return;

	for (int i = 0; i < numberOfPoints; i++)
	{
		min = Min(min, points[i]);
		max = Max(max, points[i]);
	}
}

Vector3 AABB::Min(Vector3 a, Vector3 b)
{
	return Vector3{ std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z) };
}

Vector3 AABB::Max(Vector3 a, Vector3 b)
{
	return Vector3{ std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z) };
}

bool AABB::Overlaps(Vector3 point)
{
	return !(point.x < min.x || point.y < min.y ||
		point.x > max.x || point.y > max.y);
}

bool AABB::Overlaps(AABB other)
{
	return !(max.x < other.min.x || max.y < other.min.y ||
		min.x > other.max.x || min.y > other.max.y);
}

Vector3 AABB::ClosestPoint(Vector3 p)
{
	return Vector3Max(min, Vector3Min(max, p));
}

void AABB::Draw(Color color)
{
	DrawRectangleLines(
		min.x,
		min.y,
		abs(max.x - min.x),
		abs(max.y - min.y), color);
}

AABB AABB::Transform(Matrix spriteTransform)
{
	AABB transformedBox = AABB();
	transformedBox.min = Vector3();
	transformedBox.max = Vector3();
	transformedBox.SetToTransformedBox(*this, spriteTransform);
	return transformedBox;
}
