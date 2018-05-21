#include "Board.h"

Board::Frame::Frame(const Vec2 & in_topLeft, const Vec2 & in_bottomRight)
{
	topLeft = in_topLeft;
	bottomRight = in_bottomRight;
	width = bottomRight.x - topLeft.x;
	height = bottomRight.y - topLeft.y;
	rect = RectF(topLeft, bottomRight);
}

void Board::Frame::Draw(Graphics & gfx)
{
	gfx.RectBorder(rect, c);
}

RectF Board::Frame::GetRect()
{
	return rect;
}

void Board::Tile::Init(const Vec2 & in_topLeft, const Location& in_loc)
{
	// tiles are drawn from top left corner of rect.
	loc = in_loc;
	topLeft = in_topLeft;
	// corners of diamond are then drawn from the center of the rect.
	rect = RectF(Vec2(topLeft.x, topLeft.y), Vec2(topLeft.x + tileWidth / 2.0f, topLeft.y + tileHeight));
	left   = Vec2( GetCenter().x - tileWidth / 2.0f, GetCenter().y );
	right  = Vec2( GetCenter().x + tileWidth / 2.0f, GetCenter().y );
	top    = Vec2( GetCenter().x, GetCenter().y - tileHeight / 2.0f );
	bottom = Vec2( GetCenter().x, GetCenter().y + tileHeight / 2.0f );
	// colors
	c_rect.SetR(40);
	c_rect.SetG(40);
	c_rect.SetB(40);
	c_lit.SetR(170);
	c_lit.SetG(211);
	c_lit.SetB(98);
	c_dead.SetR(70);
	c_dead.SetG(70);
	c_dead.SetB(30);
}

void Board::Tile::UpdateOffset(const Vec2 & in_topLeft)
{
	topLeft = in_topLeft;
	rect = RectF(Vec2(topLeft.x, topLeft.y), Vec2(topLeft.x + tileWidth / 2.0f, topLeft.y + tileHeight));
	left = Vec2(GetCenter().x - tileWidth / 2.0f, GetCenter().y);
	right = Vec2(GetCenter().x + tileWidth / 2.0f, GetCenter().y);
	top = Vec2(GetCenter().x, GetCenter().y - tileHeight / 2.0f);
	bottom = Vec2(GetCenter().x, GetCenter().y + tileHeight / 2.0f);
}

void Board::Tile::Draw(Graphics & gfx,const RectF& clamp)
{
	DrawRect(gfx,clamp);
	DrawTile(gfx,clamp);
}

bool Board::Tile::IsInFrame(Frame& frame)
{
	if (left.x >= frame.GetRect().left &&
		right.x < frame.GetRect().right &&
		top.y >= frame.GetRect().top &&
		bottom.y < frame.GetRect().bottom)
		return true;
	else
		return false;
}

Vec2 Board::Tile::GetCenter()
{
	return RectF::GetCenter(rect);
}

Board::Location Board::Tile::GetLoc()
{
	return loc;
}

void Board::Tile::DrawRect(Graphics & gfx, const RectF& clamp )
{
	gfx.RectBorderClamp(rect, c_rect, clamp);
}

void Board::Tile::DrawTile(Graphics & gfx,const RectF& clamp)
{
	gfx.PutPixelClamp(left,  c_diamond,clamp);
	gfx.PutPixelClamp(right, c_diamond,clamp);
	gfx.PutPixelClamp(top,   c_diamond,clamp);
	gfx.PutPixelClamp(bottom,c_diamond,clamp);
	gfx.LineClamp(left,top,    c_diamond,clamp);
	gfx.LineClamp(top,right,   c_diamond,clamp);
	gfx.LineClamp(bottom,right,c_diamond,clamp);
	gfx.LineClamp(left,bottom, c_diamond,clamp);
}

void Board::Tile::ProcessMouse(const Mouse & mouse)
{
	if (mouse.GetPosX() >= rect.left &&
		mouse.GetPosX() < rect.right &&
		mouse.GetPosY() >= rect.top &&
		mouse.GetPosY() < rect.bottom)
	{
		mouseIsOver = true;
		c_diamond = c_lit;
	}
	else
	{
		mouseIsOver = false;
		c_diamond = c_dead;
	}
}

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
			Vec2 pos = Vec2(offset.x + x * tileWidth / 2.0f, offset.y + y * tileHeight);
			// if column is uneven, offset by half height.
			if ((x % 2) > 0)
				pos.y += tileHeight / 2.0f;

			tiles[i].Init(pos,Location(x,y));
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

	TileAt(mouseLoc).Draw(gfx,frame.GetRect());
}

void Board::ProcessBoard(const Keyboard & kbd, const Mouse& mouse)
{
	// keyboard controls-- to move map around
	if (kbd.KeyIsPressed(VK_UP) || kbd.KeyIsPressed('W'))
		offset.y -= speed;
	if (kbd.KeyIsPressed(VK_DOWN) || kbd.KeyIsPressed('S'))
		offset.y += speed;
	if (kbd.KeyIsPressed(VK_LEFT) || kbd.KeyIsPressed('A'))
		offset.x -= speed;
	if (kbd.KeyIsPressed(VK_RIGHT) || kbd.KeyIsPressed('D'))
		offset.x += speed;

	ClampTileArray();
	// tile placing code, yet again. except 60x per second
	for (int y = 0; y < dimY; ++y)
	{
		for (int x = 0; x < dimX; ++x)
		{
			Vec2 pos = Vec2(offset.x + x * tileWidth / 2.0f, offset.y + y * tileHeight);
			if ((x % 2) > 0)
				pos.y += tileHeight / 2.0f;

			tiles[y * dimX + x].UpdateOffset(pos);
			// process the mouse to change color, etc.
			tiles[y * dimX + x].ProcessMouse(mouse);
			// assign the board's mouseLoc to the location of the tile the mouse is over.
			if (tiles[y * dimX + x].mouseIsOver)
				mouseLoc = tiles[y * dimX + x].GetLoc();
		}
	}
}

Board::Tile & Board::TileAt(Location & loc)
{
	return tiles[loc.y*dimX + loc.x];
}

void Board::ClampTileArray()
{
	if (offset.x > frame.GetRect().left)
		offset.x = frame.GetRect().left;

	if (GetTileArrayRect().right < frame.GetRect().right)
		offset.x = frame.GetRect().right - GetTileArrayRect().width;

	if(offset.y > frame.GetRect().top)
		offset.y = frame.GetRect().top;

	if (GetTileArrayRect().bottom < frame.GetRect().bottom)
		offset.y = frame.GetRect().bottom - GetTileArrayRect().height;
}

RectF Board::GetTileArrayRect()
{
	Vec2 bottomRight;
	bottomRight.x = offset.x + ((tileWidth / 2) * dimX);
	bottomRight.y = offset.y + (tileHeight * dimY) + (tileHeight / 2);
	return RectF(topLeft,bottomRight);
}
