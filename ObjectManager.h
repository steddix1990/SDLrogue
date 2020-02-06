// w16016982	Stephen Dixon	KV6003

#ifndef __ObjectManager__
#define __ObjectManager__

#include "GameObject.h"
#include <list>
#include <algorithm> // for the clean function

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager() {}

	SDL_Rect A;
	SDL_Rect B;

	std::list<GameObject*> m_gameObjects;

	void addObject(GameObject* object);
	void update(float frameTime);
	void render();
	void processCollision();
	void clean();
	void gameOver();

	// To add?
	//void deactivateTypes(ObjectType type); // set all these types to inactive?



};
#endif /* defined(__ObjectManager__) */