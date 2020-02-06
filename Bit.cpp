// w16016982	Stephen Dixon	KV6003

#include "Bit.h"

Bit::Bit() : GameObject(BIT)
{}

void Bit::initialise(Vector2D pos, int type)
{
	switch (type)
	{
	case 1:
		m_bitTexture = TextureLoader::loadTexture("assets/textures/zombie/bit1.png", TheGame::Instance()->renderer);
		srcRect = { 0, 0, 16, 16 };
		destRect = { 1024 / 2 - 16 / 2, 768 / 2 - 16 / 2, 16, 16 };
		break;
	case 2:
		m_bitTexture = TextureLoader::loadTexture("assets/textures/zombie/bit2.png", TheGame::Instance()->renderer);
		srcRect = { 0, 0, 4, 18 };
		destRect = { 1024 / 2 - 4 / 2, 768 / 2 - 18 / 2, 4, 18 };
		break;
	case 3:
		m_bitTexture = TextureLoader::loadTexture("assets/textures/zombie/bit3.png", TheGame::Instance()->renderer);
		srcRect = { 0, 0, 20, 4 };
		destRect = { 1024 / 2 - 20 / 2, 768 / 2 - 4 / 2, 20, 4 };
		break;
	case 4:
		m_bitTexture = TextureLoader::loadTexture("assets/textures/zombie/bit4.png", TheGame::Instance()->renderer);
		srcRect = { 0, 0, 25, 25 };
		destRect = { 1024 / 2 - 25 / 2, 768 / 2 - 25 / 2, 25, 25 };
		break;
	case 5:
		m_bitTexture = TextureLoader::loadTexture("assets/textures/zombie/bit5.png", TheGame::Instance()->renderer);
		srcRect = { 0, 0, 14, 24 };
		destRect = { 1024 / 2 - 14 / 2, 768 / 2 - 24 / 2, 14, 24 };
		break;

	default:
		break;
	}

	m_position = pos;
}

void Bit::update()
{
	if (active)
	{
		destRect.x = m_position.getX();
		destRect.y = m_position.getY();
	}
}

void Bit::render()
{
	if (active)
	{
		SDL_RenderCopy(TheGame::Instance()->renderer, m_bitTexture, &srcRect, &destRect);
	}
}

SDL_Rect& Bit::GetRect()
{
	return destRect;
}