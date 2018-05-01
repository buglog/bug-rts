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

float Vec2::getLengthSq() const
{
	return x*x + y*y;
}

float Vec2::getLength() const
{
	return sqrtf(getLengthSq());
}

Vec2& Vec2::normalize()
{
	return *this = *this * (1.0f / getLength());
}

Vec2 Vec2::getNormalized() 
{
	return Vec2(*this * (1.0f / getLength()));
}
