// w16016982	Stephen Dixon	KV6003

#include "Casing.h"

Casing::Casing() : GameObject(CASING)
{}

void Casing::initialise(Vector2D pos)
{
	m_casingTexture = TextureLoader::loadTexture("assets/textures/props/casing.png", TheGame::Instance()->renderer);

	srcRect = { 0, 0, 8, 4 };
	destRect = { 1024 / 2 - 8 / 2, 768 / 2 - 4 / 2, 8, 4 };

	m_position = pos;

	active = true;
}

void Casing::update()
{
	if (active)
	{
		// set the position to draw on screen
		destRect.x = m_position.getX();
		destRect.y = m_position.getY();
	}
}

void Casing::render()
{
	if (active)
	{
		SDL_RenderCopy(TheGame::Instance()->renderer, m_casingTexture, &srcRect, &destRect);
	}
}

SDL_Rect& Casing::GetRect()
{
	return destRect;
}