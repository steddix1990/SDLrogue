// w16016982	Stephen Dixon	KV6003

#ifndef __Barrel__
#define __Barrel__

#include "GameObject.h"
#include "Sprite.h"

class Barrel : public GameObject
{
public:

	Barrel();
	~Barrel();

	// barrel functions
	void initialise(Vector2D pos);

	void update();
	void render();

	SDL_Rect& GetRect();

private:

	Sprite* m_barrelSprite;
	Vector2D m_position;

};
#endif /* defined(__Barrel__) */