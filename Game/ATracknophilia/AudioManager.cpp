#include "stdafx.h"
#include "AudioManager.h"

AudioManager::AudioManager()
{
}
AudioManager::~AudioManager()
{
}
bool AudioManager::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		return false;
	}
	return true;
}

void AudioManager::playMusic(string musicName)
{
	music = ResourceManager::getInstance()->getMusicByKey(musicName);
	if (Mix_PlayingMusic() == 0)
	{
		if (music == NULL)
		{
			printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		}
		else
		{
			Mix_PlayMusic(music, -1);
		}
	}
}

void AudioManager::playFX(string sound)
{
	playFX(ResourceManager::getInstance()->getSoundEffectByKey(sound));
}

void AudioManager::playFX(Mix_Chunk* sound)
{
	if (Mix_PlayChannel(-1, sound, 0) == -1) 
	{
		printf("Mix_PlayChannel: %s\n", Mix_GetError());
	}
}