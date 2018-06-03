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
			target = mouse.GetPos();
	}
}

void Bug::Update(const Vec2 offset)
{

}

void Bug::Draw(Graphics & gfx,const RectF clamp) const
{
	gfx.RectBorderClamp(RectF(brdPos, width, height), Colors::Green, clamp);
}
