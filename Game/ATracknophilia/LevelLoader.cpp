#include "stdafx.h"
#include "LevelLoader.h"
#include "EntityFactory.h"

std::unordered_map<LEVELS, const char*> LevelLoader::m_paths;
std::vector<IEntity*> LevelLoader::m_entities;

void LevelLoader::RegisterLevels(std::vector<std::pair<LEVELS, const char*>> map)
{
	for (auto element : map)
	{
		m_paths[element.first] = element.second;
	}
}

Vector2D LevelLoader::loadLevel(LEVELS lvl)
{
	destroyLevel();
	FILE* file = new FILE();
	fopen_s(&file, m_paths[lvl], "rb");
	char readBuffer[65536];
	rapidjson::FileReadStream is(file, readBuffer, sizeof(readBuffer));
	rapidjson::Document document;
	document.ParseStream(is);
	fclose(file);

	Vector2D biggest;

	if (document.HasMember("objects"))
	{
		for (const auto& itr : document["objects"].GetArray())
		{
			float x, y, w, h;
			x = itr["x"].GetFloat() / 50.f;
			y = itr["y"].GetFloat() / 50.f;
			w = itr["width"].GetFloat() / 50.f;
			h = itr["height"].GetFloat() / 50.f;
			EntityFactory::SpawnStaticBox(x, y, w, h);

			if (x + w > biggest.w)
			{
				biggest.w = x + w;
			}
			if (y + h > biggest.h)
			{
				biggest.h = y + h;
			}
		}
	}

	if (document.HasMember("softbox"))
	{
		for (const auto& itr : document["softbox"].GetArray())
		{
			float x, y, w, h;
			x = itr["x"].GetFloat() / 50.f;
			y = itr["y"].GetFloat() / 50.f;
			w = itr["width"].GetFloat() / 50.f;
			h = itr["height"].GetFloat() / 50.f;
			EntityFactory::SpawnSoftBox(x, y, w, h);

			if (x + w > biggest.w)
			{
				biggest.w = x + w;
			}
			if (y + h > biggest.h)
			{
				biggest.h = y + h;
			}
		}
	}
	
	if (document.HasMember("directions"))
	{
		for (const auto& itr : document["directions"].GetArray())
		{
			float x, y, w, h, priority, directionX, directionY;
			x = itr["x"].GetFloat() / 50.f;
			y = itr["y"].GetFloat() / 50.f;
			w = itr["width"].GetFloat() / 50.f;
			h = itr["height"].GetFloat() / 50.f;
			priority = itr["priority"].GetFloat();
			directionX = itr["directionX"].GetFloat();
			directionY = itr["directionY"].GetFloat();
			EntityFactory::SpawnDirectionVolume(x, y, w, h, priority, Vector2D(directionX, directionY));

			if (x + w > biggest.w)
			{
				biggest.w = x + w;
			}
			if (y + h > biggest.h)
			{
				biggest.h = y + h;
			}
		}
	}

	return biggest;

}

void LevelLoader::destroyLevel()
{
	for (auto i : m_entities)
	{
		delete i;
	}
	m_entities.clear();
}

void LevelLoader::destroyObjects()
{
	for (vector<IEntity*>::iterator it = m_entities.begin(); it != m_entities.end();)
	{
		if (!(*it)->alive)
		{
			delete *it;
			it = m_entities.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void LevelLoader::appendToEntities(IEntity* entity)
{
	m_entities.push_back(entity);
}
