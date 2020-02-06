// w16016982	Stephen Dixon	KV6003

#include "Zombie.h"

Zombie::Zombie() : GameObject(ZOMBIE)
{}

/// The zombie initialisation needs to be changed.

// A new zombie is being initialised each time, and all the textures / sprites loaded / pushed into the game object list again.
// Need to work out how to clone the same zombie that is already in memory, save on pointer fuck ups and what not

// Also, when the zombies destroyed now, the sounds and sprites aren't. Which will bloat the vector even more and slow the game down
void Zombie::initialise(Vector2D pos, int type)
{
	srcRect = { 0, 0, 32, 64 };
	destRect = { 1024 / 2 - 32, 768 / 2 - 64, 32, 64 };

	zombieIdleSprite = new Sprite("assets/textures/zombie/zombie_idle.png", 4, 500, destRect.w, destRect.h);
	zombieWalkingLeftSprite = new Sprite("assets/textures/zombie/zombie_left.png", 4, 200, destRect.w, destRect.h);
	zombieWalkingRightSprite = new Sprite("assets/textures/zombie/zombie_right.png", 4, 200, destRect.w, destRect.h);
	zombieWalkingUpSprite = new Sprite("assets/textures/zombie/zombie_up.png", 4, 200, destRect.w, destRect.h);
	zombieWalkingDownSprite = new Sprite("assets/textures/zombie/zombie_down.png", 4, 200, destRect.w, destRect.h);

	m_splat = Sprite::LoadTexture("assets/textures/zombie/splat.png", TheGame::Instance()->renderer);

	switch (type)
	{
	case 0:
		// BIGMAN
		m_speed = 40;
		m_health = 6;

		break;
	case 1:
		// INTERCEPTOR
		m_speed = 55;
		m_health = 2;

		break;
	case 2:
		// CADAVER
		m_speed = 30;
		m_health = 3;

		break;
	}

	destRect.x = m_position.getX();
	destRect.y = m_position.getY();

	m_position = pos;

	active = true;
}

void Zombie::update()
{
	Vector2D friction = m_zVelocity * -1.5;

	m_zVelocity = m_zVelocity + friction * m_frameTime;
	m_position = m_position + m_zVelocity * m_frameTime;

	// set the position to draw on screen
	destRect.x = m_position.getX();
	destRect.y = m_position.getY();

	// Follow the player
	float player_x = TheGame::Instance()->getPlayerPosition().getX();
	float player_y = TheGame::Instance()->getPlayerPosition().getY();

	if (player_y < m_position.getY())
	{
		m_position.setY(m_position.getY() - m_speed * m_frameTime);
	}

	if (player_y > m_position.getY())
	{
		m_position.setY(m_position.getY() + m_speed * m_frameTime);
	}

	if (player_x < m_position.getX())
	{
		m_position.setX(m_position.getX() - m_speed * m_frameTime);
	}

	if (player_x > m_position.getX())
	{
		m_position.setX(m_position.getX() + m_speed * m_frameTime);
	}
}

void Zombie::render()
{
	if (active)
	{
		if (destRect.x + destRect.w >= (TheGame::Instance()->camera.x) &&
			TheGame::Instance()->camera.x + TheGame::Instance()->camera.w >= (destRect.x) &&
			destRect.y + destRect.h >= (TheGame::Instance()->camera.y) &&
			TheGame::Instance()->camera.y + TheGame::Instance()->camera.h >= (destRect.y)) // zombie within camera veiwport
		{
			// get player x, get zombie x
			// get player y, get zombie y

			// add px and zx
			// and py and zy

			// if total zx > zy, draw left / right animations, else draw up / down

			// if the distance between player x and zombie x > player y and zombie y
			// player left or right
			/// play left / right animation based on zombie x and player x

			// if the distance between player x and zombie x < player y and zombie y
			// play up or down
			/// play up / down animation based on player y and zombie y

			// Follow the player
			float player_x = TheGame::Instance()->getPlayerPosition().getX();
			float player_y = TheGame::Instance()->getPlayerPosition().getY();

			if (player_x + m_position.getX() > player_y + m_position.getY())
			{
				if (player_x > m_position.getX())
				{
					zombieWalkingRightSprite->play(destRect);
				}
				else if (player_x < m_position.getX())
				{
					zombieWalkingLeftSprite->play(destRect);
				}
			}
			else if (player_x + m_position.getX() < player_y + m_position.getY())
			{
				if (player_y > m_position.getY())
				{
					zombieWalkingDownSprite->play(destRect);
				}
				else if (player_y < m_position.getY())
				{
					zombieWalkingUpSprite->play(destRect);
				}
			}
		}
	}
}

void Zombie::processCollision(GameObject* object)
{
	if (object->GetType() == ZOMBIE)
	{
		Vector2D zombiePos = object->GetPosition();

		if (m_position.getX() > zombiePos.getX() && m_position.getY() > zombiePos.getY())
		{
			m_zAccelleration += Vector2D(+5.0f, +5.0f);
		}

		if (m_position.getX() < zombiePos.getX() && m_position.getY() < zombiePos.getY())
		{
			m_zAccelleration += Vector2D(-5.0f, -5.0f);
		}

		if (m_position.getX() > zombiePos.getX() && m_position.getY() < zombiePos.getY())
		{
			m_zAccelleration += Vector2D(+5.0f, -5.0f);
		}

		if (m_position.getX() > zombiePos.getY() && m_position.getX() < zombiePos.getY())
		{
			m_zAccelleration += Vector2D(-5.0f, +5.0f);
		}

		m_zVelocity = m_zVelocity + m_zAccelleration;
	}
	
	if (object->GetType() == BULLET)
	{
		object->active = false;

		Sound::playZombieGroan();

		SDL_RenderCopy(TheGame::Instance()->renderer, m_splat, &srcRect, &destRect);
		
		m_health--;

		if (m_health <= 0)
		{
			Event evt;
			evt.type = EVENT_BURST;
			evt.position = m_position;
			evt.sourceRect = { 0, 0, 90, 90 };
			evt.destinationRect = destRect;

			TheGame::Instance()->manageEvent(evt);

			// destroy sprites?
			//SDL_DestroyTexture(m_zombieDownTexture);

			active = false;
		}
	}

	if (object->GetType() == PLAYER)
	{
		// chomp sound, health++
		// animated zombie healing sprite
		// some bits falling off the player?
	}
}

SDL_Rect& Zombie::GetRect()
{
	return destRect;
}