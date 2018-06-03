#pragma once
#include <math.h>

class Vec2
{
public:
	Vec2() = default;
	Vec2(const Vec2& in_vec);
	Vec2(const float in_x, const float in_y);
	Vec2 operator + (const Vec2& rhs) const;
	Vec2 operator - (const Vec2& rhs) const;
	Vec2& operator += (const Vec2& rhs);
	Vec2& operator -= (const Vec2& rhs);
	Vec2 operator * (const float rhs);
	Vec2 operator / (const float rhs);
	float GetLengthSq() const;
	float GetLength() const;
	Vec2& Normalize();
	Vec2 GetNormalized();
public:
	float x;
	float y;
};