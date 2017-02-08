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

//float toPixels(float f)
//{
//	return f / 10;
//}
//
//SDL_Rect toPixels(SDL_Rect r)
//{
//	r.x *= 1;
//	r.y *= 1;
//	r.w *= 1;
//	r.h *= 1;
//
//	return r;
//}

static b2Vec2& Gravity()
{
	static b2Vec2 gravity(0, 20);
	return gravity;
}

static b2World& World()
{
	static b2World world(Gravity());
	return world;
}

//float toMeters(double f)
//{
//	return f * 10;
//}

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
		
		bodyDef.position.Set(x + width / 2, y + height / 2);
		
		if (red)
		{
			bodyDef.type = b2_staticBody;
		}
		else
		{
			bodyDef.type = b2_dynamicBody;
		}

		m_body = World().CreateBody(&bodyDef);
		m_box.SetAsBox(width / 2, height / 2);

		b2FixtureDef fixture;
		
		fixture.shape = &m_box;
		fixture.density = 1.0f;

		m_body->CreateFixture(&fixture);
	}
	void update(float dt)
	{
		if (!m_red)
		{
			
		}
		m_rect.x = m_body->GetPosition().x - m_rect.w / 2;
		m_rect.y = m_body->GetPosition().y - m_rect.h / 2;
	}

	void Render(SDL_Renderer* r)
	{
		if (m_red)
			SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
		else
			SDL_SetRenderDrawColor(r, 0, 255, 0, 255);

		SDL_RenderDrawRect(r, &m_rect);
	}

private:
	SDL_Rect m_rect;
	bool m_red;
	b2Body* m_body;
	b2PolygonShape m_box;
};

int main(int argc, char** argv)
{
#pragma region irrelevant
	SDL_Window* window = NULL;
	SDL_Event e;
	window = SDL_CreateWindow("Spike", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// calculate delta time
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;
#pragma endregion

	vector<Box> _boxes;
	_boxes.push_back(Box(70, 120, 10, 10, false));
	_boxes.push_back(Box(0, 0, 100, 1, true));

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
		_boxes.push_back(Box(itr["x"].GetDouble() / 10, itr["y"].GetDouble() / 10, itr["width"].GetDouble() / 10, itr["height"].GetDouble() / 10, true));
	}

	bool quit = false;

	while (!quit) 
	{
		if (deltaTime > frameTime)
		{
			World().Step(timeStep, velocityIterations, positionIterations);

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

