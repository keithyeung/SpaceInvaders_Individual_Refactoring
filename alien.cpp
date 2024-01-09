#include "alien.h"
#include "Source/Resources.h"

Alien::Alien(float initialX, float initialY) noexcept : active(true), position{ initialX, initialY } {}


void Alien::Update() noexcept
{
	position.x += moveRight ? speed : -speed;
	CheckDirection();
}

void Alien::CheckDirection() noexcept
{
	if (position.x >= GetScreenWidthF() - 100)
	{
		moveRight = false;
		position.y += 50;
	}
	else if (position.x <= 100)
	{
		moveRight = true;
		position.y += 50;
	}
}
void Alien::Render(Texture2D texture) noexcept
{
	DrawTexture(texture, position.x, position.y, WHITE);
}

