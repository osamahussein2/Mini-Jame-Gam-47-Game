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

	float GetPositionY() const { return position.y; }

	bool CheckEggCollision(Supernova::Vector2 otherPos_, Supernova::Vector2 otherSize_);

private:
	Supernova::Image egg;

	static constexpr float fallSpeed = 200.0f;
};

#endif EGG_H