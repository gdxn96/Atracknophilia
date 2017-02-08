// ATracknophilia.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "ResourceManager.h"

const float	SCREEN_WIDTH = 1200.0f;
const float	SCREEN_HEIGHT = 1200.0f;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
ResourceManager* resourceMan = nullptr;

float lastTime = 0;

int main()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "Could not init SDL: " << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow(
		"Resource Manager Component",		// window title
		SDL_WINDOWPOS_UNDEFINED,			// initial x position
		SDL_WINDOWPOS_UNDEFINED,			// initial y position
		(int)SCREEN_WIDTH,					// width, in pixels
		(int)SCREEN_HEIGHT,                 // height, in pixels
		SDL_WINDOW_OPENGL					// flags - see below
	);

	if (window == NULL)
	{
		cout << "Could not create window: " << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		cout << "Could not create renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	// get a pointer to the resource manager and initialiase it with the renderer
	resourceMan = ResourceManager::getInstance();
	resourceMan->init(renderer);

	resourceMan->loadResourcesFromJSON("Resources/resourcesNEW.json");
	resourceMan->loadResourceQueue();


	/************************** GAME LOOP *************************************/
	while (true)
	{
		update();
		render();
	}

    return 0;
}

void update()
{
	float _currentTime = SDL_GetTicks();						//millis since game started
	float _deltaTime = (_currentTime - lastTime) / 1000.0;	//time since last update

	// Update the resource manager to monitor changes in the files
	resourceMan->update(_deltaTime);

	lastTime = _currentTime;
}

void render()
{

}

