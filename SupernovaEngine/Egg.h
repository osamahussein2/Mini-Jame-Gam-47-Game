#ifndef EGG_H
#define EGG_H

#include "GameObject.h"

enum class EggType
{
	FreshEgg,
	FakeEgg
};

class Egg : public GameObject
{
public:
	Egg(Supernova::Scene* scene_, Supernova::Vector2& spawnPos_, EggType eggType_);
	~Egg();

	virtual void InitializeGameObject() override;
	virtual void UpdateGameObject() override;

	Supernova::Vector2 GetPosition() const { return position; }
	Supernova::Vector2 GetSize() const { return size; }

	bool CheckEggCollision(Supernova::Vector2 otherPos_, Supernova::Vector2 otherSize_);

	EggType GetEggType() const { return eggType; }

private:
	Supernova::Image egg;
	EggType eggType;

	static constexpr float fallSpeed = 500.0f;
};

#endif EGG_H