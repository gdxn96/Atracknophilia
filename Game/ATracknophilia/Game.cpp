#include "stdafx.h"
#include "Game.h"

bool Game::quit = false;

void Game::init()
{
	m_renderer.init(Size2D(1280, 720), "Whatever", nullptr);
}

void Game::update(float dt)
{
}

void Game::render()
{
	m_renderer.clear(Colour(0,0,0));

	m_renderer.present();
}
