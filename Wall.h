#pragma once
#include "raylib.h"


class Wall
{
public:
	Wall(float initialX, float initialY) noexcept;

	Vector2 position;
	float health = 50.0f;
	bool active;
	void Render(Texture2D texture) noexcept;
	void Update() noexcept;
};

