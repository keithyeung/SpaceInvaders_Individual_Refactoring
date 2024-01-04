#pragma once
#include "raylib.h"

class Alien
{
public:
	Alien() noexcept;
	Alien(float initialX, float initialY);
	~Alien();

	Color color = WHITE;
	Vector2 position = { 0, 0 };
	int x = 0;
	int y = 0;
	float radius = 30;
	bool active = true;
	bool moveRight = true;
	int speed = 2;

	void Update() noexcept;
	void Render(Texture2D texture) noexcept;
private:

};

