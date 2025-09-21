#include "Game.h"

Game::Game() : player(&scene), spawnChickenTime(0.0f), randomMaxTime(0.0f), playerScoreText(&UI_scene), gamePaused(false),
pauseMenu(&UI_scene), pauseKeyPressed(false), playerLivesText(&UI_scene), gameOver(&UI_scene), isGameOver(false), 
gameMusic(&scene), eggCollectSounds{ &scene, &scene }, worldBackground(&scene), loadingImage(&UI_scene)
{
    randomMaxTime = 1.0f + (rand() % 2);
}

Game::~Game()
{
}

void Game::InitializeGame()
{
    // Initialize world background
    worldBackground.setTexture("WorldBackground.png");
    worldBackground.setPosition(0.0f, 0.0f);
    worldBackground.setSize(1000.0f, 600.0f);
    worldBackground.setVisible(false);

    // Initialize loading image
    loadingImage.setTexture("LoadingImage.png");
    loadingImage.setPosition(3.0f, 3.0f);
    loadingImage.setSize(4, 3);
    loadingImage.setVisible(true);

    // Initialize player
    player.InitializeGameObject();

    playerScoreText.setAnchorPreset(Supernova::AnchorPreset::TOP_LEFT);
    playerScoreText.setPositionXOffset(20.0f);
    playerScoreText.setPositionYOffset(20.0f);
    playerScoreText.setText("Score: " + std::to_string(player.GetPlayerScore()));
    playerScoreText.setColor(0.0f, 0.0f, 0.0f);
    playerScoreText.setFontSize(25.0f);
    playerScoreText.setVisible(true);

    playerLivesText.setAnchorPreset(Supernova::AnchorPreset::TOP_LEFT);
    playerLivesText.setPositionXOffset(20.0f);
    playerLivesText.setPositionYOffset(50.0f);
    playerLivesText.setText("Lives: " + std::to_string(player.GetPlayerLives()));
    playerLivesText.setColor(0.0f, 0.0f, 0.0f);
    playerLivesText.setFontSize(25.0f);
    playerLivesText.setVisible(true);

    pauseMenu.InitializePauseMenu();
    gameOver.InitializeGameOver(player);

    // Initialize game music
    gameMusic.loadAudio("EggBasketGame OZONE MASTER.wav");
    gameMusic.setSound3D(false);
    gameMusic.setLopping(true);
    gameMusic.play();

    // Initialize egg collect sounds
    eggCollectSounds[0].loadAudio("CollectEgg.mp3");
    eggCollectSounds[1].loadAudio("FakeEgg.mp3");

    for (Supernova::Audio& eggCollectSound : eggCollectSounds)
    {
        eggCollectSound.setSound3D(false);
        eggCollectSound.setLopping(false);
    }

    // Initialize engine members
    Supernova::Engine::setScalingMode(Supernova::Scaling::STRETCH);
    Supernova::Engine::setCanvasSize(1000, 600);
    Supernova::Engine::setScene(&scene);
    Supernova::Engine::addSceneLayer(&UI_scene);
    Supernova::Engine::setAutomaticTransparency(false);
}

void Game::UpdateGame()
{
    // Make loading image invisible once loading is done
    if (loadingImage.isVisible()) loadingImage.setVisible(false);

    // Make world background show up
    if (!worldBackground.isVisible()) worldBackground.setVisible(true);

    // When the game is NOT paused
    if (!gamePaused)
    {
        if (player.GetPlayerLives() > 0)
        {
            // Update player
            player.UpdateGameObject();

            // Update player's score
            if (playerScoreText.getText() != "Score: " + std::to_string(player.GetPlayerScore()))
            {
                playerScoreText.setText("Score: " + std::to_string(player.GetPlayerScore()));
            }

            // Update player's life value
            if (playerLivesText.getText() != "Lives: " + std::to_string(player.GetPlayerLives()))
            {
                playerLivesText.setText("Lives: " + std::to_string(player.GetPlayerLives()));
            }

            // Update chickens vector
            SpawnChickens();
            UpdateChickens();

            // Update eggs vector
            IterateThroughEggs();

            // Check for game related input
            HandleGameInput();
        }

        // Player has no lives left
        else
        {
            // Trigger game over
            ExecuteGameOverScreen();
        }
    }

    // Otherwise, when the game IS paused
    else
    {
        // Check for game related input
        HandleGameInput();

        // Update pause menu
        pauseMenu.UpdatePauseMenu();
    }

    // Set game paused to false whenever pause menu isn't visible
    if (!pauseMenu.GetVisibilty() && gamePaused)
    {
        pauseMenu.ResetSelectedOption();
        gamePaused = false;
    }
}

