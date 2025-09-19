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

private:
	void DetectPlayerInput();

private:
	static constexpr float playerMoveSpeed = 350.0f;

	Supernova::Image playerImage;
};

#endif PLAYER_H