#include "GameOver.h"
#include "sokol_app.h"

GameOver::GameOver(Supernova::Scene* scene_) : gameOverPanel(scene_), gameOverTitle(scene_), 
restartText(scene_), quitText(scene_), selectedOption(0), keySelectionPressed(false), textColorChanged(false),
highscoreText(scene_)
{
	gameOverPanel.setVisible(false);
}

GameOver::~GameOver()
{
}

void GameOver::InitializeGameOver(Player& player_)
{
    gameOverPanel.setAnchorPreset(Supernova::AnchorPreset::CENTER_TOP);
    gameOverPanel.setSize(430, 600);
    gameOverPanel.setColor(0.0f, 0.0f, 0.0f);
    gameOverPanel.setAlpha(0.5f);
    gameOverPanel.setCanResize(false);
    gameOverPanel.addChild(&gameOverTitle);
    gameOverPanel.addChild(&highscoreText);
    gameOverPanel.addChild(&restartText);
    gameOverPanel.addChild(&quitText);

    gameOverTitle.setAnchorPreset(Supernova::AnchorPreset::CENTER_TOP);
    gameOverTitle.setPositionYOffset(10.0f);
    gameOverTitle.setText("Game Over");
    gameOverTitle.setColor(1.0f, 1.0f, 1.0f);
    gameOverTitle.setFontSize(50.0f);

    highscoreText.setAnchorPreset(Supernova::AnchorPreset::CENTER);
    highscoreText.setPositionYOffset(-100.0f);
    highscoreText.setText("Highscore: " + std::to_string(player_.GetPlayerHighscore()));
    highscoreText.setColor(1.0f, 0.5f, 0.0f);
    highscoreText.setFontSize(40.0f);

    restartText.setAnchorPreset(Supernova::AnchorPreset::CENTER);
    restartText.setText("Restart");
    restartText.setColor(1.0f, 1.0f, 1.0f);
    restartText.setFontSize(30.0f);

    quitText.setAnchorPreset(Supernova::AnchorPreset::CENTER);
    quitText.setPositionYOffset(50.0f);
    quitText.setText("Quit");
    quitText.setColor(1.0f, 1.0f, 1.0f);
    quitText.setFontSize(30.0f);
}

void GameOver::UpdateGameOver(Player& player_)
{
    SelectGameOverOption();

    // Update player's high score
    if (highscoreText.getText() != "Highscore: " + std::to_string(player_.GetPlayerHighscore()))
    {
        highscoreText.setText("Highscore: " + std::to_string(player_.GetPlayerHighscore()));
    }

    switch (selectedOption)
    {
    case 0:

        if (!textColorChanged)
        {
            restartText.setColor(1.0f, 0.0f, 0.0f);
            quitText.setColor(1.0f, 1.0f, 1.0f);

            textColorChanged = true;
        }

        if (Supernova::Input::isKeyPressed(S_KEY_ENTER))
        {
            RestartGame();
        }

        break;

    case 1:

        if (!textColorChanged)
        {
            restartText.setColor(1.0f, 1.0f, 1.0f);
            quitText.setColor(1.0f, 0.0f, 0.0f);

            textColorChanged = true;
        }

        if (Supernova::Input::isKeyPressed(S_KEY_ENTER))
        {
            sapp_request_quit();
        }

        break;

    default:
        break;
    }
}

void GameOver::RestartGame()
{
    gameOverPanel.setVisible(false);
}

void GameOver::ShowGameOver()
{
    gameOverPanel.setVisible(true);
}

bool GameOver::GetVisibilty() const
{
    return gameOverPanel.isVisible();
}

void GameOver::SelectGameOverOption()
{
    // Go down the selected options
    if (Supernova::Input::isKeyPressed(S_KEY_DOWN) && !keySelectionPressed && selectedOption < 1)
    {
        selectedOption += 1;
        textColorChanged = false;
        keySelectionPressed = true;
    }

    // Go up the selected options
    else if (Supernova::Input::isKeyPressed(S_KEY_UP) && !keySelectionPressed && selectedOption > 0)
    {
        selectedOption -= 1;
        textColorChanged = false;
        keySelectionPressed = true;
    }

    // Set key selection pressed to false so that the player can select options again
    else if (!Supernova::Input::isKeyPressed(S_KEY_DOWN) && !Supernova::Input::isKeyPressed(S_KEY_UP) &&
        keySelectionPressed)
    {
        keySelectionPressed = false;
    }
}
