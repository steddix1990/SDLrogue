#include "Barrel.h"
#include "Game.h"

Barrel::Barrel() : GameObject(BARREL)
{}

void Barrel::initialise(Vector2D pos)
{
	m_barrelSprite = new Sprite("assets/textures/props/barrel.png", 3, 150, 32, 40);

	m_position = pos;
	active = true;
}

void Barrel::update()
{
	if (active)
	{
		destRect.x = m_position.getX();
		destRect.y = m_position.getY();
	}
}

void Barrel::render()
{
	if (active)
	{
		m_barrelSprite->play(destRect);
	}
}

SDL_Rect& Barrel::GetRect()
{
	return destRect;
}

Barrel::~Barrel()
{
	
}