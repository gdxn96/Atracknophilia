#pragma once

#include "sdl\SDL.h"
#include "ECSInterfaces.h"
#include "Renderer.h"

class RenderSystem : public ISystem
{
public:
	void init(Renderer* r);
	void process(float dt) override;

private:
	Renderer* m_renderer;
};
