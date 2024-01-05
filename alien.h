#pragma once
#include "raylib.h"

class Alien
{
public:
	Alien(float initialX, float initialY) noexcept;

	Color color = WHITE;
	Vector2 position = { 0, 0 };
	const float radius = 30;
	bool active = true;
	bool moveRight = true;
	const int speed = 2;

	void Update() noexcept;
	void Render(const Texture2D texture) noexcept;
private:

};

