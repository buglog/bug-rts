#pragma once
#include "RectF.h"
#include "Vec2.h"
#include "Mouse.h"
#include "Board.h"

class Bug
{
	enum class State
	{
		OnGround,
		OnStem,
		InHole
	};
public:
	Bug() = default;
	Bug(const Vec2 offset);
	void ProcessMouse(Mouse& mouse);
	void Update(const Vec2& in_offset);
	void Draw(Graphics& gfx,const RectF clamp) const;
	RectF GetRect();
public:
	float speed = 3.0f;
	Vec2 offset;
	Vec2 brdPos = {200.0f,100.0f};
	Vec2 scrnPos = (brdPos + offset);
	Vec2 vel;
	Vec2 target = brdPos;
	Vec2 scrnTarget;
	static constexpr float width  = 40;
	static constexpr float height = 30;
};