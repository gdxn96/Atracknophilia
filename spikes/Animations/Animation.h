#pragma once

#include "ResourceManager.h"

class Animation
{
public:
	Animation(string _animationName, SDL_Rect _position);
	~Animation();

	void update(float dt);
	void changeAnimation(string name);

	void resetAnimation();

	void SetLooping(bool _isLooping);
	void setFramesPerSecond(float _framesPerSecond);

	void setPosition(SDL_Rect dest);

	bool isAlive();

	void setScale(float s);
	void draw(SDL_Renderer& r);

private:
	SDL_Texture* m_currentSpriteSheet;
	int m_maxCellHeight;
	int m_maxCellWidth;
	bool m_isAlive;
	bool m_isLooping;
	string m_selectedAnimation;
	float m_animationScale;
	SDL_Rect m_dest;
	vector<SDL_Rect> m_currentFrames;
	float m_timeSinceLastFrame;
	SDL_Rect m_currentFrame;
	int m_frameIndex;

	float FPS;
};