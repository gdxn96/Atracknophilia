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
		case START_RACE:
			playFX("start_race");
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
		case JUMP:
			playFX("jump");
			break;
		case CLICK_OFF:
			playFX("click_off");
			break;
		case CLICK_ON:
			playFX("click_on");
			break;
		case MAIN_MENU:
			playMusic("menu-music");
			break;
		case GAME_SCENE:
			playMusic("game_music");
			break;
		case CREDITS:
			playMusic("credits-music");
			break;
		}
	}

	bool init();
private:
	void playFX(Mix_Chunk * sound);

	Mix_Music* music = NULL;
};
#endif