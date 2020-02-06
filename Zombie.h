// w16016982	Stephen Dixon	KV6003

///
/*
	Zombies with move speed buffs? increase move speed of 1 zombie class for a few seconds(come kind of rush)
		Derement a counter in the zombies class for when it can rush again
	Zombies with guns? that they can drop and you can pick up?
*/


#ifndef __Zombie__
#define __Zombie__

#include "GameObject.h"
#include "Game.h"
#include "Sound.h"
#include "Sprite.h"

class Zombie : public GameObject
{
public:

	Zombie();
	virtual ~Zombie() {}

	void initialise(Vector2D position, int type);
	void update();
	void render();
	void processCollision(GameObject* object);

	SDL_Rect& Zombie::GetRect();

private:

	int m_speed = 110;
	
	Vector2D m_zVelocity;
	Vector2D m_zAccelleration;

	SDL_Rect srcRect;
	SDL_Rect destRect;

	SDL_Texture* m_splat;

	Sprite* zombieIdleSprite;
	Sprite* zombieWalkingLeftSprite;
	Sprite* zombieWalkingRightSprite;
	Sprite* zombieWalkingUpSprite;
	Sprite* zombieWalkingDownSprite;
};
#endif /* defined(__Zombie__) */