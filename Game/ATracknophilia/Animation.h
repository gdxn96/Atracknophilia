#pragma once

#include "Resource.h"

class Animation
{
public:
	Animation(string _animationName, Rect _position);
	Animation();

	~Animation();

	void update(float dt);
	void draw(Renderer& r);

	void changeAnimation(string name);
	void resetAnimation();

	void setLooping(bool _isLooping);
	void setFramesPerSecond(float _framesPerSecond);

	void setPosition(Rect dest);

	bool isAlive();

	void setScale(float s);
	
	void setAngleInRadians(float a);

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