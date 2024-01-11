#include "Wall.h"

Wall::Wall(float initialX, float initialY) noexcept : active(true), position{ initialX, initialY }, health(50) {}

void Wall::Render(const MyTexture& tex) const noexcept
{
	constexpr float offset = 100.0f;
	const Vector2 p_position{ position.x - offset, position.y - offset };
	DrawTextureV(tex.get(), p_position, WHITE);
	const int temp_Int_ValueX{ GetIntValue(position.x - 21) };
	const int temp_Int_ValueY{ GetIntValue(position.y + 10) };
	DrawText(TextFormat("%i", health), temp_Int_ValueX, temp_Int_ValueY, 40, RED);
}

void Wall::Update() noexcept
{
	// set walls as inactive when out of health
	if (health < 1)
	{
		active = false;
	}
}