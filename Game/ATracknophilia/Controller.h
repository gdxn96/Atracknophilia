#pragma once
#include "ECSInterfaces.h"
#include "Dimensional.h"
#include "FLInput\FLInputManager.h"

class PressCommand : public Command
{
public:
	PressCommand(std::function<void()> fn) : Command(fn, EventListener::Type::Press) {};
	void executePress() {
		m_function();
	};

private:

};
class HoldCommand : public Command
{
public:
	HoldCommand(std::function<void()> fn) : Command(fn, EventListener::Type::Hold) {};
	void executeHold() {
		m_function();
	};
private:

};
class ReleaseCommand : public Command
{
public:
	ReleaseCommand(std::function<void()> fn) : Command(fn, EventListener::Type::Release) {};
	void executeRelease() {
		m_function();
	};

private:

};


struct IControllerComponent : public IComponent, public AutoLister<IControllerComponent>
{
	IControllerComponent(int id) : IComponent(id)
	{

	}

	virtual void process() = 0;
};

struct PlayerControllerComponent : public IControllerComponent
{
	PlayerControllerComponent(int id);

	void process() override;
};