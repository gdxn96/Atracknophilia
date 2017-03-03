#ifndef AUDIO_HEADER
#define AUDIO_HEADER


#ifdef __APPLE__
#include "SDL2/SDL.h"
#elif defined(_WIN64) || defined(_WIN32)
#include "../dependancies/sdl/SDL.h"
#endif


#include <string>
#include <iostream>
#include "stdafx.h"
#include "ResourceManager.h"
#include "Observer.h"

class AudioManager : public Observer
{
public:
	AudioManager();
	~AudioManager();

	void playMusic(string musicName);
	void playFX(string sound);

	virtual void onNotify(Event event)
	{
		switch (event)
		{
		case START_GAME:
			playFX("start_game");
			break;
		case RESPAWN:
			playFX("start_game");
			break;
		case HOOK:
			playFX("rope");
			break;
		case SWAP_SHOT:
			playFX("swoosh");
			break;
		case SHOOT:
			playFX("shoot");
			break;
		case DROP:
			playFX("drop");
			break;
		case HIT:
			playFX("hit");
			break;
		case DYING:
			playFX("dying");
			break;
		case SIREN:
			playFX("siren");
			break;
		case LAND:
			playFX("land");
			break;

		case MAIN_MENU:
			playMusic("main_menu");
			break;
		case GAME_SCENE:
			playMusic("game_scene");
			break;
		case CREDITS:
			playMusic("credits");
			break;
		}
	}

	bool init();
private:
	void playFX(Mix_Chunk * sound);

	Mix_Music* music = NULL;
};
#endif