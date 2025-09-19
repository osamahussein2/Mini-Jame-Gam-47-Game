#include "Game.h"

void update();
void quit();

Game game;

void init()
{
    game.InitializeGame();

    Supernova::Engine::onUpdate = update;
    Supernova::Engine::onShutdown = quit;
}

void update()
{
    game.UpdateGame();
}

void quit()
{
    game.CleanGame();
}