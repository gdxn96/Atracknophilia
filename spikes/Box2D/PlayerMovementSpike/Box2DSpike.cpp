// PlayerMovementSpike.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "SDL.h"
#include "Box2D\Box2D.h"
#include "Dependancies\rapidjson\rapidjson.h"
#include "Dependancies\rapidjson\document.h"
#include "Dependancies\rapidjson\filereadstream.h"
#include "Dependancies\rapidjson\reader.h"


using namespace std;
using namespace rapidjson;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

float toPixels(float f)
{
	return f / 10;
}

SDL_Rect toPixels(SDL_Rect r)
{
	r.x /= 10;
	r.y /= 10;
	r.w /= 10;
	r.h /= 10;

	return r;
}

static b2World* World()
{
	static b2World world(b2Vec2(-40.0f, 0.0f));
	return &world;
}

float toMeters(double f)
{
	return f * 10;
}
//
//b2BodyDef dynamicBodyDef;
//dynamicBodyDef.type = b2_dynamicBody; //This line changes it from the default static to a dynamic body
//dynamicBodyDef.position.Set(2500.0f, 10.0f);
//b2Body* dynamicBody = world.CreateBody(&dynamicBodyDef);
class Box
{
public:
	Box(float x, float y, float width, float height, bool red) : 
		m_red(red)
	{
		m_rect.x = x;
		m_rect.y = y;
		m_rect.w = width;
		m_rect.h = height;

		b2BodyDef bodyDef;
		bodyDef.position.Set(x , y);
		
		if (red)
		{
			bodyDef.type = b2_staticBody;
		}
		else
		{
			bodyDef.type = b2_dynamicBody;
		}
		m_body = World()->CreateBody(&bodyDef);

		b2PolygonShape m_box;
		m_box.SetAsBox(width / 2, height / 2);

		m_body->CreateFixture(&m_box, 0.0f);
	}
	void update(float dt)
	{
		printf("----------------------------------\n");
		std::cout << m_rect.x << " " << m_rect.y << " " << m_rect.w << " " << m_rect.h << std::endl;
		printf("\n");
		std::cout << m_body->GetPosition().x << " " << m_body->GetPosition().y << std::endl;
		printf("----------------------------------\n");
		
		m_rect.x = m_body->GetPosition().x;
		m_rect.y = m_body->GetPosition().y;
	}

	void Render(SDL_Renderer* r)
	{
		if (m_red)
		SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
		else
			SDL_SetRenderDrawColor(r, 0, 255, 0, 255);

		SDL_RenderDrawRect(r, &toPixels(m_rect));
	}

private:
	SDL_Rect m_rect;
	bool m_red;
	b2Body* m_body;
};

int main(int argc, char** argv)
{
	SDL_Window* window = NULL;
	SDL_Event e;
	window = SDL_CreateWindow("Spike", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// calculate delta time
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;

	vector<Box> _boxes;
	//_boxes.push_back(Box(500, 100, 100, 100, false));
	//_boxes.push_back(Box(100, 100, 100, 100, true));

	float32 timeStep = 1.0f / 60.0f; //60 steps per second

	float frameTime = 1000 * timeStep;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	FILE* _file = new FILE();
	fopen_s(&_file, "test.json", "rb");
	char readBuffer[65536];
	FileReadStream _is(_file, readBuffer, sizeof(readBuffer));
	Document _document;
	_document.ParseStream(_is);
	fclose(_file);

	for (const auto& itr : _document["objects"].GetArray())
	{
		_boxes.push_back(Box(itr["x"].GetDouble(), itr["y"].GetDouble(), itr["width"].GetDouble(), itr["height"].GetDouble(), true));
	}

	bool quit = false;

	while (!quit) 
	{
		if (deltaTime > frameTime)
		{
			World()->Step(timeStep, velocityIterations, positionIterations);

			SDL_RenderClear(renderer);

			for (int i = 0; i < _boxes.size(); i++)
			{
				_boxes.at(i).update(0);
				_boxes.at(i).Render(renderer);
			}

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderPresent(renderer);

			LAST = NOW;
		}

		NOW = SDL_GetPerformanceCounter();

		deltaTime = ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

	} // end  game loop


		

	return 0;
}

