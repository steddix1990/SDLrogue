// w16016982	Stephen Dixon	KV6003

#ifndef __Bullet__
#define __Bullet__

#include "GameObject.h"
#include "Game.h"
#include "TextureLoader.h"

class Bullet : public GameObject
{
public:
	Bullet();
	virtual ~Bullet() {}

	void initialise(float startX, float startY, float targetX, float targetY);
	void update();
	void render();

	SDL_Rect& Bullet::GetRect();
	Vector2D m_bVelocity;

	// How fast does a bullet travel?
	float m_BulletSpeed = 1000;

	// What fraction of 1 pixel does the bullet travel, 
	// Horizontally and vertically each frame?
	// These values will be derived from m_BulletSpeed
	float m_BulletDistanceX;
	float m_BulletDistanceY;

	// Where is this bullet headed to?
	float m_XTarget;
	float m_YTarget;

	// Some boundaries so the bullet doesn't fly forever
	float m_MaxX;
	float m_MinX;
	float m_MaxY;
	float m_MinY;

private:

	SDL_Texture* m_bulletTexture;
};
#endif /* defined(__Bullet__) */