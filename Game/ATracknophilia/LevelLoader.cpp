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

void LevelLoader::loadLevel(LEVELS lvl)
{
	destroyLevel();
	FILE* file = new FILE();
	fopen_s(&file, m_paths[lvl], "rb");
	char readBuffer[65536];
	rapidjson::FileReadStream is(file, readBuffer, sizeof(readBuffer));
	rapidjson::Document document;
	document.ParseStream(is);
	fclose(file);

	for (const auto& itr : document["objects"].GetArray())
	{
		float x, y, w, h;
		x = itr["x"].GetFloat() / 10.f;
		y = itr["y"].GetFloat() / 10.f;
		w = itr["width"].GetFloat() / 10.f;
		h = itr["height"].GetFloat() / 10.f;
		EntityFactory::SpawnStaticBox(x, y, w, h);
	}

	for (const auto& itr : document["softbox"].GetArray())
	{
		float x, y, w, h;
		x = itr["x"].GetFloat() / 10.f;
		y = itr["y"].GetFloat() / 10.f;
		w = itr["width"].GetFloat() / 10.f;
		h = itr["height"].GetFloat() / 10.f;
		EntityFactory::SpawnSoftBox(x, y, w, h);
	}
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