void Game::CleanGame() // Executes after the program quits running
{
    // Destroy scenes
    scene.destroy();
    UI_scene.destroy();

    gameMusic.destroyAudio();

    // Destroy the egg collect sounds audio
    eggCollectSounds[0].destroyAudio();
    eggCollectSounds[1].destroyAudio();

    // Clean the player (if needed)
    player.CleanPlayer();

    // Release all memory that the egg elements have used up
    for (Egg* egg : eggs)
    {
        delete egg;
    }

    // Release all memory that the chicken elements have used up
    for (Chicken* chicken : chickens)
    {
        delete chicken;
    }

    // Clear all elements of the vector
    if (!eggs.empty()) eggs.clear();
    if (!chickens.empty()) chickens.clear();
}

void Game::UpdateChickens()
{
    for (Chicken* chicken : chickens)
    {
        // If the chicken stops moving and hasn't spawned an egg, spawn an egg
        if (chicken->GetStoppedMoving() && !chicken->GetSpawnedEgg())
        {
            // If the percentage is between 0-60
            if (chicken->GetRandomizedPercentage() <= 60)
            {
                // Spawn a fresh egg at the center point of the chicken
                eggs.push_back(new Egg(&scene, Supernova::Vector2(chicken->GetPosition().x + (chicken->GetSize().x / 2.0f), 
                    chicken->GetPosition().y + (chicken->GetSize().y / 2.0f)), EggType::FreshEgg));

                // This just sets spawned egg for the chicken to true and re-enables their movement
                chicken->SpawnedEgg();
            }

            // Otherwise, the percentage is greater than 60 (this half is meant for 40% chance)
            else
            {
                // Spawn a fake egg at the center point of the chicken
                eggs.push_back(new Egg(&scene, Supernova::Vector2(chicken->GetPosition().x + (chicken->GetSize().x / 2.0f),
                    chicken->GetPosition().y + (chicken->GetSize().y / 2.0f)), EggType::FakeEgg));

                // This just sets spawned egg for the chicken to true and re-enables their movement
                chicken->SpawnedEgg();
            }
        }
    }

    // Iterate through all the chickens in the element
    for (std::vector<Chicken*>::iterator chickenIt = chickens.begin(); chickenIt != chickens.end();)
    {
        Chicken* chicken = *chickenIt;

        // Update chickens
        chicken->UpdateGameObject();

        /* If the chicken goes offscreen based on their random direction value, erase it from the vector and delete the
        pointer element from memory */
        if (chicken->GetPosition().x >= 1010.0f && chicken->GetRandomDirection() == 0 ||
            chicken->GetPosition().x <= -110.0f && chicken->GetRandomDirection() == 1)
        {
            delete chicken;
            chickenIt = chickens.erase(chickenIt);
        }

        else // Otherwise, just keep looping through the egg elements
        {
            ++chickenIt;
        }
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
        if (egg->GetPosition().y >= 610.0f)
        {
            delete egg;
            eggIt = eggs.erase(eggIt);
        }

        // If the egg collides with the player, also erase it from the vector and delete the pointer element from memory
        else if (egg->CheckEggCollision(player.GetPosition(), player.GetSize()))
        {
            // Only increment the score if the fresh egg is on top of the basket upon collision
            if (egg->GetPosition().y + (egg->GetSize().y / 1.3f) <= player.GetPosition().y && 
                egg->GetEggType() == EggType::FreshEgg)
            {
                eggCollectSounds[0].play(); // Play collected fresh egg sound

                player.IncrementScore(10);
            }

            // Only decrement player's life if the fake egg is on top of the basket upon collision
            else if (egg->GetPosition().y + (egg->GetSize().y / 1.3f) <= player.GetPosition().y &&
                egg->GetEggType() == EggType::FakeEgg)
            {
                eggCollectSounds[1].play(); // Play collected fake egg sound

                player.DecrementLife(1);
            }

            delete egg;
            eggIt = eggs.erase(eggIt);
        }

        else // Otherwise, just keep looping through the egg elements
        {
            ++eggIt;
        }
    }
}

