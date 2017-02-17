#pragma once
#include "sdl/SDL.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include<map>
#include<vector>
#include<iostream>
#include<queue>
#include<thread>
#include<functional>
#include "Vector2D.h"

class EventListener
{
public:
	enum Event {
		UNKNOWN = 0,

		// Controller
		BUTTON_INVALID = 999,
		BUTTON_A = 1000,
		BUTTON_B,
		BUTTON_X,
		BUTTON_Y,
		BUTTON_BACK,
		BUTTON_GUIDE,
		BUTTON_START,
		BUTTON_LEFTSTICK,
		BUTTON_RIGHTSTICK,
		BUTTON_LEFTSHOULDER,
		BUTTON_RIGHTSHOULDER,
		BUTTON_DPAD_UP,
		BUTTON_DPAD_DOWN,
		BUTTON_DPAD_LEFT,
		BUTTON_DPAD_RIGHT,
		TRIGGER_SOFT_LEFT,
		TRIGGER_LEFT,
		TRIGGER_SOFT_RIGHT,
		TRIGGER_RIGHT,

		MOUSE_WHEEL_UP,
		MOUSE_WHEEL_DOWN
	};

	enum Type {
		Press,
		Release,
		Hold,
		None
	};

	virtual void onEvent(Event) = 0;
};

class Command
{
public:
	Command(std::function<void()> function) : m_function(function) {}
	Command(std::function<void()> function, EventListener::Type type) : m_function(function), m_type(type) { m_functions.push_back(m_function); }

	virtual ~Command() {}

	std::function<void()> m_function;
	std::vector<std::function<void()>> m_functions;

	EventListener::Type m_type;

	virtual void execute() {};
	virtual void executePress() {};
	virtual void executeRelease() {};
	virtual void executeHold() {};

	void clearKeys()
	{
		for (std::vector<std::function<void()>>::iterator it = m_functions.begin(); it != m_functions.end(); ++it)
		{
			delete &it;
		}
	}
};

class InputManager
{
public:
	static InputManager* getInstance();
	InputManager();
	~InputManager();

	void ProcessInput();
	void AddListener(EventListener::Event, EventListener*);
	void AddKey(EventListener::Event, Command*, EventListener* x = nullptr);
	void ResetKey(EventListener::Event);

	// Controller
	Command* Button_INVALID;
	Command* Button_A;
	Command* Button_B;
	Command* Button_X;
	Command* Button_Y;
	Command* Button_BACK;
	Command* Button_GUIDE;
	Command* Button_START;
	Command* Button_LEFTSTICK;
	Command* Button_RIGHTSTICK;
	Command* Button_LEFTSHOULDER;
	Command* Button_RIGHTSHOULDER;
	Command* Button_DPAD_UP;
	Command* Button_DPAD_DOWN;
	Command* Button_DPAD_LEFT;
	Command* Button_DPAD_RIGHT;
	Command* Trigger_SOFT_LEFT;
	Command* Trigger_LEFT;
	Command* Trigger_SOFT_RIGHT;
	Command* Trigger_RIGHT;

	Command* Mouse_Wheel_Up;
	Command* Mouse_Wheel_Down;

	Vector2D GetLeftStickVector();
	Vector2D GetLeftStickVectorNormal();
	float GetLeftStickAngle();
	float GetLeftTrigger();

	Vector2D GetRightStickVector();
	Vector2D GetRightStickVectorNormal();
	float GetRightStickAngle();
	float GetRightTrigger();

	void SetStickDeadZone(int deadZone);

private:
	static InputManager*											m_instance;
	std::map<EventListener::Event, std::vector<EventListener*>*>	listeners;
	std::map<EventListener::Event, bool>							beingHeld;
	std::map<EventListener::Event, std::vector<Command*>*>			commands;

	void Dispatch(EventListener::Type, EventListener::Event);
	void SetPrevious(EventListener::Event, bool);
	void CheckPrevious(EventListener::Type, EventListener::Event);
	void AddCommand(EventListener::Event, Command*);
	void Execute(EventListener::Type, EventListener::Event);
	Command*& bindCommand(EventListener::Event);
	void AddController(int id);
	void RemoveController(int id);

	std::map<EventListener::Event, bool>	controllerHeld;
	int										countedButtonFrames = 0;
	int										countedTriggerFrames = 0;
	int										controllerButtonDelay = 1;
	int										controllerTriggerDelay = 500;
	int										ID;

	SDL_GameController*						mGameController = SDL_GameControllerOpen(0);
	SDL_Joystick*							mJoyStick = SDL_JoystickOpen(0);

	EventListener::Event					mControllerButton;
	bool									mIsConnected = false;
	bool									mIsPressed = false;

	int										stick_Dead_Zone = 4000;

	float									stick_Left_X = 0;
	float									stick_Left_Y = 0;
	float									stick_Left_T = 0;

	float									stick_Right_X = 0;
	float									stick_Right_Y = 0;
	float									stick_Right_T = 0;

	std::map<EventListener::Event, std::string> keyNames;
	std::map<EventListener::Type, std::string> keyTypes;

	EventListener::Event previousEvent;
	float holdDuration = 0;
};