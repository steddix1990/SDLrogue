#include "Map.h"
#include "Game.h"
#include "Barrel.h"
#include <fstream>

Map::Map()
{}

void Map::initialise(Vector2D mapPos)
{
	bomttom_layer = TextureLoader::loadTexture("assets/textures/map/bottom_layer.png", TheGame::Instance()->renderer);
	top_layer = TextureLoader::loadTexture("assets/textures/map/top_layer.png", TheGame::Instance()->renderer);

	srcRect.x = srcRect.y = 0;
	destRect.x = destRect.y = 0;
	srcRect.w = destRect.w = 1920;
	srcRect.h = destRect.h = 1080;

	Tiles.clear();

	// Test some barrels / items
	Barrel* barrel = new Barrel();
	barrel->initialise(Vector2D(300, 150));
	TheGame::Instance()->om.addObject(barrel);

	map_objects.push_back(barrel);
}

void Map::loadMap(const char* path, int sizeX, int sizeY)
{
	int tile;
	std::fstream mapFile;
	mapFile.open(path);

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile >> tile;
			addTile(tile, x * 32, y * 32);
			mapFile.ignore();
		}
	}

	mapFile.close();
}

void Map::loadLevel(int id)
{
	switch (id)
	{
	case 1:
		loadMap("assets/map_files/p16x161.map", 16, 16);

		break;
	case 2:
		loadMap("assets/map_files/p16x162.map", 16, 16);

		break;
	case 3:
		loadMap("assets/map_files/p16x163.map", 16, 16);

		break;
	case 4:
		loadMap("assets/map_files/p16x164.map", 16, 16);

		break;
	case 5:
		loadMap("assets/map_files/p16x165.map", 16, 16);

		break;
	default:
		break;
	}
}

void Map::addTile(int id, int x, int y)
{
	Tile* tile = new Tile(x, y, 32, 32, id);
	Tiles.push_back(tile);
}

void Map::update()
{
	for (auto &it : Tiles)
	{
		it->update();
	}
}

void Map::drawMap(SDL_Rect rect)
{
	//SDL_RenderCopy(TheGame::Instance()->renderer, bomttom_layer, &Game::camera, &Game::camera);
	//SDL_RenderCopy(TheGame::Instance()->renderer, top_layer, &Game::camera, &Game::camera);

	for (auto &it : Tiles)
	{
		it->render(rect);
	}
}

void Map::moveUp()
{
	destRect.y = destRect.y + 2;
	
	for (auto &it : Tiles)
	{
		it->tileDestRect.y++;
	}

	for (auto &it : map_objects)
	{
		it->destRect.y++;
	}
}

void Map::moveDown()
{
	destRect.y = destRect.y - 2;

	for (auto &it : Tiles)
	{
		it->tileDestRect.y--;
	}

	for (auto &it : map_objects)
	{
		it->destRect.y--;
	}
}

void Map::moveLeft()
{
	destRect.x = destRect.x + 2;

	for (auto &it : Tiles)
	{
		it->tileDestRect.x++;
	}

	for (auto &it : map_objects)
	{
		it->destRect.x++;
	}
}

void Map::moveRight()
{
	destRect.x = destRect.x - 2;

	for (auto &it : Tiles)
	{
		it->tileDestRect.x--;
	}

	for (auto &it : map_objects)
	{
		it->destRect.x--;
	}
}