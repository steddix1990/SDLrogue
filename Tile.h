#ifndef __Tile__
#define __Tile__

#include "SDL.h"
#include "Vector2D.h"

class Tile
{
public:
	//Initializes position and type
	Tile(int x, int y, int w, int h, int tileType);

	//Update the tiles position
	void update();

	//Shows the tile
	void render(SDL_Rect rect);
	//void render(SDL_Rect& camera);

	//Get the tile type
	int getTileType();

	//Box collision detector
	//bool checkCollision(SDL_Rect a, SDL_Rect b);

	//The attributes of the tile

	SDL_Rect tileSrcRect;
	SDL_Rect tileDestRect;

	const char* path;

	bool active = false;



private:

	//The tile type
	int m_tileType;

	//The tiles texture
	SDL_Texture* m_tileTexture;

	//Get rect
	SDL_Rect& Tile::GetRect();
};
#endif /* defined(__Tile__) */