#include "stdafx.h"
#include "FiniteStateMachine.h"


//FiniteStateMachine::FiniteStateMachine()
//{
//}
//
//
//FiniteStateMachine::~FiniteStateMachine()
//{
//}

Idle::Idle(bool left)
{
	m_left = left;
	type = "idle";
}

void Idle::update(float dt)
{
	//if (player condition met)
	//{
	//	change state
	//}
	//else if (...)
	//{
	//	change state
	//}
	//p->getComponent<AnimationComponent>()->state = new Running();
}

Running::Running(bool left)
{
	m_left = left;
	type = "running";
}

void Running::update(float dt)
{
}

void Jumping::update(float dt)
{
}

void Falling::update(float dt)
{
}

void Landing::update(float dt)
{
}

void Attacking::update(float dt)
{
}

void Hitting::update(float dt)
{
}




