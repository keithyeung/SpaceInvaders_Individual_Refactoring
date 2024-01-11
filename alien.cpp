#include "alien.h"
#include "Source/Resources.h"

void Alien::Update() noexcept
{
	position.x += speed;
	if (needToTurn()) {
		speed *= -1;
		position.y += 50;
	}
}

bool Alien::needToTurn() const noexcept{
	return  (position.x > GetScreenWidthF() - 100) || (position.x < 100);
}

void Alien::Render(const MyTexture& tex) const noexcept
{
	DrawTextureV(tex.get(), position, WHITE);
}

