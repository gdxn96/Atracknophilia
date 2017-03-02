#pragma once
#include "SceneManager.h"
#include "ECSInterfaces.h"
#include "Systems.h"
#include "Animation.h"
#include "CameraManager.h"


class GameScene : public Scene
{
public:
	GameScene(CameraManager * cameraManager);

	void update(float dt) override;
	void render(Renderer& r) override;
	void destroy() override;
	void enter() override;

	bool init(Renderer & r) override;

	void changeScene(Scenes newScene) override;

	void initialiseMapLvls(int mapLvl);
	void initialiseGameScenePlayerIDs(vector<int> playerIDs);
	void initAiEnabled(bool aiEnabled);

private:
	CameraManager * m_cameraManager;
	Vector2D m_currentLvl;
	vector<int> m_playerIds;
	int m_mapLvl;
	bool m_aiEnabled;
};