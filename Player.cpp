// w16016982	Stephen Dixon	KV6003

/// NEW TEXTURES 128x128
/// STOP TO SHOOT, WITH A SHOTGUN! (KNOCK BACK THE PLAYER?)

#include "Player.h"
#include "Game.h"

Player::Player() : GameObject(PLAYER)
{}

void Player::initialise(Vector2D pos)
{
	srcRect = { 0, 0, 32, 64 };
	destRect = { 1024 / 2, 768 / 2, 32, 64 };

	mouseSrcRect = {0, 0, 20, 20};
	mouseDestRect = {1024 / 2, 768 / 2, 20, 20};

	m_position = pos;

	playerIdleSprite = new Sprite("assets/textures/player/player_idle.png", 4, 500, destRect.w, destRect.h);
	playerWalkingLeftSprite = new Sprite("assets/textures/player/player_left.png", 4, 200, destRect.w, destRect.h);
	playerWalkingRightSprite = new Sprite("assets/textures/player/player_right.png", 4, 200, destRect.w, destRect.h);
	playerWalkingUpSprite = new Sprite("assets/textures/player/player_up.png", 4, 200, destRect.w, destRect.h);
	playerWalkingDownSprite = new Sprite("assets/textures/player/player_down.png", 4, 200, destRect.w, destRect.h);
	playerGrassRustleSprite = new Sprite("assets/textures/player/player_grass_rustle.png", 2, 200, destRect.w, destRect.h);

	mouseTexture = Sprite::LoadTexture("assets/textures/props/xhair.png", TheGame::Instance()->renderer);

	m_bullets = 10;
	m_health = 100;

	active = true;
}

void Player::update()
{
	/*
	Event evt;
	evt.type = EVENT_CASING;
	evt.position = m_position;
	TheGame::Instance()->manageEvent(evt);
	*/

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_MOUSEBUTTONDOWN:

			mousePress(e.button);

			break;

		default:
			break;
		}
	}

	// Get the state of the keys
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_SPACE] && m_bullets <= 0)
	{
		Sound::playGunReload();
		m_bullets = m_bullets + 10;
	}

	// Calculate delays
	m_bulletDelayTimer = m_bulletDelayTimer - m_frameTime;
	m_gunClickTimer = m_gunClickTimer - m_frameTime;
	m_hitDelayTimer = m_hitDelayTimer - m_frameTime;

	// Calculate player movement and position vector
	Vector2D friction = m_pVelocity * -5;
	m_pVelocity = m_pVelocity + friction * m_frameTime;
	m_position = m_position + m_pVelocity * m_frameTime;

	// Set the position to draw the player on screen
	destRect.x = m_position.getX();
	destRect.y = m_position.getY();
}

void Player::render()
{
	SDL_GetMouseState(&mouseX, &mouseY);

	// mouse shit here
	mouseDestRect.x = mouseX;
	mouseDestRect.y = mouseY;

	SDL_RenderCopy(TheGame::Instance()->renderer, mouseTexture, &mouseSrcRect, &mouseDestRect);
	SDL_RenderDrawLine(TheGame::Instance()->renderer, destRect.x, destRect.y, mouseDestRect.x, mouseDestRect.y);

	// Get the state of the keys
	const Uint8* state = SDL_GetKeyboardState(NULL);

	// Handle movement based on the state of a key
	if (state[SDL_SCANCODE_W] && key_down == false)
	{
		key_down = true;

		TheGame::Instance()->map->moveUp();
		playerWalkingUpSprite->play(destRect);
		m_pVelocity = m_pVelocity + Vector2D(0.0f, -1500.0f) * m_frameTime;

		key_down = false;
	}
	else if (state[SDL_SCANCODE_A] && key_down == false)
	{
		key_down = true;

		TheGame::Instance()->map->moveLeft();
		playerWalkingLeftSprite->play(destRect);
		m_pVelocity = m_pVelocity + Vector2D(-1500.0f, 0.0f) * m_frameTime;

		key_down = false;
	}
	else if (state[SDL_SCANCODE_S] && key_down == false)
	{
		key_down = true;

		TheGame::Instance()->map->moveDown();
		playerWalkingDownSprite->play(destRect);
		m_pVelocity = m_pVelocity + Vector2D(0.0f, +1500.0f) * m_frameTime;

		key_down = false;
	}
	else if (state[SDL_SCANCODE_D] && key_down == false)
	{
		key_down = true;

		TheGame::Instance()->map->moveRight();
		playerWalkingRightSprite->play(destRect);
		m_pVelocity = m_pVelocity + Vector2D(+1500.0f, 0.0f) * m_frameTime;

		key_down = false;
	}
	else
	{
		playerIdleSprite->play(destRect);
	}

	//std::cout << "player position vector: " << m_position.getX() << " " << m_position.getY() << std::endl;
	//std::cout << "player velocity vector: " << m_pVelocity.getX() << " " << m_pVelocity.getY() << std::endl;
	//std::cout << "player rect: " << destRect.x << " " << destRect.y << std::endl;
}

