#include "Game.h"

Game::Game() : player(&scene), spawnEggTime(0.0f)
{
}

Game::~Game()
{
}

void Game::InitializeGame()
{
    // Initialize player
    player.InitializeGameObject();

    // Initialize engine members
    Supernova::Engine::setScalingMode(Supernova::Scaling::STRETCH);
    Supernova::Engine::setCanvasSize(1000, 600);
    Supernova::Engine::setScene(&scene);
    Supernova::Engine::setAutomaticTransparency(false);
}

void Game::UpdateGame()
{
    // Update player
    player.UpdateGameObject();

    // Update eggs vector
    SpawnEggs();
    IterateThroughEggs();
}

void Game::CleanGame() // Executes after the program quits running
{
    // Clean the player (if needed)
    player.CleanPlayer();

    // Release all memory that the egg elements have used up
    for (Egg* egg : eggs)
    {
        delete egg;
    }

    // Clear all the eggs off the vector
    if (!eggs.empty()) eggs.clear();
}

void Game::SpawnEggs()
{
    // Increment time to spawn eggs
    spawnEggTime += 0.016f;

    // If spawn egg time exceeds some value, spawn the eggs and reset the time back to 0
    if (spawnEggTime >= 3.0f)
    {
        eggs.push_back(new Egg(&scene, Supernova::Vector2(50.0f, 0.0f)));
        spawnEggTime = 0.0f;
    }
}

void Game::IterateThroughEggs()
{
    // Iterate through all the eggs in the element
    for (std::vector<Egg*>::iterator eggIt = eggs.begin(); eggIt != eggs.end();)
    {
        Egg* egg = *eggIt;

        // Update eggs
        egg->UpdateGameObject();

        // If the egg goes below the screen, erase it from the vector and delete the pointer element from memory
        if (egg->GetPositionY() >= 610.0f)
        {
            delete egg;
            eggIt = eggs.erase(eggIt);
        }

        else // Otherwise, just keep looping through the egg elements
        {
            ++eggIt;
        }
    }
}