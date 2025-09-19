#include "Chicken.h"

Chicken::Chicken(Supernova::Scene* scene_, float posY_) : chickenImage(scene_),  spawnedEgg(false), stopPoint(0.0f),
knowsStopPoint(false), stoppedMoving(false), randomizeDirection(0)
{
	randomizeDirection = rand() % 2;

	// Spawn chicken based on random direction number
	switch (randomizeDirection)
	{
	case 0: // Going right
		position = Supernova::Vector2(-50.0f, posY_);
		break;

	case 1: // Going left
		position = Supernova::Vector2(1050.0f, posY_);
		break;

	default:
		break;
	}

	size = Supernova::Vector2(100.0f, 100.0f);

	// Set chicken image settings
	chickenImage.setTexture("");
	chickenImage.setColor(1.0f, 0.0f, 0.0f);
	chickenImage.setSize(size.x, size.y);
	chickenImage.setPosition(position.x, position.y);
	chickenImage.setVisible(true);
}

Chicken::~Chicken()
{
}

void Chicken::InitializeGameObject()
{
}

void Chicken::UpdateGameObject()
{
	switch (randomizeDirection)
	{
	case 0: // Moving right
		if (!knowsStopPoint)
		{
			// Randomize the stop point
			stopPoint = 100.0f + (rand() % 700);
			knowsStopPoint = true;
		}

		else
		{
			/* Since the chicken is moving to the right, we need to examine if the chicken's position is less than the
			stop point and is moving */
			if (position.x < stopPoint && !stoppedMoving)
			{
				position.x += chickenMoveSpeed * 0.016f;
			}

			// Check if the chicken reached the stop point to stop moving until they spawned an egg
			else
			{
				if (!spawnedEgg && stoppedMoving != true) stoppedMoving = true;
				
				// Once it can move again, move it to the right
				if (!stoppedMoving) position.x += chickenMoveSpeed * 0.016f;
			}
		}

		break;

	case 1: // Moving left
		if (!knowsStopPoint)
		{
			// Randomize the stop point
			stopPoint = 870.0f - (rand() % 700);
			knowsStopPoint = true;
		}

		else
		{
			/* Since the chicken is moving to the left, we need to examine if the chicken's position is more than the
			stop point and is moving */
			if (position.x > stopPoint && !stoppedMoving)
			{
				position.x -= chickenMoveSpeed * 0.016f;
			}

			// Check if the chicken reached the stop point to stop moving until they spawned an egg
			else
			{
				if (!spawnedEgg && stoppedMoving != true) stoppedMoving = true;

				// Once it can move again, move it to the left
				if (!stoppedMoving) position.x -= chickenMoveSpeed * 0.016f;
			}
		}

		break;

	default:
		break;
	}

	// Update chicken's position
	chickenImage.setPosition(position.x, position.y);
}

void Chicken::SpawnedEgg()
{
	// Set spawned egg to true and stopped moving to false so that the chicken can move again
	if (spawnedEgg != true) spawnedEgg = true;
	if (stoppedMoving != false) stoppedMoving = false;
}