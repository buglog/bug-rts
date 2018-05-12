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

void Board::Tile::Init(const Vec2 & in_topLeft)
{
	// tiles are drawn from top left corner of rect.
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

void Board::Tile::Draw(Graphics & gfx,const RectF& clamp)
{
	DrawRect(gfx,clamp);
	DrawTile(gfx,clamp);
}

Vec2 Board::Tile::GetCenter()
{
	return RectF::GetCenter(rect);
}

void Board::Tile::ProcessMouse(const Mouse & mouse)
{
	if (MouseIsOver(mouse))
	{
		c_diamond = c_lit;
	}
	else
	{
		c_diamond = c_dead; 
	}
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

bool Board::Tile::MouseIsOver(const Mouse & mouse)
{
	if (mouse.GetPosX() >= rect.left &&
		mouse.GetPosX() <= rect.right &&
		mouse.GetPosY() >= rect.top &&
		mouse.GetPosY() <= rect.bottom)
	{
		return true;
	}
	return false;
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

			tiles[i].Init(pos);
			++i;
		}
	}
}

void Board::Draw(Graphics & gfx)
 {
	frame.Draw(gfx);
	for (Tile& t : tiles)
	{
		// if(t.IsInFrame(frame))
			t.Draw(gfx,frame.GetRect());
	}
}

void Board::ProcessOffset(Keyboard & kbd)
{
	// keyboard controls-- supposed to move map around but not working lmao
	if (kbd.KeyIsPressed(VK_UP) || kbd.KeyIsPressed('W'))
		offset.y -= speed;
	if (kbd.KeyIsPressed(VK_DOWN) || kbd.KeyIsPressed('S'))
		offset.y += speed;
	if (kbd.KeyIsPressed(VK_LEFT) || kbd.KeyIsPressed('A'))
		offset.x -= speed;
	if (kbd.KeyIsPressed(VK_RIGHT) || kbd.KeyIsPressed('D'))
		offset.x += speed;

	// tile placing code, yet again. except 60x per second
	int i = 0;
	for (int y = 0; y < dimY; ++y)
	{
		for (int x = 0; x < dimX; ++x)
		{
			Vec2 pos = Vec2(offset.x + x * tileWidth / 2.0f, offset.y + y * tileHeight);
			if ((x % 2) > 0)
				pos.y += tileHeight / 2.0f;

			tiles[i].Init(pos);
			++i;
		}
	}
}

void Board::ProcessTiles(const Mouse & mouse)
{
	for (Tile& t : tiles)
	{
		t.ProcessMouse(mouse);
	}
}