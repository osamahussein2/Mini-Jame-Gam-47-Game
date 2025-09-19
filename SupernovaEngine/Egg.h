#ifndef EGG_H
#define EGG_H

#include "GameObject.h"

class Egg : public GameObject
{
public:
	Egg(Supernova::Scene* scene_, Supernova::Vector2& spawnPos_);
	~Egg();

	virtual void InitializeGameObject() override;
	virtual void UpdateGameObject() override;

	Supernova::Vector2 GetPosition() const { return position; }
	Supernova::Vector2 GetSize() const { return size; }

	bool CheckEggCollision(Supernova::Vector2 otherPos_, Supernova::Vector2 otherSize_);

private:
	Supernova::Image egg;

	static constexpr float fallSpeed = 500.0f;
};

#endif EGG_H