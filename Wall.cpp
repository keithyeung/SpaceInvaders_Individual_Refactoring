#include "Wall.h"

Wall::Wall() noexcept
{
}

Wall::~Wall()
{
}

void Wall::Render(Texture2D texture)
{
	constexpr float offset = 100.0f;
	DrawTexture(texture, position.x - offset, position.y - offset, WHITE);
	DrawText(TextFormat("%i", health), position.x - 21, position.y + 10, 40, RED);
}

void Wall::Update()
{
	// set walls as inactive when out of health
	if (health < 1)
	{
		active = false;
	}
}