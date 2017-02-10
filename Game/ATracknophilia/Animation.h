#pragma once

#include "Resource.h"

class Animation
{
public:
	Animation(string _animationName);
	Animation();

	~Animation();

	void update(float dt);
	void drawAtPosition(Renderer* r, Vector2D pos, Vector2D size, float angle = 0);

	void changeAnimation(string name);
	void resetAnimation();

	void setLooping(bool _isLooping);
	void setFramesPerSecond(float _framesPerSecond);

	bool isAlive();

	void setScale(float s);

private:
	int					m_maxCellHeight;
	int					m_maxCellWidth;
	int					m_frameIndex;
	bool				m_isAlive;
	bool				m_isLooping;
	float				m_animationScale;
	float				m_timeSinceLastFrame;
	float				m_angle;
	float				FPS;
	string				m_selectedAnimation;
	
	vector<Rect>		m_currentFrames;
	SDL_Texture*		m_currentSpriteSheet;
	Rect				m_currentFrame;
	Rect				m_dest;
};