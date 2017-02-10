#include "stdafx.h"
#include "LevelLoader.h"
#include "Entities.h"

std::unordered_map<LEVELS, const char*> LevelLoader::m_paths;
std::vector<IEntity> LevelLoader::m_entities;

void LevelLoader::RegisterLevels(std::vector<std::pair<LEVELS, const char*>> map)
{
	for (auto element : map)
	{
		m_paths[element.first] = element.second;
	}
}

void LevelLoader::loadLevel(LEVELS lvl)
{
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
		m_entities.push_back(StaticBox(id(), x, y, w, h));
	}
}

void LevelLoader::destroyLevel()
{
	m_entities.clear();
}
