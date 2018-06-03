#include "Vec2.h"

Vec2::Vec2(const Vec2 & in)
	:
	x(in.x),
	y(in.y)
{
}

Vec2::Vec2(const float in_x, const float in_y)
	:
	x(in_x),
	y(in_y)
{
}

Vec2 Vec2::operator+(const Vec2 & rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2 & rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 & Vec2::operator+=(const Vec2 & rhs)
{
	return *this = *this + rhs;
}

Vec2 & Vec2::operator-=(const Vec2 & rhs)
{
	return *this = *this - rhs;
}

Vec2 Vec2::operator*(const float rhs)
{
	return Vec2(x * rhs, y * rhs);
}

Vec2 Vec2::operator/(const float rhs)
{
	return Vec2(x / rhs, y / rhs);
}

float Vec2::GetLengthSq() const
{
	return x*x + y*y;
}

float Vec2::GetLength() const
{
	return sqrtf(GetLengthSq());
}

Vec2& Vec2::Normalize()
{
	return *this = *this * (1.0f / GetLength());
}

Vec2 Vec2::GetNormalized() 
{
	return Vec2(*this * (1.0f / GetLength()));
}
