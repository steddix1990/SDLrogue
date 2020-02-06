// w16016982	Stephen Dixon	KV6003

#include "Sound.h"
#include <iostream>

Mix_Chunk* gameStart = NULL;
Mix_Chunk* gunShot = NULL;
Mix_Chunk* gunClick = NULL;
Mix_Chunk* gunReload = NULL;
Mix_Chunk* zombieGroan = NULL;
Mix_Chunk* zombieBurst = NULL;

//Mix_Chunk* playerHit = NULL;
//Mix_Chunk* playerDeath = NULL;

Sound::Sound()
{}

void Sound::init()
{
	// Initialize SDL_mixer 
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << "Mix_Init: %s\n" << Mix_GetError();
	}

	// Load the sounds after opening an audio channel
	loadGameStart();
	loadGunShot();
	loadGunClick();
	loadGunReload();
	loadZombieGroan();
	loadZombieBurst();
}

void Sound::loadGameStart()
{
	gameStart = Mix_LoadWAV("assets/sounds/game/groan.wav");
	if (gameStart != NULL)
	{
		std::cout << "Loaded groan.wav\n";
	}
	else
	{
		std::cout << stderr << "Could not load groan.wav\n";
	}
}

void Sound::loadGunShot()
{
	gunShot = Mix_LoadWAV("assets/sounds/player/gunshot.wav");
	if (gunShot != NULL)
	{
		std::cout << "Loaded gunshot.wav\n";
	}
	else
	{
		std::cout << stderr << "Could not load gunshot.wav\n";
	}
}

void Sound::loadGunClick()
{
	gunClick = Mix_LoadWAV("assets/sounds/player/click.wav");
	if (gunClick != NULL)
	{
		std::cout << "Loaded click.wav\n";
	}
	else
	{
		std::cout << stderr << "Could not load click.wav\n";
	}
}

void Sound::loadGunReload()
{
	gunReload = Mix_LoadWAV("assets/sounds/player/reload.wav");
	if (gunReload != NULL)
	{
		std::cout << "Loaded reload.wav\n";
	}
	else
	{
		std::cout << stderr << "Could not load reload.wav\n";
	}
}

void Sound::loadZombieGroan()
{
	zombieGroan = Mix_LoadWAV("assets/sounds/zombie/gargle.wav");
	if (zombieGroan != NULL)
	{
		std::cout << "Loaded gargle.wav\n";
	}
	else
	{
		std::cout << stderr << "Could not load gargle.wav\n";
	}
}

void Sound::loadZombieBurst()
{
	zombieBurst = Mix_LoadWAV("assets/sounds/zombie/burst.wav");
	if (zombieBurst != NULL)
	{
		std::cout << "Loaded burst.wav\n";
	}
	else
	{
		std::cout << stderr << "Could not load burst.wav\n";
	}
}

void Sound::playGameStart()
{
	if (Mix_PlayChannel(-1, gameStart, 0) == -1)
	{
		std::cout << "Could not play gameStart sound: %s\n" << Mix_GetError();
	}
}

void Sound::playGunShot()
{
	if(Mix_PlayChannel(-1, gunShot, 0) == -1) 
	{
		std::cout << "Could not play gunShot sound: %s\n" << Mix_GetError();
	}
}

void Sound::playGunClick()
{
	if (Mix_PlayChannel(-1, gunClick, 0) == -1)
	{
		std::cout << "Could not play gunClick sound: %s\n" << Mix_GetError();
	}
}

void Sound::playGunReload()
{
	if (Mix_PlayChannel(-1, gunReload, 0) == -1)
	{
		std::cout << "Could not play gunReload sound: %s\n" << Mix_GetError();
	}
}

void Sound::playZombieGroan()
{
	if (Mix_PlayChannel(-1, zombieGroan, 0) == -1) 
	{
		std::cout << "Cound not play zombieGroan sound: %s\n" << Mix_GetError();
	}
}

void Sound::playZombieBurst()
{
	if (Mix_PlayChannel(-1, zombieBurst, 0) == -1)
	{
		std::cout << "Cound not play zombieBurst sound: %s\n" << Mix_GetError();
	}
}

void Sound::cleanup()
{
	Mix_FreeChunk(gameStart);
	Mix_FreeChunk(gunShot);
	Mix_FreeChunk(gunClick);
	Mix_FreeChunk(gunReload);
	Mix_FreeChunk(zombieGroan);
	Mix_FreeChunk(zombieBurst);

	Mix_CloseAudio();
}

/// Sound credits
// start - https://freesound.org/people/Under7dude/sounds/163440/
// gunshot - http://soundbible.com/1906-Barreta-M9.html
// click - https://freesound.org/people/KlawyKogut/sounds/154934/
// reload - https://freesound.org/people/Fr3yr/sounds/100804/
// burst - https://freesound.org/people/JustInvoke/sounds/446115/
// gurgle - https://freesound.org/people/Breviceps/sounds/445983/