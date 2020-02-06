// w16016982	Stephen Dixon	KV6003

#ifndef __GameObject__
#define __GameObject__

#include "SDL.h"
#include "Vector2D.h"
#include "ObjectTypes.h"
#include "Events.h"
#include <iostream>

class GameObject abstract
{
public:

	bool active = true;
	const ObjectType TYPE;

	explicit GameObject(ObjectType type);
	virtual ~GameObject() {}

	virtual void update() = 0;
	virtual void render();
	virtual void processCollision(GameObject* object);
	virtual SDL_Rect& GetRect() = 0;

	Vector2D GetPosition() { return m_position; }

	bool isActive() { return active; }
	ObjectType GetType() const;

	SDL_Rect srcRect;
	SDL_Rect destRect;

	virtual void clean();

protected:

	float m_health;
	float m_frameTime = 0.01667f;

	int m_width;
	int m_height;

	Vector2D m_position;
};
#endif /* defined(__GameObject__) */