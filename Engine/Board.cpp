#include "Board.h"


Board::Board(const Vec2& in_topLeft, const Vec2& in_bottomRight)
	:
	offset(in_topLeft),
	topLeft(in_topLeft),
	bottomRight(in_bottomRight)
{
	frame = Frame(topLeft, bottomRight);
	// tile placing code!
	int i = 0;
	for (int y = 0; y < dimY; ++y)
	{
		for (int x = 0; x < dimX; ++x)
		{
			Vec2 pos = Vec2(offset.x + x * Tile::width / 2.0f, offset.y + y * Tile::height);
			// if column is uneven, offset by half height.
			if ((x % 2) > 0)
				pos.y += Tile::height / 2.0f;

			tiles[i].Init(pos,Tile::Location(x,y));
			++i;
		}
	}
}

void Board::Draw(Graphics & gfx)
 {
	for (Tile& t : tiles)
	{
		// if(t.IsInFrame(frame))
			t.Draw(gfx,frame.GetRect());
	}
	frame.Draw(gfx);
	gfx.RectBorder(RectF(frame.GetRect().left + 1.0f, frame.GetRect().right - 1.0f, frame.GetRect().top + 1.0f, frame.GetRect().bottom - 1.0f ), Colors::Blue);

	TileAt(mouseLoc).DrawDiamond(gfx,frame.GetRect());
}

void Board::ProcessInput(const Keyboard & kbd, const Mouse& mouse)
{
	// keyboard controls-- to move map around
	if (kbd.KeyIsPressed(VK_UP) || kbd.KeyIsPressed('W'))
		offset.y += speed;
	if (kbd.KeyIsPressed(VK_DOWN) || kbd.KeyIsPressed('S'))
		offset.y -= speed;
	if (kbd.KeyIsPressed(VK_LEFT) || kbd.KeyIsPressed('A'))
		offset.x += speed;
	if (kbd.KeyIsPressed(VK_RIGHT) || kbd.KeyIsPressed('D'))
		offset.x -= speed;

	ClampTileArray(50);
	// tile placing code, yet again. except 60x per second
	for (int y = 0; y < dimY; ++y)
	{
		for (int x = 0; x < dimX; ++x)
		{
			Vec2 pos = Vec2(offset.x + x * Tile::width / 2.0f, offset.y + y * Tile::height);
			if ((x % 2) > 0)
				pos.y += Tile::height / 2.0f;

			tiles[y * dimX + x].UpdateOffset(pos);
			// process the mouse to change color, etc.
			tiles[y * dimX + x].ProcessMouse(mouse);
			// assign the board's mouseLoc to the location of the tile the mouse is over.
			if (tiles[y * dimX + x].mouseIsOver)
				mouseLoc = tiles[y * dimX + x].GetLoc();
		}
	}
}

Tile& Board::TileAt(Tile::Location & loc)
{
	return tiles[loc.y*dimX + loc.x];
}

void Board::ClampTileArray(const int buffer)
{
	if (offset.x > frame.GetRect().left + (Tile::width/4) + buffer)
		offset.x = frame.GetRect().left + (Tile::width/4) + buffer;

	if (GetTileArrayRect().right < frame.GetRect().right			- (Tile::width/4) - buffer)
		offset.x = frame.GetRect().right - GetTileArrayRect().width - (Tile::width/4) - buffer;

	if (offset.y > frame.GetRect().top + buffer)
		offset.y = frame.GetRect().top + buffer;

	if (GetTileArrayRect().bottom < frame.GetRect().bottom - buffer)
		offset.y = frame.GetRect().bottom - GetTileArrayRect().height - buffer;
}

RectF Board::GetTileArrayRect()
{
	Vec2 bottomRight;
	bottomRight.x = offset.x + ((Tile::width / 2) * dimX);
	bottomRight.y = offset.y + (Tile::height * dimY) + (Tile::height / 2);
	return RectF(offset,bottomRight);
}
