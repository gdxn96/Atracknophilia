#include "stdafx.h"
#include "Animation.h"

using namespace std;

Animation::Animation(string _animationName, Rect _position) : FPS(0.5f), m_maxCellHeight(0), m_maxCellWidth(0), m_isAlive(true), m_isLooping(true), m_selectedAnimation(_animationName), m_animationScale(1.2), m_dest(_position)
{
	auto& data = ResourceManager::getInstance()->getAnimationByKey(_animationName);
	m_currentSpriteSheet = data.first;
	m_currentFrames = data.second;

	for (int i = 0; i < m_currentFrames.size(); i++)
	{
		if (m_currentFrames[i].size.w > m_maxCellWidth)
		{
			m_maxCellWidth = m_currentFrames[i].size.w;
		}
		if (m_currentFrames[i].size.h > m_maxCellHeight)
		{
			m_maxCellHeight = m_currentFrames[i].size.h;
		}
	}
}

Animation::~Animation() {}

void Animation::update(float dt)
{
	m_timeSinceLastFrame += dt;
	if (m_timeSinceLastFrame > FPS && m_isAlive)
	{
		if (m_frameIndex < m_currentFrames.size() - 1)
		{
			//increment frame
			m_frameIndex++;
			m_currentFrame = m_currentFrames.at(m_frameIndex);
		}
		else
		{
			if (!m_isLooping)
			{
				m_isAlive = false;
			}
			else
			{
				resetAnimation();
				m_currentFrame = m_currentFrames.at(m_frameIndex);
			}
		}

		m_timeSinceLastFrame = 0;
	}
}
void Animation::changeAnimation(string _animationName)
{
	m_selectedAnimation = _animationName;
}

void Animation::resetAnimation()
{
	m_frameIndex = 0;
	auto& data = ResourceManager::getInstance()->getAnimationByKey(m_selectedAnimation);
	m_currentSpriteSheet = data.first;
	m_currentFrames = data.second;
}

void Animation::SetLooping(bool _isLooping)
{
	m_isLooping = _isLooping;
}
void Animation::setFramesPerSecond(float _framesPerSecond)
{
	FPS = 1 / _framesPerSecond;
}

void Animation::setPosition(Rect dest)
{
	m_dest = dest;
}

bool Animation::isAlive()
{
	return m_isAlive;
}

void Animation::setScale(float s)
{
	m_animationScale = s;
}

void Animation::draw(Renderer& r)
{
	if (m_isAlive)
	{
		SDL_Rect _src;
		_src.w = m_currentFrame.size.w;
		_src.h = m_currentFrame.size.h;
		_src.x = m_currentFrame.pos.x;
		_src.y = m_currentFrame.pos.y;

		SDL_Rect _dest;
		_dest.w = _src.w;
		_dest.h = _src.h;
		_dest.x = 640;
		_dest.y = 360;

		SDL_RenderCopy(r.getRenderer(), m_currentSpriteSheet, &_src, &_dest);
		//r.drawRectOutline(m_dest, Colour(255, 255, 255, 255));
	}
}