#pragma once
#include "Graphics.h"
#include "RectF.h"
#include "Vec2.h"
#include "Tile.h"
#include "Board.h"
#include "Bug.h"

class Flower
{
public:
	Flower(const Tile::Location in_loc);
	void UpdateOffset(const Vec2& offset);
	void Draw(Graphics& gfx);
private:
	
	Tile::Location& loc;
};