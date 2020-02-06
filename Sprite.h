#ifndef __Sprite__
#define __Sprite__

#include "SDL_image.h"

class Sprite
{
public:

	Sprite(const char* fileName, int frames, int speed, int w, int h);

	void update();
	void renderSprite();
	void play(SDL_Rect rect);

	// used to load single use textures /// MAY BE REPLACED
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* renderer);

	virtual SDL_Rect& GetRect();

	SDL_Rect srcRect;
	SDL_Rect destRect;

	bool visible = true;

private:
	int m_frames = 0;
	int m_speed = 100;

	SDL_Texture* sprite;
};
#endif /* defined(__Sprite__) */