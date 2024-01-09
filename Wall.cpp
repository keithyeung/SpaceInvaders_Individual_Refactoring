#include "Wall.h"

Wall::Wall(float initialX, float initialY) noexcept : active(true), position{ initialX, initialY }, health(50) {}

void Wall::Render(const MyTexture& tex) const noexcept
{
	constexpr float offset = 100.0f;
	DrawTexture(tex.get(), position.x - offset, position.y - offset, WHITE);
	DrawText(TextFormat("%i", health), position.x - 21, position.y + 10, 40, RED);
}

void Wall::Update() noexcept
{
	// set walls as inactive when out of health
	if (health < 1)
	{
		active = false;
	}
}