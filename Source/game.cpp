#include "game.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>


bool is_dead(const auto& entity) noexcept {
	return !entity.active;
}

float lineLength(Vector2 A, Vector2 B) noexcept//Uses pythagoras to calculate the length of a line
{
	const double length = sqrtf(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));
	return static_cast<float>(length);
}

Game::Game() 
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

void Game::Launch()
{
	//LOAD SOME RESOURCES HERE
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
		//Code
		if (IsKeyReleased(KEY_Q))
		{
			End();
		}

		//Update Player
		player.Update();
		
		//Update Aliens and Check if they are past player
		for (auto& i : Aliens)
		{
			i.Update(); 

			if (i.position.y > GetScreenHeight() - player.player_base_height)
			{
				End();
			}
		}

		//End game if player dies
		if (player.lives < 1)
		{
			End();
		}

		//Spawn new aliens if aliens run out
		if (Aliens.size() < 1)
		{
			SpawnAliens();
		}

		//UPDATE PROJECTILE
		for (auto& playerBullet : PlayerBullets)
		{
			playerBullet.Update();
		}
		for (auto& enemyBullet : EnemyBullets)
		{
			enemyBullet.Update();
		}
		for (auto& wall : Walls)
		{
			wall.Update();
		}

		//CHECK ALL COLLISONS HERE
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


		for (auto& playerBullet : PlayerBullets)
		{
			for (auto& wall : Walls)
			{
				const float Wallradius = 60.0f;
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

		// REMOVE INACTIVE/DEAD ENITITIES
		std::erase_if(PlayerBullets, is_dead<Projectile>);
		std::erase_if(EnemyBullets, is_dead<Projectile>);
		std::erase_if(Aliens, is_dead<Alien>);
		std::erase_if(Walls, is_dead<Wall>);

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

			// If the name is right legth and enter is pressed, exit screen by setting highscore to false and add 
			// name + score to scoreboard
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


void Game::Render()
{
	switch (gameState)
	{
	case State::STARTSCREEN:
		//Code
		DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);

		DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);


		break;
	case State::GAMEPLAY:
		//Code


		//background render LEAVE THIS AT TOP
		background.Render();

		//DrawText("GAMEPLAY", 50, 30, 40, YELLOW);
		DrawText(TextFormat("Score: %i", score), 50, 20, 40, YELLOW);
		DrawText(TextFormat("Lives: %i", player.lives), 50, 70, 40, YELLOW);

		//player rendering 
		player.Render(resources.shipTextures[player.activeTexture].get());
		//projectile rendering
		render(PlayerBullets, resources.laserTexture);
		render(EnemyBullets, resources.laserTexture);
		render(Walls, resources.barrierTexture);
		render(Aliens, resources.alienTexture);
		//TODO: Remove the for loops below.
		// wall rendering 
		//for (auto& wall : Walls)
		//{
		//	wall.Render(getTexture(resources.barrierTexture)); 
		//}

		////alien rendering  
		//for (auto& alien : Aliens)
		//{
		//	alien.Render(getTexture(resources.alienTexture));
		//}


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
				// HOVER CONFIRMIATION
				DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
			}
			else
			{
				DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
			}

			//Draw the name being typed out
			DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

			//Draw the text explaining how many characters are used
			DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), 600, 600, 20, YELLOW);

			if (mouseOnText)
			{
				if (letterCount < 9)
				{
					// Draw blinking underscore char
					if (((framesCounter / 20) % 2) == 0)
					{
						DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
					}

				}
				else
				{
					//Name needs to be shorter
					DrawText("Press BACKSPACE to delete chars...", 600, 650, 20, YELLOW);
				}
				
			}

			// Explain how to continue when name is input
			if (letterCount > 0 && letterCount < 9)
			{
				DrawText("PRESS ENTER TO CONTINUE", 600, 800, 40, YELLOW);
			}

		}
		else {
			// If no highscore or name is entered, show scoreboard and call it a day
			DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);

			DrawText("LEADERBOARD", 50, 100, 40, YELLOW);

			for (int i = 0; i < Leaderboard.size(); i++)
			{
				char* tempNameDisplay = Leaderboard[i].name.data();
				DrawText(tempNameDisplay, 50, 140 + (i * 40), 40, YELLOW);
				DrawText(TextFormat("%i", Leaderboard[i].score), 350, 140 + (i * 40), 40, YELLOW);
			}
		}

		


		break;
	default:
		//SHOULD NOT HAPPEN
		break;
	}
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

void Game::LoadLeaderboard()
{
	// CLEAR LEADERBOARD

	// OPEN FILE

	// READ DATA

	// WRITE DATA ONTO LEADERBOARD

	//CLOSE FILE
}

void Game::SaveLeaderboard()
{
	// SAVE LEADERBOARD AS ARRAY

	// OPEN FILE
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
	// CLEAR FILE

	// WRITE ARRAY DATA INTO FILE

	// CLOSE FILE
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

















/*LEGACY CODE
	// our objective is to calculate the distance between the closest point of the line to the centre of the circle,
	// and determine if it is shorter than the radius.

	// we can imagine the edges of the line and circle centre to form a triangle. calculating the height of the
	// triangle will give us the distance, if the line serves as the base

	// simplify variables
	Vector2 A = lineStart;
	Vector2 B = lineEnd;
	Vector2 C = circlePos;

	// calculate area using determinant method

	float triangle_area = fabsf(A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y)) / 2;


	// Caculate vectors AB to calculate base length
	Vector2 AB;
	AB.x = B.x - A.x;
	AB.y = B.y - A.y;

	//get the base length
	float trangle_base_length = (float)sqrt(pow(AB.x, 2) + pow(AB.y, 2));

	// we double the area to turn in into a rectangle, and then divide the base length to get the height.
	float triangle_height = (triangle_area * 2 ) / trangle_base_length;

	std::cout << triangle_area << "\n";

	if (triangle_height < circleRadius)
	{
		return true;
	}
	else
	{
		return false;
	}


	*/

