#pragma once
#include "raylib.h"

class Wall
{
public:
	Wall();
	~Wall();

	Vector2 position;
	Rectangle rec;
	bool active;
	Color color;
	int health = 50;
	const int radius = 60;

	void Render(const Texture2D texture) noexcept;
	void Update() noexcept;
private:

};

