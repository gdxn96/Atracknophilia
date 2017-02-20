#pragma once
#pragma once
#include <vector>
#include "sdl/SDL.h"
#include "box2d/Box2D.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/reader.h"
#include "ECSInterfaces.h"
#include <unordered_map>
#include "Components.h"

enum class LEVELS {PROTOTYPE};

class LevelLoader
{
public:
	static void RegisterLevels(std::vector<std::pair<LEVELS, const char*>> map);
	static void loadLevel(LEVELS lvl);
	static void destroyLevel();
	static void destroyObjects();
	static void appendToEntities(IEntity* entity);
private:
	static std::unordered_map<LEVELS, const char *> m_paths;
	static std::vector<IEntity*> m_entities;
};