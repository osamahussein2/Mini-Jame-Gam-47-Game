#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Egg.h"

class Game
{
public:
	Game();
	~Game();

	void InitializeGame();
	void UpdateGame();

	void CleanGame();

private:
	void SpawnEggs();
	void IterateThroughEggs();

private:
	Supernova::Scene scene;

	Player player;
	std::vector<Egg*> eggs;

	float spawnEggTime;
};

#endif GAME_H