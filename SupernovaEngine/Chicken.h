#ifndef CHICKEN_H
#define CHICKEN_H

#include "GameObject.h"

class Chicken : public GameObject
{
public:
	Chicken(Supernova::Scene* scene_, float posY_);
	~Chicken();

	virtual void InitializeGameObject() override;
	virtual void UpdateGameObject() override;

	bool GetStoppedMoving() const { return stoppedMoving; }
	bool GetSpawnedEgg() const { return spawnedEgg; }

	void SpawnedEgg();

	int GetRandomDirection() const { return randomizeDirection; }

	Supernova::Vector2 GetPosition() const { return position; }

	int GetRandomizedPercentage() const { return randomizedPercentage; }

private:
	static constexpr float chickenMoveSpeed = 300.0f;

	Supernova::Image chickenImage;

	bool spawnedEgg;

	Supernova::Vector2 initialChickenPosition;

	int randomizeDirection;

	float stopPoint;

	bool knowsStopPoint;
	bool stoppedMoving;

	int randomizedPercentage;
};

#endif CHICKEN_H