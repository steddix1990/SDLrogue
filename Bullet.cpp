// w16016982	Stephen Dixon	KV6003

#include "Bullet.h"

Bullet::Bullet() : GameObject(BULLET)
{}

void Bullet::initialise(float startX, float startY, float targetX, float targetY)
{
	m_bulletTexture = TextureLoader::loadTexture("assets/textures/props/bullet.png", TheGame::Instance()->renderer);

	srcRect = { 0, 0, 10, 10 };
	destRect = { 1024 / 2 - 10 / 2, 768 / 2 - 10 / 2, 10, 10 };

	m_position.setX(startX);
	m_position.setY(startY);

	// Calculate the gradient of the flight path
	float gradient = (startX - targetX) / (startY - targetY);

	// Any gradient less than zero needs to be negative
	if (gradient < 0){gradient *= -1;}

	// Calculate the ratio between x and t
	float ratioXY = m_BulletSpeed / (1 + gradient);

	// Set the "speed" horizontally and vertically
	m_BulletDistanceY = ratioXY;
	m_BulletDistanceX = ratioXY * gradient;

	// Point the bullet in the right direction
	if (targetX < startX){m_BulletDistanceX *= -1;}
	if (targetY < startY){m_BulletDistanceY *= -1;}

	// Finally, assign the results to the
	// member variables
	m_XTarget = targetX;
	m_YTarget = targetY;

	// Set a max range of 1000 pixels
	float range = 1000;
	m_MinX = startX - range;
	m_MaxX = startX + range;
	m_MinY = startY - range;
	m_MaxY = startY + range;
}

void Bullet::update()
{
	if (active)
	{
		// Update the bullet position variables
		m_position.m_x += m_BulletDistanceX * m_frameTime;
		m_position.m_y += m_BulletDistanceY * m_frameTime;

		destRect.x = m_position.getX();
		destRect.y = m_position.getY();
	}
}

void Bullet::render()
{
	if (active)
	{
		SDL_RenderCopy(TheGame::Instance()->renderer, m_bulletTexture, &srcRect, &destRect);
	}
}

SDL_Rect& Bullet::GetRect()
{
	return destRect;
}