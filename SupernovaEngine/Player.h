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

	void IncrementScore(int newValue_);

private:
	void DetectPlayerInput();

private:
	static constexpr float playerMoveSpeed = 350.0f;

	Supernova::Image playerImage;

	int playerScore;
};

#endif PLAYER_H