#include "projectile.h"

Projectile::Projectile(Vector2 p_position, int p_speed) noexcept
	: position(p_position)
	, speed(p_speed)
	, rect(Rectangle(p_position.x, p_position.y, 10, 50))
	, active(true)
{

}

void Projectile::Render(const MyTexture& tex) const noexcept
{
	constexpr float offset = 25.0f;
	const Vector2 p_position = { position.x - offset, position.y - offset };
	DrawTextureV(tex.get(), p_position, WHITE);
}

void Projectile::Update() noexcept
{
	position.y -= speed;

	rect.x = position.x;
	rect.y = position.y;

	if (position.y < 0 || position.y > 1500)
	{
		active = false;
	}
}