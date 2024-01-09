#pragma once
#include "raylib.h"
#include "Source/Resources.h"


constexpr static float PLAYER_RADIUS = 50;
class Player
{
	constexpr static float speed = 7.0f;
	int direction = 0;
	float timer = 0;
public:
	int activeTexture = 0;
	int lives = 3;
	float player_base_height = 100.0f;
	Vector2 position{ (GetScreenWidthF() / 2.0f),GetScreenHeightF() - player_base_height };
	void Render(Texture2D texture) noexcept;
	void Update() noexcept;
};
