#include "Tile.h"
#include "Game.h"

Tile::Tile(int x, int y, int w, int h, int tileType)
{
	m_tileType = tileType;

	switch (m_tileType)
	{
	case 0:
		path = "assets/textures/map/tile1.png"; // stone

		break;
	case 1:
		path = "assets/textures/map/tile2.png"; // water

		break;
	case 2:
		path = "assets/textures/map/tile3.png"; // grass

		break;
	case 3:
		path = "assets/textures/map/tile4.png"; // spikes

		break;
	case 4:
		path = "assets/textures/map/tile5.png"; // wall center

		break;
	case 5:
		path = "assets/textures/map/tile6.png"; // wall top

		break;
	case 6:
		path = "assets/textures/map/tile7.png"; // wall left

		break;
	case 7:
		path = "assets/textures/map/tile8.png"; // wall right

		break;
	case 8:
		path = "assets/textures/map/tile9.png"; // wall bottom

		break;
	case 9:
		path = "assets/textures/map/tile10.png"; // wall top right

		break;
	case 10:
		path = "assets/textures/map/tile11.png"; // wall top left

		break;
	case 11:
		path = "assets/textures/map/tile12.png"; // wall bottom right

		break;
	case 12:
		path = "assets/textures/map/tile13.png"; // wall bottom left

		break;
	case 13:
		path = "assets/textures/map/tile14.png"; // void

		break;
	case 14:
		path = "assets/textures/map/tile15.png"; // wall corner top left

		break;
	case 15:
		path = "assets/textures/map/tile16.png"; // wall corner top right

		break;
	case 16:
		path = "assets/textures/map/tile17.png"; // wall corner bottom left

		break;
	case 17:
		path = "assets/textures/map/tile18.png"; 
		break;

	case 18:
		path = "assets/textures/map/tile19.png";
		break;

	case 19:
		path = "assets/textures/map/tile20.png"; // A* / shadow wall?


		break;
	default:
		break;
	}

	m_tileTexture = TextureLoader::loadTexture(path, TheGame::Instance()->renderer);

	tileSrcRect.x = tileSrcRect.y = 0;
	tileSrcRect.w = tileSrcRect.h = 32;

	tileDestRect.w = w;
	tileDestRect.h = h;

	tileDestRect.x = x;
	tileDestRect.y = y;

	active = true;
}

void Tile::update()
{
	//destRect.x = tilePos.getX();
	//destRect.y = tilePos.getY();
}

void Tile::render(SDL_Rect rect)
{
	if (tileDestRect.x + tileDestRect.w >= (rect.x) &&
		rect.x + rect.w >= (tileDestRect.x) &&
		tileDestRect.y + tileDestRect.h >= (rect.y) &&
		rect.y + rect.h >= (tileDestRect.y))
	{
		// This doesnt seem right? off set for camera rect
		SDL_RenderCopy(TheGame::Instance()->renderer, m_tileTexture, &tileSrcRect, &tileDestRect);
	}
}

int Tile::getTileType()
{
	return m_tileType;
}

SDL_Rect& Tile::GetRect()
{
	return tileDestRect;
}