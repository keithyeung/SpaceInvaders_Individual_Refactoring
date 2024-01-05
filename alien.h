#pragma once
#include "raylib.h"


class Alien
{
public:
	Alien(float initialX, float initialY) noexcept;

	Color color = WHITE;
	Vector2 position = { 0, 0 };
	float radius = 30;
	bool active;
	bool moveRight = true;
	int speed = 2;

	void Update() noexcept;
	void Render(Texture2D texture) noexcept;

};

