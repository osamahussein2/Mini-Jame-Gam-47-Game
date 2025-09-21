#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

// Make the Player class derive from GameObject class
class Player : public GameObject
{
public:
	Player(Supernova::Scene* scene_);
	~Player();

	virtual void InitializeGameObject() override;
	virtual void UpdateGameObject() override;
	
	void CleanPlayer();

	Supernova::Vector2 GetPosition() const { return position; }
	Supernova::Vector2 GetSize() const { return size; }

	int GetPlayerScore() const { return playerScore; }
	int GetPlayerLives() const { return playerLives; }
	int GetPlayerHighscore() const { return playerHighScore; }

	void IncrementScore(int newValue_);
	void DecrementLife(int newValue_);

	void UpdateHighscore();

	void ResetStats();

private:
	void DetectPlayerInput();

private:
	static constexpr float playerMoveSpeed = 800.0f;

	Supernova::Image playerImage;

	int playerScore;
	int playerLives;

	int playerHighScore;
};

#endif PLAYER_H