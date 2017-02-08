// ATracknophilia.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "sdl\SDL.h"
#include "box2d\Box2D.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "rapidjson\rapidjson.h"
#include "rapidjson\filereadstream.h"
#include "rapidjson\reader.h"
#include "rapidjson\document.h"
#include "Player.h"
#include "Box.h"
#include "LTimer.h"

#define SDL_main main

int main()
{
#pragma region irrelevant
	const int SCREEN_FPS = 120;
	const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

	SDL_Window* window = NULL;
	SDL_Event e;
	window = SDL_CreateWindow("Spike", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
#pragma endregion

	std::vector<Box> _boxes;

	int32 velocityIterations = 6;
	int32 positionIterations = 3;

	FILE* _file = new FILE();
	fopen_s(&_file, "levels/test.json", "rb");
	char readBuffer[65536];
	rapidjson::FileReadStream _is(_file, readBuffer, sizeof(readBuffer));
	rapidjson::Document _document;
	_document.ParseStream(_is);
	fclose(_file);

	for (const auto& itr : _document["objects"].GetArray())
	{
		_boxes.push_back(Box(itr["x"].GetDouble() / 100, itr["y"].GetDouble() / 100, itr["width"].GetDouble() / 100, itr["height"].GetDouble() / 100, true));
	}

	bool quit = false;

	Player p;
	LTimer capTimer;//to cap framerate
	float prevTime = 0;

	while (!quit)
	{
		//Start the frame timer
		capTimer.start();
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_LEFT:
					p.ApplyForce(Vector(-20, 0));
					break;
				case SDLK_RIGHT:
					p.ApplyForce(Vector(20, 0));
					break;
				case SDLK_SPACE:
					b2Vec2& g = Gravity();
					g.y = -g.y;
					break;
				}	// end switch
			}	// end key if statement
			else
			{
				//p.Move();  // apply friction to keep speed constant
			}
		}// end event while loop

		unsigned int currentTime = LTimer::gameTime();//millis since game started
		float deltaTime = (currentTime - prevTime) / 1000.0;//time since last update

		World().Step(deltaTime, velocityIterations, positionIterations);

		SDL_RenderClear(renderer);

		for (int i = 0; i < _boxes.size(); i++)
		{
			_boxes.at(i).update(deltaTime);
			p.update(deltaTime);
			_boxes.at(i).Render(renderer);
			p.Render(renderer);
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderPresent(renderer);
		
		prevTime = currentTime;
		int frameTicks = capTimer.getTicks();//time since start of frame
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time before going to next frame
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}

	} // end  game loop

	return 0;
}

