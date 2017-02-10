#include "stdafx.h"
#include "Animation.h"

Animation::Animation(string _animationName, Rect _position) 
	: m_maxCellHeight(0)
	, m_maxCellWidth(0)
	, m_isAlive(true)
	, m_isLooping(true)
	, m_animationScale(1.2)
	, m_timeSinceLastFrame(0)
	, m_angle(0)
	, FPS(0.25f)
	, m_selectedAnimation(_animationName)
	, m_currentSpriteSheet(nullptr)
	, m_currentFrame(Rect())
	, m_dest(_position)
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

Animation::Animation()
	: m_maxCellHeight(0)
	, m_maxCellWidth(0)
	, m_isAlive(false)
	, m_isLooping(false)
	, m_animationScale(1.0)
	, m_timeSinceLastFrame(0)
	, m_angle(0)
	, FPS(0)
	, m_selectedAnimation("")
	, m_currentSpriteSheet(nullptr)
	, m_currentFrame(Rect())
	, m_dest(Rect())
{}

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
				m_frameIndex = 0;
				m_currentFrame = m_currentFrames.at(m_frameIndex);
			}
		}

		m_timeSinceLastFrame = 0;
	}
}
void Animation::changeAnimation(string _animationName)
{
	m_selectedAnimation = _animationName;
	resetAnimation();
}

void Animation::resetAnimation()
{
	m_frameIndex = 0;
	auto& data = ResourceManager::getInstance()->getAnimationByKey(m_selectedAnimation);
	m_currentSpriteSheet = data.first;
	m_currentFrames = data.second;
}

void Animation::setLooping(bool _isLooping)
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

void Animation::setAngleInRadians(float a)
{
	m_angle = a;
}

void Animation::draw(Renderer* r)
{
	if (m_isAlive)
	{
		float angle = m_angle * (180 / 3.14);

		r->drawTextureWithAngle(m_currentSpriteSheet, m_currentFrame, m_dest, angle);
	}
}