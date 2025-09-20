#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "Supernova.h"

class PauseMenu
{
public:
	PauseMenu(Supernova::Scene* scene_);
	~PauseMenu();

	void InitializePauseMenu();
	void UpdatePauseMenu();

	void PauseGame();
	void ResumeGame();

	bool GetVisibilty() const;

	void ResetSelectedOption();

private:
	void SelectPauseOption();

private:
	Supernova::Panel pausePanel;

	Supernova::Text pauseTitle;

	Supernova::Text resumeText, quitText;

	int selectedOption;
	bool keySelectionPressed;

	bool textColorChanged;
};

#endif PAUSEMENU_H