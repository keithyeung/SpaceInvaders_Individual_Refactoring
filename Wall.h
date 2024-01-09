#pragma once
#include "raylib.h"
#include "Source/Resources.h"


class Wall
{
public:
	Wall(float initialX, float initialY) noexcept;

	Vector2 position;
	int health = 50;
	bool active = true;
	void Render(const MyTexture& tex) const noexcept;
	void Update() noexcept;
	//make a funtion to check if the wall is active if needed
};

