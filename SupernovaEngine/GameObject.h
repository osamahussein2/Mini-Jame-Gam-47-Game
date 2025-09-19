#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Supernova.h"

// Abstract base class of GameObject
class GameObject
{
protected:
	GameObject() {}
	virtual ~GameObject() {}

	virtual void InitializeGameObject() = 0;
	virtual void UpdateGameObject() = 0;
};

#endif GAMEOBJECT_H