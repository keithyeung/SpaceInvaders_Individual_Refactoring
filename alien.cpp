#include "alien.h"
#include "Source/Resources.h"

Alien::Alien(float initialX, float initialY) noexcept : active(true), position{ initialX, initialY } {}


void Alien::Update() noexcept
{
	if (moveRight)
	{
		position.x += speed;

		if (position.x >= GetScreenWidthF())
		{
			moveRight = false;
			position.y += 50;
		}
	}
	else
	{
		position.x -= speed;

		if (position.x <= 0)
		{
			moveRight = true;
			position.y += 50;
		}
	}
}

void Alien::Render(Texture2D texture) noexcept
{
	DrawTexture(texture, position.x, position.y, WHITE);
}