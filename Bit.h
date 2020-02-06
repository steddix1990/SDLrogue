// w16016982	Stephen Dixon	KV6003

#ifndef __Bit__
#define __Bit__

#include "GameObject.h"
#include "TextureLoader.h"
#include "Game.h"

class Bit : public GameObject
{
public:

	Bit();
	virtual ~Bit() {}

	void initialise(Vector2D position, int type);
	void update();
	void render();

	SDL_Rect& Bit::GetRect();

private:

	SDL_Texture* m_bitTexture;
};
#endif /* defined(__Bit__) */