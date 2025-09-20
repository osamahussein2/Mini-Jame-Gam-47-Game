#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "Supernova.h"
#include "Player.h"

class GameOver
{
public:
	GameOver(Supernova::Scene* scene_);
	~GameOver();

	void InitializeGameOver(Player& player_);
	void UpdateGameOver(Player& player_);

	void ShowGameOver();

	bool GetVisibilty() const;

private:
	void SelectGameOverOption();

	void RestartGame();

private:
	Supernova::Panel gameOverPanel;

	Supernova::Text gameOverTitle;
	Supernova::Text highscoreText;

	Supernova::Text restartText, quitText;

	int selectedOption;
	bool keySelectionPressed;

	bool textColorChanged;
};

#endif GAMEOVER_H