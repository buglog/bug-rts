#pragma once
#include "RectF.h"
#include "Vec2.h"
#include "Mouse.h"
#include "Board.h"

class Bug
{
public:
	void Update(float dt, const Mouse& mouse);
	void Draw(Graphics& gfx);
	RectF GetRect();
public:
	Vec2 pos;
	Vec2 vel;
	Vec2 target;
	static constexpr int width = 30;
	static constexpr int height = 20;
};