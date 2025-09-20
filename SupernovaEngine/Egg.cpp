#include "Egg.h"

Egg::Egg(Supernova::Scene* scene_, Supernova::Vector2& spawnPos_, EggType eggType_) : GameObject(), egg(scene_)
{
	eggType = eggType_;

	position = spawnPos_;
	size = Supernova::Vector2(100.0f, 100.0f);

	// Set egg image settings
	egg.setTexture("");

	// Set egg's color based on type of egg
	switch (eggType)
	{
	case EggType::FreshEgg:
		egg.setColor(1.0f, 1.0f, 1.0f);
		break;

	case EggType::FakeEgg:
		egg.setColor(0.3f, 0.3f, 0.3f);
		break;
	}

	egg.setSize(size.x, size.y);
	egg.setPosition(position.x, position.y);
	egg.setVisible(true);
}

Egg::~Egg()
{
}

void Egg::InitializeGameObject()
{
}

void Egg::UpdateGameObject()
{
	// Make egg fall down
	position.y += fallSpeed * 0.016f;

	// Update egg's position
	egg.setPosition(position.x, position.y, 0.0f);
}

bool Egg::CheckEggCollision(Supernova::Vector2 otherPos_, Supernova::Vector2 otherSize_)
{
	// Return true if collision with other object is found
	if (position.x + size.x >= otherPos_.x && position.x <= otherPos_.x + otherSize_.x &&
		position.y + size.y >= otherPos_.y && position.y <= otherPos_.y + otherSize_.y)
	{
		return true;
	}

	return false;
}
