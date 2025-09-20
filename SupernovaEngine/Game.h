#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Egg.h"
#include "Chicken.h"
#include "PauseMenu.h"
#include "GameOver.h"

class Game
{
public:
	Game();
	~Game();

	void InitializeGame();
	void UpdateGame();

	void CleanGame();

private:
	void UpdateChickens();
	void IterateThroughEggs();

	void SpawnChickens();

	void HandleGameInput();

	void ResetGame();

	void ExecuteGameOverScreen();

private:
	Supernova::Scene scene;
	Supernova::Scene UI_scene;

	Supernova::Text playerScoreText, playerLivesText;

	Player player;

	std::vector<Chicken*> chickens;
	std::vector<Egg*> eggs;
	
	PauseMenu pauseMenu;
	GameOver gameOver;

	float spawnChickenTime;
	float randomMaxTime;

	bool gamePaused;
	bool pauseKeyPressed;

	bool isGameOver;
};

#endif GAME_H