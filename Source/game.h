#pragma once
#include "raylib.h"
#include <vector>
#include "Resources.h"
#include <string>
#include <string_view>
#include "../player.h"
#include "../projectile.h"
#include "../alien.h"
#include "../Wall.h"
#include "../Star.h"


enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};

struct PlayerData
{
	std::string name;
	int score;
};

struct Background
{
	std::vector<Star> Stars;
	void Initialize(int starAmount);
	void Render() const noexcept;

};

struct Game
{
	// Gamestate
	State gameState = {};

	// Score
	int score;

	//Aliens shooting
	float shootTimer = 0;

	//Aliens stuff? (idk cause liv wrote this)
	Rectangle rec = { 0, 0 ,0 ,0 }; 

	bool newHighScore = false;

	//Game Constructor
	Game() noexcept;

	void Start();
	void End();

	void Continue();

	void Update();
	void Render() noexcept;
	void RenderGamePlay() noexcept;
	void UpdateGamePlay() noexcept;

	void SpawnAliens();
	void SpawnWalls();
	void RemoveDeadEntities() noexcept;
	void CollisionForAlienBullets() noexcept;
	void CollisionForPlayerBullets() noexcept;

	bool CheckNewHighScore() noexcept;

	void InsertNewHighScore(std::string name);
	void SaveLeaderboard();

	// Entity Storage and Resources
	Resources resources{};

	Player player{};

	std::vector<Projectile> PlayerBullets;
	std::vector<Projectile> EnemyBullets;

	std::vector<Wall> Walls;

	std::vector<Alien> Aliens;

	std::vector<PlayerData> Leaderboard = { {"Player 1", 500}, {"Player 2", 400}, {"Player 3", 300}, {"Player 4", 200}, {"Player 5", 100} };
	
	Background background{};

	//TEXTBOX ENTER
	char name[9 + 1] = "\0";      //One extra space required for null terminator char '\0'
	int letterCount = 0;

	Rectangle textBox = { 600, 500, 225, 50 };
	bool mouseOnText = false;

	int framesCounter = 0;

};