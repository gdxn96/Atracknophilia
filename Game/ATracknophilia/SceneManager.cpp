#include "stdafx.h" 
#include "SceneManager.h"

SceneManager * SceneManager::instance = 0;

SceneManager::SceneManager() : m_currScene(nullptr)
{

}

void SceneManager::destroy()
{
	for (auto& scene : m_scenes)
	{
		scene->destroy();
	}
}

void SceneManager::update(float dt)
{
	//dynamic typing
	if (m_currScene != nullptr)
	{
		m_currScene->update(dt);
	}

}

void SceneManager::render(Renderer & r)
{
	//dynamic typing
	if (m_currScene != nullptr)
	{
		m_currScene->render(r);
	}
}

SceneManager * SceneManager::getInstance()
{
	//singleton getter
	if (instance == 0)
	{
		instance = new SceneManager();
	}
	return instance;
}

void SceneManager::switchTo(Scenes title)
{
	bool sceneFound = false;
	int i = 0;
	Scene* nextScene = nullptr;

	//checks if the scene is there, if it isn't, do nothing
	while (i < m_scenes.size() && !sceneFound)
	{
		if (m_scenes.at(i)->getTitle() == title)
		{
			sceneFound = true;
			nextScene = m_scenes.at(i);
		}
		i++;
	}

	if (sceneFound)
	{
		if (m_currScene != nullptr)
		{
			//exit the old scene 
			m_currScene->exit();
		}

		//enter the new scene
		m_currScene = nextScene;
		m_currScene->enter();
	}
	else
	{
		printf("scene not found");
	}
}

Scene * SceneManager::getCurrentScene()
{
	return m_currScene;
}

void SceneManager::addScene(Scene* newScene)
{
	m_scenes.push_back(newScene);
}

void SceneManager::init(Renderer & r)
{
	//m_currScene->init();
	for (int i = 0; i < m_scenes.size(); i++)
	{
		m_scenes.at(i)->init(r); // init all the scenes data
	}
}