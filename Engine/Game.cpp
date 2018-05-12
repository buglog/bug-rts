/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	tile(Vec2(400.0f,100.0f))
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	Vec2 buttz;

	buttz = tile.GetCenter();

	buttz += Vec2(1.0f, 1.0f);
}

void Game::ComposeFrame()
{
	RectF rect(Vec2(100.0f, 40.0f), Vec2(120.0f, 568.0f)); 
	gfx.Rectangle(rect, Colors::Yellow, Colors::Cyan);

	tile.Draw(gfx);
}

void Game::ClampToScreen(Vec2 & v)
{
	if (v.x < 0.0f)
	{
		v.x = 0.0f;
	}
	if (v.x > (float)Graphics::ScreenWidth)
	{
		v.x = (float)Graphics::ScreenWidth - 1.0f;
	}
	if (v.y < 0.0f)
	{
		v.y = 0.0f;
	}
	if (v.y >(float)Graphics::ScreenHeight)
	{
		v.y = (float)Graphics::ScreenHeight - 1.0f;
	}
}