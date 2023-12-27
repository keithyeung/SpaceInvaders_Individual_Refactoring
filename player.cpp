#include "player.h"

Player::Player() noexcept
{
}

void Player::Render(Texture2D p_texture) noexcept
{
	constexpr float offset = 50.0f;
	DrawTexture(p_texture, position.x - offset, position.y - offset, WHITE);
}

void Player::Update() noexcept
{
	//Movement
	direction = 0;
	if (IsKeyDown(KEY_LEFT))
	{
		direction--;
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		direction++;
	}

	position.x += speed * direction;

	if (position.x < 0 + PLAYER_RADIUS)
	{
		position.x = 0 + PLAYER_RADIUS;
	}
	else if (position.x > GetScreenWidth() - PLAYER_RADIUS)
	{
		position.x = GetScreenWidth() - PLAYER_RADIUS;
	}


	//Determine frame for animation
	timer += GetFrameTime();

	if (timer > 0.4 && activeTexture == 2)
	{
		activeTexture = 0;
		timer = 0;
	}
	else if (timer > 0.4)
	{
		activeTexture++;
		timer = 0;
	}


}
