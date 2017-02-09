#pragma once
#define SDL_MAIN_HANDLED
#include "sdl\SDL.h"


class LTimer
{
public:
	//Initializes variables
	LTimer();

	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Gets the timer's time
	Uint32 getTicks()
	{
		//The actual timer time
		Uint32 time = 0;

		//If the timer is running
		if (mStarted)
		{
			//If the timer is paused
			if (mPaused)
			{
				//Return the number of ticks when the timer was paused
				time = mPausedTicks;
			}
			else
			{
				//Return the current time minus the start time
				time = SDL_GetTicks() - mStartTicks;
			}
		}

		return time;
	}

	//Checks the status of the timer
	bool isStarted();
	bool isPaused();

	static unsigned int gameTime() { return SDL_GetTicks(); }

private:
	//The clock time when the timer started
	Uint32 mStartTicks;

	//The ticks stored when the timer was paused
	Uint32 mPausedTicks;

	//The timer status
	bool mPaused;
	bool mStarted;
};