void Game::SpawnChickens()
{
    // Increment time to spawn chickens
    spawnChickenTime += 0.016f;

    // If spawn chicken time exceeds some value, spawn the chicken
    if (spawnChickenTime >= randomMaxTime)
    {
        chickens.push_back(new Chicken(&scene, 0.0f));

        // Also randomize the max timer again to spawn more chickens and reset the time back to 0
        randomMaxTime = 1.0f + (rand() % 2);
        spawnChickenTime = 0.0f;
    }
}

void Game::HandleGameInput()
{
    // Pause the game
    if (Supernova::Input::isKeyPressed(S_KEY_ESCAPE) && !gamePaused && !pauseKeyPressed)
    {
        pauseMenu.PauseGame();
        gamePaused = true;

        pauseKeyPressed = true;
    }

    // Resume game
    if (Supernova::Input::isKeyPressed(S_KEY_ESCAPE) && gamePaused && !pauseKeyPressed)
    {
        pauseMenu.ResumeGame();

        pauseKeyPressed = true;
    }

    // Set bool back to false to be able to press ESCAPE again
    else if (!Supernova::Input::isKeyPressed(S_KEY_ESCAPE) && pauseKeyPressed)
    {
        pauseKeyPressed = false;
    }
}

void Game::ResetGame()
{
    // Reset the entire game back to starting values
    player.ResetStats();

    spawnChickenTime = 0.0f;
}

void Game::ExecuteGameOverScreen()
{
    // If game over isn't set to true, update the player's highscore (if necessary) and show the game over screen
    if (!isGameOver)
    {
        // Hide the pause menu if it isn't hidden already
        if (pauseMenu.GetVisibilty()) pauseMenu.ResumeGame();

        StopGameMusic();

        // Update player's life value
        playerLivesText.setText("Lives: " + std::to_string(player.GetPlayerLives()));

        // Set player's score if needed
        if (playerScoreText.getText() != "Score: " + std::to_string(player.GetPlayerScore()))
        {
            playerScoreText.setText("Score: " + std::to_string(player.GetPlayerScore()));
        }

        // Release all memory that the egg elements have used up
        for (Egg* egg : eggs)
        {
            delete egg;
        }

        // Release all memory that the chicken elements have used up
        for (Chicken* chicken : chickens)
        {
            delete chicken;
        }

        // Clear all elements of the vector
        if (!eggs.empty()) eggs.clear();
        if (!chickens.empty()) chickens.clear();

        player.UpdateHighscore();
        gameOver.ShowGameOver();

        isGameOver = true; // Set game over to true once game over screen is visible
    }

    // If game over is true, update game over
    else if (isGameOver)
    {
        gameOver.UpdateGameOver(player);

        // Also we want to reset the game and set game over back to false once game over is no longer visible
        if (!gameOver.GetVisibilty())
        {
            gameMusic.play();

            ResetGame();
            isGameOver = false;
        }
    }
}

void Game::StopGameMusic()
{
    // Stop playing music
    gameMusic.stop();
}
