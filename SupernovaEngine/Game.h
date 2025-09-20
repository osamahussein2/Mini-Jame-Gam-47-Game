#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Egg.h"
#include "Chicken.h"
#include "PauseMenu.h"

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

private:
	Supernova::Scene scene;
	Supernova::Scene UI_scene;

	Supernova::Text playerScoreText, playerLivesText;

	Player player;

	std::vector<Chicken*> chickens;
	std::vector<Egg*> eggs;
	
	PauseMenu pauseMenu;

	float spawnChickenTime;
	float randomMaxTime;

	bool gamePaused;
	bool pauseKeyPressed;
};

#endif GAME_H