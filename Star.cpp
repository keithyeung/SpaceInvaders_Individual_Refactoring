#include "Star.h"
#include "Source/Resources.h"

Star::Star(float initialX, float initialY) noexcept : position{ initialX, initialY }
{
	size = GetRandomValueF(1, 4);
}

void Star::Render() const noexcept
{
	DrawCircleV(position, size, SKYBLUE);
}

