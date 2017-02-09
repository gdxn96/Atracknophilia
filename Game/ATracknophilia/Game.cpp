#include "stdafx.h"
#include "Game.h"


bool Game::quit = false;

static b2Vec2& Gravity()
{
	static b2Vec2 gravity(0, 20);
	return gravity;
}

static b2World& World()
{
	static b2World world(Gravity());
	return world;
}

Game::Game(Vector2D windowSize, Vector2D levelSize, const char* windowName) : m_camera()
{
	m_camera.init(windowSize.x, windowSize.h, m_renderer.getRenderer());
	m_renderer.init(windowSize, windowName, &m_camera);


	b2BodyDef bodyDef;

	bodyDef.position.Set(300, 300);
	bodyDef.type = b2_staticBody;

	m_body = World().CreateBody(&bodyDef);	

	m_box.SetAsBox(100, 100);

	b2FixtureDef fixture;

	fixture.shape = &m_box;
	fixture.density = 1.0f;

	m_body->CreateFixture(&fixture);


	b2BodyDef dBodyDef;

	dBodyDef.position.Set(300, 0);
	dBodyDef.type = b2_dynamicBody;

	m_dBody = World().CreateBody(&dBodyDef);

	m_dBox.SetAsBox(25, 25);

	b2FixtureDef dFixture;

	dFixture.shape = &m_dBox;
	dFixture.density = 1.0f;

	m_dBody->CreateFixture(&dFixture);
}

void Game::init()
{
	InputManager::GetInstance()->AddKey(EventListener::Event::MOUSE_WHEEL_DOWN, new Command(std::bind(&Camera2D::Camera::zoom, &m_camera, -1), EventListener::Type::Press));
	InputManager::GetInstance()->AddKey(EventListener::Event::MOUSE_WHEEL_UP, new Command(std::bind(&Camera2D::Camera::zoom, &m_camera, 1), EventListener::Type::Press));
}

void Game::update(float dt)
{
	World().Step(1.0f / 60, 6, 3);
}

void Game::render()
{
	m_renderer.clear(Colour(0,0,0));

	m_renderer.drawRect(Rect(Vector2D(0, 0), Vector2D(100, 100)), Colour());
	m_renderer.drawBox2DPolygon(m_body);
	m_renderer.drawBox2DPolygon(m_dBody);

	m_renderer.present();
}
