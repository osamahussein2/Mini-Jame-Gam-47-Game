#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game
{
public:
	Game();
	~Game();

	void InitializeGame();
	void UpdateGame();

	void CleanGame();

private:
	Supernova::Scene scene;

	Player player;
};

#endif GAME_H