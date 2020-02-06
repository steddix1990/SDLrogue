// w16016982	Stephen Dixon	KV6003

#include "Game.h"
#include "Zombie.h"
#include "Casing.h"
#include "Bit.h"
#include "Sound.h"
#include "Player.h"

Game* Game::s_pInstance = 0;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::gameRunning = false;

SDL_Rect Game::camera = {0, 0, 400, 400};

//Map* map = new Map();
Player* player = new Player();

// Used for the delay in the game loop
Uint32 frameStart;
int frameTime = 0;

const int FPS = 60; // set the FPS
const int delay = 1000 / FPS; // set the frame delay, 1ms/FPS

enum menu_states
{
	MENU = 0,
	PAUSE = 1,
	PLAY = 2,
	VIEW = 3,
	EXIT = 4,
}currentState;

void Game::manageEvent(Event evt)
{
	if (evt.type == EVENT_PLAYER_HIT)
	{
		SDL_RenderCopy(TheGame::Instance()->renderer, m_splat, &evt.sourceRect, &evt.destinationRect);
	}

	if (evt.type == EVENT_CASING)
	{
		Casing* casing = new Casing();

		casing->initialise(evt.position);
		TheGame::Instance()->om.addObject(casing);
	}

	if (evt.type == EVENT_BURST)
	{
		Sound::playZombieBurst();
		SDL_RenderCopy(TheGame::Instance()->renderer, m_burst, &evt.sourceRect, &evt.destinationRect);

		int random = rand() % 5;

		Bit* bit = new Bit();

		bit->initialise(evt.position, random);
		TheGame::Instance()->om.addObject(bit);
	}

	if (evt.type == MORE_ZOMBIES)
	{
		static const int mapWidth = 1024; // dynamic? to change based on player pos?
		static const int mapHeight = 768;

		Zombie* zombie;

		for (unsigned int i = 0; i < 2; i++)
		{
			Vector2D zombie_position;
			{
				zombie_position.setX((rand() % mapWidth));
				zombie_position.setY((rand() % mapHeight));

				zombie = new Zombie();
				zombie->initialise(zombie_position, rand() & 0 + 2);
				TheGame::Instance()->om.addObject(zombie);
			}
		}
	}
}

