// w16016982	Stephen Dixon	KV6003

#ifndef __Events__
#define __Events__

#include "SDL.h"

enum EventType { EVENT_NONE, EVENT_BURST, MORE_ZOMBIES, EVENT_PLAYER_HIT, EVENT_BLOOD_SPLAT, EVENT_CASING };

class GameObject;

struct Event
{
	EventType type;
	Vector2D position;

	SDL_Rect sourceRect;
	SDL_Rect destinationRect;
};
#endif /* defined(__Events__) */