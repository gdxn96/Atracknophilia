#pragma once
#include "SceneManager.h"
#include <iostream>
using namespace std;

#include "Renderer.h"

class Scene
{
public:

	Scene(Scenes title);

	//called automatically when a scene becomes active, used in sceneMgr
	virtual void enter();

	//called automatically when a scene becomes inactive, used in sceneMgr
	virtual void exit();

	virtual void destroy();

	//simple method that returns the title of the scene, used in sceneMgr
	const Scenes getTitle();

	virtual void update(float dt) = 0;
	virtual void render(Renderer & r) = 0;
	// adding this to init the scenes
	virtual bool init(Renderer & r) = 0;

	// adding to be able to change scenes on a certain event
	virtual void changeScene(Scenes newScene) = 0;

protected:
	Scenes m_title;
};