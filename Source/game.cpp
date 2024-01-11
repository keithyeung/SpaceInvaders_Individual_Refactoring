#include "game.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <span>



bool is_dead(const auto& entity) noexcept {
	return !entity.active;
}

float lineLength(Vector2 A, Vector2 B) noexcept//Uses pythagoras to calculate the length of a line
{
	return sqrtf(static_cast<float>(pow(B.x - A.x, 2) + pow(B.y - A.y, 2)));
}

Game::Game() noexcept
{
	// creating walls 
	SpawnWalls();
	//creating aliens
	SpawnAliens();
}

void Game::Start()
{
	// creating walls 
	SpawnWalls();
	//creating aliens
	SpawnAliens();
	//creating background
	Background newBackground;
	newBackground.Initialize(600);
	background = newBackground;

	//reset score
	score = 0;

	gameState = State::GAMEPLAY;

}

void Game::End()
{
	//SAVE SCORE AND UPDATE SCOREBOARD
	PlayerBullets.clear();
	EnemyBullets.clear();
	Walls.clear();
	Aliens.clear();
	newHighScore = CheckNewHighScore();
	gameState = State::ENDSCREEN;
}

void Game::Continue()
{
	SaveLeaderboard();
	gameState = State::STARTSCREEN;
}

void Game::Update()
{
	switch (gameState)
	{
	case State::STARTSCREEN:
		//Code 
		if (IsKeyReleased(KEY_SPACE))
		{
			Start();


		}
		break;
	case State::GAMEPLAY:
		player.Update();
		for (auto& i : Aliens)
		{
			i.Update(); 

			if (i.position.y > GetScreenHeight() - player.player_base_height)
			{
				End();
			}
		}
		if (player.lives < 1)
		{
			End();
		}
		if (Aliens.size() < 1)
		{
			SpawnAliens();
		}
		UpdateGamePlay();

		CollisionForAlienBullets();
		CollisionForPlayerBullets();

		//MAKE PROJECTILE
		if (IsKeyPressed(KEY_SPACE))
		{
			const Vector2 spawnPosition{ player.position.x ,player.position.y - PROJECTILE_HEIGHT };
			constexpr int speed = 15;
			PlayerBullets.push_back(Projectile(spawnPosition, speed));
		}
		//Aliens Shooting
		shootTimer += 1;
		if (shootTimer > 59) //once per second
		{
			int randomAlienIndex = 0;

			if (Aliens.size() > 1)
			{
				randomAlienIndex = rand() % Aliens.size();
			}
			Vector2 spawnPosition = Aliens[randomAlienIndex].position;
			spawnPosition.y += 40;
			constexpr int speed = -15;
			EnemyBullets.push_back(Projectile(spawnPosition, speed));
			shootTimer = 0;
		}
		RemoveDeadEntities();
	break;
	case State::ENDSCREEN:
		//Code
	
		//Exit endscreen
		if (IsKeyReleased(KEY_ENTER) && !newHighScore)
		{
			Continue();
		}

		if (newHighScore)
		{
			if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
			else mouseOnText = false;

			if (mouseOnText)
			{
				// Set the window's cursor to the I-Beam
				SetMouseCursor(MOUSE_CURSOR_IBEAM);

				// Get char pressed on the queue
				int key = GetCharPressed();

				// Check if more characters have been pressed on the same frame
				while (key > 0)
				{
					// NOTE: Only allow keys in range [32..125]
					if ((key >= 32) && (key <= 125) && (letterCount < 9))
					{
						name[letterCount] = (char)key;
						name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
						letterCount++;
					}

					key = GetCharPressed();  // Check next character in the queue
				}
				//Remove chars 
				if (IsKeyPressed(KEY_BACKSPACE))
				{
					letterCount--;
					if (letterCount < 0) letterCount = 0;
					name[letterCount] = '\0';
				}
			}
			else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

			if (mouseOnText)
			{
				framesCounter++;
			}
			else
			{
				framesCounter = 0;
			}
			if (letterCount > 0 && letterCount < 9 && IsKeyReleased(KEY_ENTER))
			{
				std::string nameEntry(name);

				InsertNewHighScore(nameEntry);

				newHighScore = false;
			}
		}
		break;
	default:
		//SHOULD NOT HAPPEN
		break;
	}
}

#include "Resources.h"
void Game::UpdateGamePlay() noexcept
{
	update(std::span(PlayerBullets));
	update(std::span(EnemyBullets));
	update(std::span(Walls));
}

void Game::Render() noexcept
{
	BeginDrawing();
	ClearBackground(BLACK);
	switch (gameState)
	{
	case State::STARTSCREEN:
		DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);
		DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);
		break;
	case State::GAMEPLAY:
		RenderGamePlay();
		break;
	case State::ENDSCREEN:
		if (newHighScore)
		{
			DrawText("NEW HIGHSCORE!", 600, 300, 60, YELLOW);
			// BELOW CODE IS FOR NAME INPUT RENDER
			DrawText("PLACE MOUSE OVER INPUT BOX!", 600, 400, 20, YELLOW);

			DrawRectangleRec(textBox, LIGHTGRAY);
			if (mouseOnText)
			{
				DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
			}
			else
			{
				DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
			}
			DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
			DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), 600, 600, 20, YELLOW);

			if (mouseOnText)
			{
				if (letterCount < 9)
				{
					if (((framesCounter / 20) % 2) == 0)
					{
						DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
					}

				}
				else
				{
					DrawText("Press BACKSPACE to delete chars...", 600, 650, 20, YELLOW);
				}
			}			
			if (letterCount > 0 && letterCount < 9)
			{
				DrawText("PRESS ENTER TO CONTINUE", 600, 800, 40, YELLOW);
			}
		}
		else {
			DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);
			DrawText("LEADERBOARD", 50, 100, 40, YELLOW);
			for (int i = 0; i < Leaderboard.size(); i++)
			{
				char* tempNameDisplay = Leaderboard[i].name.data(); // use string
				DrawText(tempNameDisplay, 50, 140 + (i * 40), 40, YELLOW);
				DrawText(TextFormat("%i", Leaderboard[i].score), 350, 140 + (i * 40), 40, YELLOW);
			}
		}
		break;
	default:
		break;
	}
	EndDrawing();
}

