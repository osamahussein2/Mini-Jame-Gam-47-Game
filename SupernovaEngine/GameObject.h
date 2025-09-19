#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Supernova.h"

// Abstract base class of GameObject
class GameObject
{
protected:
	GameObject() : position(), size() {}
	virtual ~GameObject() {}

	virtual void InitializeGameObject() = 0;
	virtual void UpdateGameObject() = 0;
	
	Supernova::Vector2 position;
	Supernova::Vector2 size;
};

#endif GAMEOBJECT_H