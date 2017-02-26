#pragma once
#include "LTimer.h"
#include "Renderer.h"
#include "FLInput\FLInputManager.h"
#include "Animation.h"
#include "ECSInterfaces.h"
#include "CameraManager.h"
#include "Systems.h"
#include "GameScene.h"
#include "EndGameScene.h"
#include "StartScene.h"

class Game : public EventListener
{
public:
	Game(Vector2D windowSize, Vector2D levelSize, const char* windowName);
	void init();
	void loop(float dt);
	static bool quit;	
private:
	Renderer m_renderer;
	Camera2D::Camera m_camera;

	b2Body* m_body;
	b2PolygonShape m_box;
	CameraManager m_cameraManager;

	ResourceManager* m_resourceMgr;
	std::vector<ISystem*> m_systems;
};
