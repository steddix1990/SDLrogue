// w16016982	Stephen Dixon	KV6003

#ifndef __Player__
#define __Player__

#include "GameObject.h"
#include "Bullet.h"
#include "Events.h"
#include "Sound.h"
#include "Sprite.h"
#include "TextureLoader.h"
#include <vector>

class Player : public GameObject
{
public:

	Player();
	virtual ~Player() {}

	void initialise(Vector2D position);
	void update();
	void render();
	void processCollision(GameObject* object);

	void mousePress(SDL_MouseButtonEvent& b);

	SDL_Rect& Player::GetRect();

	SDL_Rect srcRect;
	SDL_Rect destRect;
	SDL_Rect mouseSrcRect;
	SDL_Rect mouseDestRect;

	int mouseX, mouseY;

	static const int PLAYER_WIDTH = 32;
	static const int PLAYER_HEIGHT = 64;

	bool key_down = false;

	void tileCollision(std::vector<Tile*> Tiles);
	bool touchingWall;

private:

	Vector2D m_pVelocity;
	Vector2D m_pAccelleration;

	int m_bullets;

	float m_bulletDelayTimer = 0.0f;
	float m_hitDelayTimer = 0.0f;
	float m_gunClickTimer = 0.0f;

	const float m_bulletDelay = 0.5f;
	const float m_hitDelay = 3.0f;
	const float m_clickDelay = 1.0f;

	Sprite* playerIdleSprite;
	Sprite* playerWalkingLeftSprite;
	Sprite* playerWalkingRightSprite;
	Sprite* playerWalkingUpSprite;
	Sprite* playerWalkingDownSprite;
	Sprite* playerGrassRustleSprite;

	SDL_Texture* mouseTexture;
};
#endif /* defined(__Player__) */