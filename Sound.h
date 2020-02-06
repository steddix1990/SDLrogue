// w16016982	Stephen Dixon	KV6003

#ifndef __Sound__
#define __Sound__

#include "SDL_mixer.h"

class Sound
{
public:

	Sound();
	~Sound() {}

	// Initialise an audio channel
	static void init();

	// Load the sounds
	static void loadGameStart();
	static void loadGunShot();
	static void loadGunClick();
	static void loadGunReload();
	static void loadZombieGroan();
	static void loadZombieBurst();

	// Play the sounds
	static void playGameStart();
	static void playGunShot();
	static void playGunClick();
	static void playGunReload();
	static void playZombieGroan();
	static void playZombieBurst();

	// Clean the sounds up after game ends
	void cleanup();
};
#endif /* defined(__Sound__) */