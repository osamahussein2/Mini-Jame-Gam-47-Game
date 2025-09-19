#include "Game.h"

Game::Game() : player(&scene)
{
}

Game::~Game()
{
}

void Game::InitializeGame()
{
    player.InitializeGameObject();

    Supernova::Engine::setScalingMode(Supernova::Scaling::STRETCH);
    Supernova::Engine::setCanvasSize(1000, 600);
    Supernova::Engine::setScene(&scene);
    Supernova::Engine::setAutomaticTransparency(false);
}

void Game::UpdateGame()
{
    player.UpdateGameObject();
}

void Game::CleanGame()
{
    player.CleanPlayer();
}