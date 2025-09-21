#include "PauseMenu.h"
#include "sokol_app.h"

PauseMenu::PauseMenu(Supernova::Scene* scene_) : pausePanel(scene_), pauseTitle(scene_), resumeText(scene_), 
quitText(scene_), selectedOption(0), keySelectionPressed(false), textColorChanged(false)
{
    pausePanel.setVisible(false);
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::InitializePauseMenu()
{
    pausePanel.setAnchorPreset(Supernova::AnchorPreset::CENTER_TOP);
    pausePanel.setSize(430, 600);
    pausePanel.setColor(0.0f, 0.0f, 0.0f);
    pausePanel.setAlpha(0.5f);
    pausePanel.setCanResize(false);
    pausePanel.addChild(&pauseTitle);
    pausePanel.addChild(&resumeText);
    pausePanel.addChild(&quitText);

    pauseTitle.setAnchorPreset(Supernova::AnchorPreset::CENTER_TOP);
    pauseTitle.setPositionYOffset(10.0f);
    pauseTitle.setText("Game Paused");
    pauseTitle.setColor(1.0f, 1.0f, 1.0f);
    pauseTitle.setFontSize(50.0f);

    resumeText.setAnchorPreset(Supernova::AnchorPreset::CENTER);
    resumeText.setText("Resume");
    resumeText.setColor(1.0f, 1.0f, 1.0f);
    resumeText.setFontSize(30.0f);

    quitText.setAnchorPreset(Supernova::AnchorPreset::CENTER);
    quitText.setPositionYOffset(50.0f);
    quitText.setText("Quit");
    quitText.setColor(1.0f, 1.0f, 1.0f);
    quitText.setFontSize(30.0f);
}

void PauseMenu::UpdatePauseMenu()
{
    SelectPauseOption();

    switch (selectedOption)
    {
    case 0:

        if (!textColorChanged)
        {
            resumeText.setColor(1.0f, 0.0f, 0.0f);
            quitText.setColor(1.0f, 1.0f, 1.0f);

            textColorChanged = true;
        }

        if (Supernova::Input::isKeyPressed(S_KEY_ENTER))
        {
            ResumeGame();
        }

        break;

    case 1:

        if (!textColorChanged)
        {
            resumeText.setColor(1.0f, 1.0f, 1.0f);
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

void PauseMenu::PauseGame()
{
    pausePanel.setVisible(true);
}

void PauseMenu::ResumeGame()
{
    pausePanel.setVisible(false);
}

bool PauseMenu::GetVisibilty() const
{
    return pausePanel.isVisible();
}

void PauseMenu::ResetSelectedOption()
{
    // Reset pause menu back to default states
    textColorChanged = false;
    selectedOption = 0;
}

void PauseMenu::SelectPauseOption()
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