#include "alien.h"

Alien::Alien() noexcept : active(true)
{
}

Alien::Alien(float initialX, float initialY) : active(true), position{ initialX, initialY }
{
}

Alien::~Alien()
{
}

void Alien::Update() noexcept
{
	if (moveRight)
	{
		position.x += speed;

		if (position.x >= GetScreenWidth())
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