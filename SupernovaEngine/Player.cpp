#include "Player.h"

Player::Player(Supernova::Scene* scene_) : GameObject(), playerImage(scene_), playerScore(0)
{
	position = Supernova::Vector2(300.0f, 550.0f);
	size = Supernova::Vector2(100.0f, 100.0f);

	playerImage.setVisible(false);
}

Player::~Player()
{
}

void Player::InitializeGameObject()
{
	playerImage.setTexture("");
	playerImage.setSize(size.x, size.y);
	playerImage.setPosition(position.x, position.y);
	playerImage.setVisible(true);
}

void Player::UpdateGameObject()
{
	DetectPlayerInput();

	playerImage.setPosition(position.x, position.y);
}

void Player::IncrementScore(int newValue_)
{
	playerScore += newValue_;
}

void Player::DetectPlayerInput()
{
	// Move left
	if (Supernova::Input::isKeyPressed(S_KEY_LEFT) || Supernova::Input::isKeyPressed(S_KEY_A))
	{
		if (position.x >= 0.0f) position.x -= playerMoveSpeed * 0.016f;
	}

	// Move right
	if (Supernova::Input::isKeyPressed(S_KEY_RIGHT) || Supernova::Input::isKeyPressed(S_KEY_D))
	{
		if (position.x <= 1000.0f - size.x) position.x += playerMoveSpeed * 0.016f;
	}
}

void Player::CleanPlayer()
{
}