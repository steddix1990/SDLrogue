// w16016982	Stephen Dixon	KV6003

#ifndef __Casing__
#define __Casing__

#include "GameObject.h"
#include "Game.h"
#include "TextureLoader.h"

class Casing : public GameObject
{
public:
	Casing();
	virtual ~Casing() {}

	void initialise(Vector2D position);
	void update();
	void render();

	SDL_Rect& Casing::GetRect();

private:

	SDL_Texture* m_casingTexture;
};
#endif /* defined(__Casing__) */