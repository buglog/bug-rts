#include "Board.h"

Board::Board(int in_dimX, int in_dimY)
	:
	dimX(in_dimX),
	dimY(in_dimY)
{
}

Board::Tile::Tile(const Vec2 & in_topLeft)
{
	topLeft = in_topLeft;
	rect = RectF(Vec2(topLeft.x, topLeft.y), Vec2(topLeft.x + float(tileWidth / 2), topLeft.y + float(tileHeight)));
}

void Board::Tile::Draw(Graphics & gfx)
{
	DrawRect(gfx);
	DrawTile(gfx);
}

Vec2 Board::Tile::GetCenter()
{
	return RectF::GetCenter(rect);
}

void Board::Tile::DrawRect(Graphics & gfx)
{
	gfx.RectBorder(rect, Colors::Green);
}

void Board::Tile::DrawTile(Graphics & gfx)
{

}
