#include "FrameTimer.h"

FrameTimer::FrameTimer()
{
	last = std::chrono::steady_clock::now();
}

float FrameTimer::Mark()
{
	const auto oldLast = last;
	last = std::chrono::steady_clock::now();
	std::chrono::steady_clock::duration frameTime = last - oldLast;
	return frameTime.count();
}
