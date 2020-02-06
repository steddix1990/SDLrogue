#ifndef __Map__
#define __Map__

#include <string>
#include "SDL.h"
#include "Vector2D.h"
#include "Sprite.h"
#include "Tile.h"
#include <vector>
#include "GameObject.h"

class Map
{
public:

	Map();
	~Map() {}

	void loadMap(const char* path, int sizeX, int sizeY);
	void loadLevel(int id);
	void addTile(int id, int x, int y);
	void Map::clearTiles(){Tiles.clear();}
	void initialise(Vector2D mapPos);
	void update();
	void drawMap(SDL_Rect rect);

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	std::vector<Tile*> getTileVector() { return Tiles; }

	Vector2D mapPos;

	SDL_Rect srcRect;
	SDL_Rect destRect;

	SDL_Rect TileSrcRect;
	SDL_Rect TileDestRect;

	std::vector<Tile*> Tiles;
	std::vector<GameObject*> map_objects;

private:

	SDL_Texture* bomttom_layer;
	SDL_Texture* top_layer;

};
#endif /* defined(__Map__) */