void Game::RenderGamePlay() noexcept
{
	background.Render();

	DrawText(TextFormat("Score: %i", score), 50, 20, 40, YELLOW);
	DrawText(TextFormat("Lives: %i", player.lives), 50, 70, 40, YELLOW);

	player.Render(resources.shipTextures[player.activeTexture].get());
	render(std::span(PlayerBullets), resources.laserTexture);
	render(std::span(EnemyBullets), resources.laserTexture);
	render(std::span(Walls), resources.barrierTexture);
	render(std::span(Aliens), resources.alienTexture);
}

void Game::SpawnAliens()
{
	constexpr float alienSpacing = 80.0f;
	constexpr int formationWidth = 8;
	constexpr int formationHeight = 5;
	constexpr float formationX = 100.0f;
	constexpr float formationY = 50.0f;
	constexpr float InitialXOffset = 450.0f;
	for (int row = 0; row < formationHeight; row++) {
		for (int col = 0; col < formationWidth; col++) {
			const auto xpos = formationX + InitialXOffset + (col * alienSpacing);
			const auto ypos = formationY + (row * alienSpacing);
			auto a = Alien{xpos, ypos};
			Aliens.emplace_back(a);
		}
	}
}

void Game::SpawnWalls()
{
	constexpr int wallCount = 5;
	const float wall_distance = GetScreenWidth() / (wallCount + 1.0f);
	constexpr float wallsPosYOffset = 300;
	for (int i = 0; i < wallCount; i++)
	{		
		const auto ypos = GetScreenHeightF() - wallsPosYOffset;
		const auto xpos = wall_distance * (i + 1);
		Walls.emplace_back(xpos,ypos);
	}
}

void Game::RemoveDeadEntities() noexcept
{
	std::erase_if(PlayerBullets, is_dead<Projectile>);
	std::erase_if(EnemyBullets, is_dead<Projectile>);
	std::erase_if(Aliens, is_dead<Alien>);
	std::erase_if(Walls, is_dead<Wall>);
}

void Game::CollisionForAlienBullets() noexcept
{
	for (auto& enemyBullet : EnemyBullets)
	{
		for (auto& wall : Walls)
		{
			const float Wallradius = 60.0f;
			if (CheckCollisionCircleRec(wall.position, Wallradius, enemyBullet.rect))
			{
				enemyBullet.active = false;
				wall.health -= 1;
			}
		}

		if (CheckCollisionCircleRec(player.position, PLAYER_RADIUS, enemyBullet.rect))
		{
			enemyBullet.active = false;
			player.lives -= 1;
		}
	}
}

void Game::CollisionForPlayerBullets() noexcept
{
	for (auto& playerBullet : PlayerBullets)
	{
		for (auto& wall : Walls)
		{
			constexpr float Wallradius = 60.0f;
			if (CheckCollisionCircleRec(wall.position, Wallradius, playerBullet.rect))
			{
				playerBullet.active = false;
				wall.health -= 1;
			}
		}

		for (auto& alien : Aliens)
		{
			const Vector2 alienCollisionPosOffset = { alien.position.x + 50 , alien.position.y + 50 };
			if (CheckCollisionCircleRec(alienCollisionPosOffset, alien.radius, playerBullet.rect))
			{
				playerBullet.active = false;
				alien.active = false;
				score += 100;
			}
		}
	}
}

bool Game::CheckNewHighScore() noexcept
{
	return (score > Leaderboard.back().score);
}

void Game::InsertNewHighScore(std::string name)
{
	PlayerData newData;
	newData.name = name;
	newData.score = score;

	for (int i = 0; i < Leaderboard.size(); i++)
	{
		if (newData.score > Leaderboard[i].score)
		{

			Leaderboard.insert(Leaderboard.begin() + i, newData);

			Leaderboard.pop_back();

			i = Leaderboard.size();
		}
	}
}

void Game::SaveLeaderboard()
{
	std::fstream file;

	file.open("Leaderboard");

	if (!file)
	{
		std::cout << "file not found \n";

	}
	else
	{
		std::cout << "file found \n";
	}
}


void Background::Initialize(int starAmount)
{
	for (int i = 0; i < starAmount; i++)
	{
		float posX = GetRandomValueF(-150, GetScreenWidth() + 150);
		float posY = GetRandomValueF(0, GetScreenHeight());
		Stars.emplace_back(posX,posY);
	}
}

void Background::Render() const noexcept
{
	for (const auto& i : Stars)
	{
		i.Render();
	}
}