int main(int argc, char* args[])
{
	// Initialise all of SDLs subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised..." << std::endl;

		// Create a window for the game
		TheGame::Instance()->window = SDL_CreateWindow("SDL Zombies!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);

		if (!TheGame::Instance()->window)
		{
			printf("Could not create window: %s\n", SDL_GetError());
			return 1;
		}

		// Create a renderer for the game
		TheGame::Instance()->renderer = SDL_CreateRenderer(TheGame::Instance()->window, -1, 0);

		if (!TheGame::Instance()->renderer)
		{
			printf("Could not create renderer: %s\n", SDL_GetError());
			return 1;
		}

		SDL_SetRelativeMouseMode(SDL_TRUE);
		Game::gameRunning = true;
	}

	SDL_Texture* backgroundPauseTexture;
	backgroundPauseTexture = TextureLoader::loadTexture("assets/pause.png", TheGame::Instance()->renderer);

	// Load textures for events
	TheGame::Instance()->m_splat = TextureLoader::loadTexture("assets/textures/player/splat.png", TheGame::Instance()->renderer);
	TheGame::Instance()->m_burst = TextureLoader::loadTexture("assets/textures/zombie/burst.png", TheGame::Instance()->renderer);

	// Initialise TTF font subsystem
	TTF_Init();

	// Setup the font
	TTF_Font* font = TTF_OpenFont("arial.ttf", 24);
	SDL_Color color = { 255, 255, 255 };

	// Create a surface and texture for the menu text
	SDL_Surface* menu_surface = TTF_RenderText_Solid(font, "Press Enter to Play!", color);
	SDL_Texture* menu_texture = SDL_CreateTextureFromSurface(TheGame::Instance()->renderer, menu_surface);

	// Create a surface and texture for the pause text
	SDL_Surface* pause_surface = TTF_RenderText_Solid(font, "Game Paused", color);
	SDL_Texture* pause_texture = SDL_CreateTextureFromSurface(TheGame::Instance()->renderer, pause_surface);

	// Setup a rect for the menu text
	SDL_Rect menu_rect;
	menu_rect = {0,0,256,50};

	// Setup a rect for the pause text
	SDL_Rect pause_rect;
	pause_rect = { 0,0,128,50 };

	// Initialise sounds
	Sound::init();

	// Initialise the player
	player->initialise(Vector2D(512, 384));

	// Initialise the map
	TheGame::Instance()->map->initialise(Vector2D(512, 384));
	TheGame::Instance()->map->loadLevel(1);

	// Start the game in the MENU state
	currentState = MENU;

	// Start the game
	Sound::playGameStart();

	// Enter the game loop
	while (Game::gameRunning == true)
	{
		SDL_PollEvent(&TheGame::event);

		if (TheGame::event.type == SDL_KEYDOWN)
		{
			// Switch case upon keydown
			switch (TheGame::event.key.keysym.sym)
			{
			case SDLK_p:
				currentState = PAUSE;
				break;

			case SDLK_RETURN:
				currentState = PLAY;
				break;

			case SDLK_ESCAPE:
				currentState = EXIT;
				break;

			default:
				break;
			}
		}

		// The game states
		if (currentState == MENU)
		{
			SDL_RenderCopy(TheGame::Instance()->renderer, menu_texture, NULL, &menu_rect);
		}

		if (currentState == PLAY)
		{
			TheGame::Instance()->update();
			TheGame::Instance()->render();
		}

		if (currentState == PAUSE)
		{
			SDL_RenderCopy(TheGame::Instance()->renderer, backgroundPauseTexture, NULL, NULL);
			SDL_RenderCopy(TheGame::Instance()->renderer, pause_texture, NULL, &pause_rect);
		}

		if (currentState == EXIT)
		{
			// Minimize the window to see results
			SDL_MinimizeWindow(TheGame::Instance()->window);

			std::cout << "Exiting..." << std::endl;

			// Delay a bit
			SDL_Delay(3000);

			// Destroy the objects
			TheGame::Instance()->om.gameOver();

			// Destroy the window, renderer
			SDL_DestroyWindow(TheGame::Instance()->window);
			SDL_DestroyRenderer(TheGame::Instance()->renderer);

			// Destroy everything else
			SDL_Quit();

			// End the program
			return 0;
		}

		SDL_RenderPresent(TheGame::Instance()->renderer);
	}

	return 0;
}

void Game::update()
{
	frameStart = SDL_GetTicks();
	frameTime = SDL_GetTicks() - frameStart;

	if (delay > frameTime) { SDL_Delay(delay - frameTime); }

	SDL_RenderClear(TheGame::Instance()->renderer);

	TheGame::Instance()->m_playerRect = player->GetRect();
	TheGame::Instance()->set_camera();

	map->update();

	TheGame::Instance()->om.update(frameTime);
	TheGame::Instance()->om.processCollision();
	TheGame::Instance()->om.clean();

	player->update();
	player->tileCollision(map->getTileVector());
	player->render();

	TheGame::Instance()->m_playerPosition = player->GetPosition();

	if (TheGame::Instance()->zombieTimer == 0) {
		Event evt;
		evt.type = MORE_ZOMBIES;
		TheGame::Instance()->manageEvent(evt);
		TheGame::Instance()->zombieTimer = 10.0f;
	}

	TheGame::Instance()->zombieTimer -= 0.05f;
}

void Game::render()
{
	map->drawMap(TheGame::Instance()->camera);
	TheGame::Instance()->om.render();
	player->render();
}

void Game::set_camera()
{
	camera.x = (TheGame::Instance()->GetPlayerRect().x + 64) - 464 / 2;
	camera.y = (TheGame::Instance()->GetPlayerRect().y + 64) - 432 / 2;

	//if (camera.x < 0)
	//	camera.x = 0;
	//if (camera.y < 0)
	//	camera.y = 0;
	//if (camera.x > camera.w)
	//	camera.x = camera.w;
	//if (camera.y > camera.h)
	//	camera.y = camera.h;

	//std::cout << "Camera Settings: " << " X: " << camera.x << " Y: " << camera.y << std::endl;
	//std::cout << "Player Positions: " << " X: " << TheGame::Instance()->m_playerPosition.x << " Y: " << TheGame::Instance()->m_playerPosition.y << std::endl;
}