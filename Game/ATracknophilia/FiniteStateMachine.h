#pragma once
#include <string>

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
	virtual std::string getType()
	{
		return type;
	}
	virtual bool getDirection()
	{
		return m_left;
	}
protected:
	std::string type;
	bool m_left;
};

class Idle : public IState
{
public:
	Idle(bool);
	void update(float dt);
private:
};

class Running : public IState
{
public:
	Running(bool);
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

