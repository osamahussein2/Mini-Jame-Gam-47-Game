#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Egg.h"
#include "Chicken.h"

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

private:
	Supernova::Scene scene;
	Supernova::Scene UI_scene;

	Supernova::Text playerScoreText;

	Player player;

	std::vector<Chicken*> chickens;
	std::vector<Egg*> eggs;

	float spawnChickenTime;
	float randomMaxTime;
};

#endif GAME_H