void Player::processCollision(GameObject* object)
{
	if (object->GetType() == ZOMBIE)
	{
		// Report the event to the game class to be managed
		Event evt;
		evt.type = EVENT_PLAYER_HIT;
		evt.sourceRect = srcRect;
		evt.destinationRect = destRect;

		TheGame::Instance()->manageEvent(evt);

		Vector2D zombiePos = object->GetPosition();

		if (m_position.getX() > zombiePos.getX())
		{
			m_pAccelleration = Vector2D(+50.0f, 0);
		}

		if (m_position.getX() < zombiePos.getX())
		{
			m_pAccelleration = Vector2D(-50.0f, 0);
		}

		if (m_position.getY() > zombiePos.getY())
		{
			m_pAccelleration = Vector2D(0, +50.0f);
		}

		if (m_position.getY() < zombiePos.getY())
		{
			m_pAccelleration = Vector2D(0, -50.0f);
		}

		m_pVelocity = m_pVelocity + m_pAccelleration;
		m_hitDelayTimer = m_hitDelay;
	}

	if (object->GetType() == ITEM)
	{
		std::cout << "I'm touching an item!" << std::endl;
	}
}

void Player::tileCollision(std::vector<Tile*> Tiles)
{
	for (unsigned int i = 0; i < Tiles.size(); i++)
	{
		if (destRect.x + destRect.w >= (Tiles[i]->tileDestRect.x) &&
			Tiles[i]->tileDestRect.x + Tiles[i]->tileDestRect.w >= (destRect.x) &&
			destRect.y + destRect.h >= (Tiles[i]->tileDestRect.y) &&
			Tiles[i]->tileDestRect.y + Tiles[i]->tileDestRect.h >= (destRect.y))
		{
			if (Tiles[i]->getTileType() == 0) // stone
			{
				//std::cout << "Player standing on stone!" << std::endl;
			}
			if (Tiles[i]->getTileType() == 1) // water
			{
				//this->m_pVelocity = Vector2D(m_pVelocity) * 0.5f;
				//m_pAccelleration = Vector2D(0, 0);
				//m_pVelocity = Vector2D(0, 0);
			}
			if (Tiles[i]->getTileType() == 2) // grass
			{
				playerGrassRustleSprite->play(destRect);

				//std::cout << "Player standing on grass!" << std::endl;
			}
			if (Tiles[i]->getTileType() == 3) // spikes
			{
				//std::cout << "Touching tile type: " << Tiles[i]->getTileType() << std::endl;
			}
			if (Tiles[i]->getTileType() == 4) // center wall - tricky
			{
				// find the face of the wall the player is touching
				// determine which way they can travel in
			}
			if (Tiles[i]->getTileType() >= 5 || Tiles[i]->getTileType() <= 17)
			{
				std::cout << "Player touching wall!" << std::endl;
			}
		}
	}
}

/*
bool Player::touchingWall(std::vector<Tile*> Tiles)
{
for (unsigned int i = 0; i < Tiles.size(); i++)
{
if (destRect.x + destRect.w >= (Tiles[i]->tileDestRect.x) &&
Tiles[i]->tileDestRect.x + Tiles[i]->tileDestRect.w >= (destRect.x) &&
destRect.y + destRect.h >= (Tiles[i]->tileDestRect.y) &&
Tiles[i]->tileDestRect.y + Tiles[i]->tileDestRect.h >= (destRect.y))
{
if ((Tiles[i]->getTileType() >= 4) && (Tiles[i]->getTileType() <= 12))
{
return true;
}
}
}

return false;
}
*/

void Player::mousePress(SDL_MouseButtonEvent& b)
{
	if (b.button == SDL_BUTTON_LEFT && m_bullets > 0) 
	{
		Bullet* bullet = new Bullet();
		bullet->initialise(m_position.getX(), m_position.getY(), mouseX, mouseY);
		TheGame::Instance()->om.addObject(bullet);

		Sound::playGunShot();

		m_bulletDelayTimer = m_bulletDelay;
		m_bullets--;
	}
	else if (b.button == SDL_BUTTON_LEFT && m_bullets <= 0)
	{
		Sound::playGunClick();
		m_gunClickTimer = m_clickDelay;
	}
}

SDL_Rect& Player::GetRect()
{
	return destRect;
}