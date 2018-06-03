#include "Bug.h"

Bug::Bug(const Vec2 in_offset)
{
	offset = in_offset;
}

void Bug::ProcessMouse(Mouse & mouse)
{
	while (!mouse.IsEmpty())
	{
		const auto e = mouse.Read();
		if (e.GetType() == Mouse::Event::Type::RPress)
		{
			target = mouse.GetPos() - offset;
		}
	}
}

void Bug::Update(const Vec2& in_offset)
{
	offset = in_offset;
	vel = target - brdPos;
	float margin = 2.0f;
	RectF targetRect(target.x-margin,target.x+margin,target.y-margin,target.y+margin);
	if (!targetRect.Contains(brdPos))
		brdPos += vel.Normalize() * speed;
	scrnPos = brdPos + offset;
	scrnTarget = target + offset;
}

void Bug::Draw(Graphics & gfx,const RectF clamp) const
{
	gfx.RectBorderClamp(RectF(scrnPos, width, height), Colors::Green, clamp);
	gfx.PutPixelClamp(scrnTarget, Colors::Red, clamp);
}
