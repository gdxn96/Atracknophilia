#pragma once

#include <vector>

using namespace std;

enum class Scenes { SPLASH, GAME, ENDGAME, CREDITS, OPTIONS, LEVELSELECT };

#include "Scene.h"
#include <vector>
#include "Renderer.h"

class Scene;
class SceneManager
{
public:

	static SceneManager * getInstance();

	SceneManager();

	//update the current scene
	void update(float dt);

	void render(Renderer & r);

	//switch to a scene defined by the Scenes enum ie "Scenes::GAME"
	void switchTo(Scenes scene);

	void destroy();

	//simple getter which tells you the current scene, may not be needed
	Scene * getCurrentScene();

	//adds a scene object to the scene list
	void addScene(Scene* newScene);


	// Adding init method to create the levels
	void init(Renderer & r);

private:
	Scene* m_currScene;
	vector<Scene*> m_scenes;

	static SceneManager * instance;

};