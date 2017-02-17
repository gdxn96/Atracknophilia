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
			x = itr["x"].GetFloat() / 10.f;
			y = itr["y"].GetFloat() / 10.f;
			w = itr["width"].GetFloat() / 10.f;
			h = itr["height"].GetFloat() / 10.f;
			m_entities.push_back(EntityFactory::SpawnStaticBox(x, y, w, h));

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
			x = itr["x"].GetFloat() / 10.f;
			y = itr["y"].GetFloat() / 10.f;
			w = itr["width"].GetFloat() / 10.f;
			h = itr["height"].GetFloat() / 10.f;
			m_entities.push_back(EntityFactory::SpawnSoftBox(x, y, w, h));

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
			x = itr["x"].GetFloat() / 10.f;
			y = itr["y"].GetFloat() / 10.f;
			w = itr["width"].GetFloat() / 10.f;
			h = itr["height"].GetFloat() / 10.f;
			priority = itr["priority"].GetFloat() / 10.f;
			directionX = itr["directionX"].GetFloat() / 10.f;
			directionY = itr["directionY"].GetFloat() / 10.f;
			m_entities.push_back(EntityFactory::SpawnDirectionVolume(x, y, w, h, priority, Vector2D(directionX, directionY)));

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
