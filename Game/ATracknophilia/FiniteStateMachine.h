#pragma once
#include "Player.h"

//class FiniteStateMachine
//{
//public:
//	FiniteStateMachine();
//	~FiniteStateMachine();
//};

class IState
{
public:
	virtual ~IState() {}
	virtual void update(float dt)
	{

	}
};

class Idle : public IState
{
public:
	void update(float dt);
private:
};

class Running : public IState
{
public:
	void update(float dt);
private:
};

class Jumping : public IState
{
public:
	void update(float dt);
private:
};

class Falling : public IState
{
public:
	void update(float dt);
private:
};

class Landing : public IState
{
public:
	void update(float dt);
private:
};

class Attacking : public IState
{
public:
	void update(float dt);
private:
};

class Hitting : public IState
{
public:
	void update(float dt);
private:
};

