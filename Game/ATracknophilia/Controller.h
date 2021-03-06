#pragma once
#include "ECSInterfaces.h"
#include "FLInput\FLInputManager.h"
#include "Subject.h"

class AudioManager;

class PressCommand : public Command
{
public:
	PressCommand(std::function<void()> fn) : m_function(fn), Command(EventListener::EventType::Press) {};
	void executePress() override {
		m_function();
	};

private:
	std::function<void()> m_function;
};
class HoldCommand : public Command
{
public:
	HoldCommand(std::function<void()> fn) : m_function(fn), Command(EventListener::EventType::Hold) {};
	void executeHold() override {
		m_function();
	};
private:
	std::function<void()> m_function;
};
class ReleaseCommand : public Command
{
public:
	ReleaseCommand(std::function<void()> fn) : m_function(fn), Command(EventListener::EventType::Release) {};
	void executeRelease() override {
		m_function();
	};

private:
	std::function<void()> m_function;
};


struct IControllerComponent : public IComponent, public AutoLister<IControllerComponent>
{
	IControllerComponent(int id, Uint8 controllerId) : m_controllerId(controllerId), IComponent(id)
	{

	}

	virtual void process(float dt) = 0;

	Uint8 m_controllerId;
	bool isHooked = false;
};

struct PlayerControllerComponent : public IControllerComponent, public EventListener, public AutoLister<PlayerControllerComponent>, public Subject
{
	PlayerControllerComponent(int id, int controllerId, AudioManager* audioMgr);

	void process(float dt) override;

	bool isHoldingA = false;
	AudioManager* m_audioMgr;
};