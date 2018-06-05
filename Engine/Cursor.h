#pragma once
#include "Vec2.h"
#include "RectF.h"
#include "Board.h"
#include "Mouse.h"

class Cursor
{ // the idea for the Cursor class is to specify different mouse behavior for different states. 
	// For example- this class will handle box select, and be aware of all objects. OR all objects are aware of it? not sure.
	// it will also handle building placement and other cool stuff.
public:
	enum class State
	{
		
	};
public:
	Cursor(Board& in_brd);
private:
	Board& brd;
};