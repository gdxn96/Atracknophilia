#include "stdafx.h"
#include "Animation.h"

Animation::Animation(string _animationName, SDL_Rect _position) : FPS(0.05f), m_maxCellHeight(0), m_maxCellWidth(0), m_isAlive(true), m_isLooping(true), m_selectedAnimation(_animationName), m_animationScale(1.2), m_dest(_position)
{
	m_currentSpriteSheet = ResourceManager::getInstance()->getAnimationByKey(_animationName).first;
	m_currentFrames = ResourceManager::getInstance()->getAnimationByKey(_animationName).second;

	for (int i = 0; i < m_currentFrames.size(); i++)
	{
		if (m_currentFrames[i].w > m_maxCellWidth)
		{
			m_maxCellWidth = m_currentFrames[i].w;
		}
		if (m_currentFrames[i].h > m_maxCellHeight)
		{
			m_maxCellHeight = m_currentFrames[i].h;
		}
	}
}
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

void Animation::setPosition(SDL_Rect dest)
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

void Animation::draw(SDL_Renderer& r)
{
	if (m_isAlive)
	{
		//r.drawTexture(m_currentSpriteSheet, m_currentFrame, m_dest.ScaleCopy(m_animationScale));
		//r.drawRectOutline(m_dest, Colour(255, 255, 255, 255));
	}
}