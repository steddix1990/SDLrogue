// w16016982	Stephen Dixon	KV6003

#ifndef __Game__
#define __Game__

#include "SDL.h"
#include "SDL_ttf.h"
#include "Vector2D.h"
#include "TextureLoader.h"
#include "ObjectManager.h"
#include <vector>
#include <iostream>
#include "Tile.h"
#include "Map.h"

class Game
{
public:

	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}

	void update();
	void render();

	void Game::set_camera();

	ObjectManager om;

	SDL_Window* window;

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool gameRunning;

	SDL_Texture* m_splat;
	SDL_Texture* m_burst;

	Vector2D m_playerPosition;
	Vector2D getPlayerPosition() { return m_playerPosition; }

	SDL_Rect m_playerRect;
	SDL_Rect& GetPlayerRect() { return m_playerRect; }

	void manageEvent(Event evt);

	float zombieTimer = 0.0f;

	static SDL_Rect camera;
	SDL_Rect getCameraRect() { return camera; }

	Map* map = new Map();

private:

	static Game* s_pInstance;
};
typedef Game TheGame;
#endif /* defined(__Game__) */