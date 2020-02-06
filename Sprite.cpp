#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(const char* fileName, int frames, int speed, int w, int h)
{
	m_frames = frames;
	m_speed = speed;

	sprite = LoadTexture(fileName, TheGame::Instance()->renderer);

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = w;
	srcRect.h = h;

	destRect.x = 1024 / 2 - w / 2;
	destRect.y = 768 / 2 - h / 2;
	destRect.w = w;
	destRect.h = h;

	//m_spritePos = pos;

	srcRect = { 0, 0, w, h };
	destRect = { 1024 / 2 - w / 2, 768 / 2 - h / 2, w, h };
}

void Sprite::update()
{
	srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / m_speed) % m_frames);
}

void Sprite::renderSprite()
{
	if (visible)
	{
		SDL_RenderCopy(TheGame::Instance()->renderer, sprite, &srcRect, &destRect);
	}
}

void Sprite::play(SDL_Rect rect)
{
	destRect.x = rect.x;
	destRect.y = rect.y;

	update();
	renderSprite();
}

SDL_Rect& Sprite::GetRect()
{
	return destRect;
}

SDL_Texture* Sprite::LoadTexture(const char* texture, SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tempTexture;
}