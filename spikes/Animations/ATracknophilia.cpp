// ATracknophilia.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#define SDL_main main
#include "Animation.h"
#include <thread>
#include <chrono>

const float	SCREEN_WIDTH = 1200.0f;
const float	SCREEN_HEIGHT = 1200.0f;

ResourceManager* resourceMan = nullptr;
Renderer renderer;
Animation* stick = nullptr;

float lastTime = 0;

using namespace std;

void update()
{
	float _currentTime = SDL_GetTicks();						//millis since game started
	float _deltaTime = (_currentTime - lastTime) / 1000.0;		//time since last update

	SDL_Event _e;

	while (SDL_PollEvent(&_e) != 0)
	{
		switch (_e.type)
		{
		case SDL_KEYUP:
			switch (_e.key.keysym.sym)
			{
			case SDLK_1:
				stick->changeAnimation("bob");
				break;
			case SDLK_2:
				stick->changeAnimation("stick_man");
				break;
			}
			break;

		default:
			break;
		}
	}


	// Update the resource manager to monitor changes in the files
	resourceMan->update(_deltaTime);
	stick->update(_deltaTime);

	lastTime = _currentTime;
}

void render()
{
	renderer.clear(Colour(0, 0, 0));

	stick->draw(renderer);

	renderer.present();
}

int main()
{
	renderer.init(Size2D(1280, 720), "Whatever", nullptr);

	// get a pointer to the resource manager and initialiase it with the renderer
	resourceMan = ResourceManager::getInstance();
	resourceMan->init(&renderer);

	resourceMan->loadResources("Resources/resourcesNEW.json");
	resourceMan->loadResourceQueue();

	stick = new Animation("stick_man", Rect(Point2D(640, 360), Size2D(64, 205)));

	/************************** GAME LOOP *************************************/
	while (true)
	{
		update();
		render();
	}

    return 0;
}


