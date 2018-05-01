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
	float getLengthSq() const;
	float getLength() const;
	Vec2& normalize();
	Vec2 getNormalized();
public:
	float x;
	float y;
};