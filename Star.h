#pragma once
#include "raylib.h"

class Star
{
public:
	Star(float initialX,float initialY) noexcept;
	Vector2 position = { 0, 0 };
	float size;
	void Render() const noexcept;
};


