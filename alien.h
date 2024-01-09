#pragma once
#include "raylib.h"
#include "Source/Resources.h"

struct Alien{
	static constexpr float radius = 30;					
	Vector2 position = { 0, 0 };
	int speed = 2;
	bool active = true;	
	
	void Update() noexcept;
	void Render(const MyTexture& tex) const noexcept;
private:
	bool needToTurn() const noexcept;
};

