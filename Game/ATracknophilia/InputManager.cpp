#include "stdafx.h"
#include "InputManager.h"

InputManager * InputManager::m_instance = nullptr;

InputManager* InputManager::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new InputManager;
	}

	return m_instance;
}

InputManager::InputManager()
{
	auto e = SDL_Init(SDL_INIT_EVERYTHING);

	if (e != 0)
	{
		std::cout << "Error with SDL INIT: " << SDL_Error << std::endl;
	}
}

InputManager::~InputManager() {}

void InputManager::ProcessInput()
{
	SDL_Event evn;

	EventListener::Type type;

	while (SDL_PollEvent(&evn) != 0)
	{
		//* Get Event Listener Type
		switch (evn.type)
		{
		case SDL_KEYDOWN: type = EventListener::Type::Press;	break;
		case SDL_KEYUP: type = EventListener::Type::Release;	break;
		default: type = EventListener::Type::None;				break;
		}

		switch (evn.key.keysym.sym)
		{
		case SDLK_UNKNOWN: Dispatch(type, EventListener::Event::UNKNOWN); break;
		}

		switch (evn.type)
		{
		case SDL_CONTROLLERDEVICEADDED: AddController(evn.cdevice.which);		break;
		case SDL_CONTROLLERDEVICEREMOVED: RemoveController(evn.cdevice.which);	break;
		default: type = EventListener::Type::None;								break;
		}

		if (evn.type == SDL_MOUSEWHEEL)
		{
			type = EventListener::Type::Press;
			if (evn.wheel.y > 0)
			{
				Dispatch(type, EventListener::Event::MOUSE_WHEEL_UP);
				SetPrevious(EventListener::Event::MOUSE_WHEEL_UP, false);
			}
			else if (evn.wheel.y < 0)
			{
				Dispatch(type, EventListener::Event::MOUSE_WHEEL_DOWN);
				SetPrevious(EventListener::Event::MOUSE_WHEEL_DOWN, false);
			}
		}

		if (mIsConnected)
		{
			//* Controller Button Pressed
			if (evn.type == SDL_CONTROLLERBUTTONDOWN)
			{
				//* Set Type
				type = EventListener::Type::Press;
				//* Find Button
				if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_INVALID) { mControllerButton = EventListener::Event::BUTTON_INVALID; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_A) { mControllerButton = EventListener::Event::BUTTON_A; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_B) { mControllerButton = EventListener::Event::BUTTON_B; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_X) { mControllerButton = EventListener::Event::BUTTON_X; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_Y) { mControllerButton = EventListener::Event::BUTTON_Y; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_BACK) { mControllerButton = EventListener::Event::BUTTON_BACK; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_GUIDE) { mControllerButton = EventListener::Event::BUTTON_GUIDE; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_START) { mControllerButton = EventListener::Event::BUTTON_START; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSTICK) { mControllerButton = EventListener::Event::BUTTON_LEFTSTICK; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSTICK) { mControllerButton = EventListener::Event::BUTTON_RIGHTSTICK; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER) { mControllerButton = EventListener::Event::BUTTON_LEFTSHOULDER; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) { mControllerButton = EventListener::Event::BUTTON_RIGHTSHOULDER; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) { mControllerButton = EventListener::Event::BUTTON_DPAD_UP; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) { mControllerButton = EventListener::Event::BUTTON_DPAD_DOWN; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) { mControllerButton = EventListener::Event::BUTTON_DPAD_LEFT; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) { mControllerButton = EventListener::Event::BUTTON_DPAD_RIGHT; }
				//* Set Pressed in map
				controllerHeld[mControllerButton] = true;
				//* Dispatch
				Dispatch(type, mControllerButton);
				//* Used to Delay Hold
				countedButtonFrames = -controllerButtonDelay * 8;
				break;
			}

			else if (evn.type == SDL_CONTROLLERBUTTONUP)
			{
				//* Set Type
				type = EventListener::Type::Release;
				//* Find Button
				if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_INVALID) { mControllerButton = EventListener::Event::BUTTON_INVALID; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_A) { mControllerButton = EventListener::Event::BUTTON_A; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_B) { mControllerButton = EventListener::Event::BUTTON_B; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_X) { mControllerButton = EventListener::Event::BUTTON_X; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_Y) { mControllerButton = EventListener::Event::BUTTON_Y; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_BACK) { mControllerButton = EventListener::Event::BUTTON_BACK; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_GUIDE) { mControllerButton = EventListener::Event::BUTTON_GUIDE; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_START) { mControllerButton = EventListener::Event::BUTTON_START; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSTICK) { mControllerButton = EventListener::Event::BUTTON_LEFTSTICK; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSTICK) { mControllerButton = EventListener::Event::BUTTON_RIGHTSTICK; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER) { mControllerButton = EventListener::Event::BUTTON_LEFTSHOULDER; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) { mControllerButton = EventListener::Event::BUTTON_RIGHTSHOULDER; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP) { mControllerButton = EventListener::Event::BUTTON_DPAD_UP; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN) { mControllerButton = EventListener::Event::BUTTON_DPAD_DOWN; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) { mControllerButton = EventListener::Event::BUTTON_DPAD_LEFT; }
				else if (evn.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) { mControllerButton = EventListener::Event::BUTTON_DPAD_RIGHT; }
				//* Set Pressed in map
				controllerHeld[mControllerButton] = false;
				//* Dispatch
				Dispatch(type, mControllerButton);
				//* Used to Delay Hold
				countedButtonFrames = -controllerButtonDelay * 8;
				break;
			}

			//* Joystick
			//* Get If Axis Is Moving
			if (evn.type == SDL_JOYAXISMOTION)
			{
				//* Left Stick X Axis
				if (evn.jaxis.axis == 0) { stick_Left_X = evn.jaxis.value; }
				//* Left Stick Y Axis	   
				if (evn.jaxis.axis == 1) { stick_Left_Y = evn.jaxis.value; }
				//* Left Trigger Axis	   
				if (evn.jaxis.axis == 2) { stick_Left_T = evn.jaxis.value; }
				//* Right Stick X Axis	   
				if (evn.jaxis.axis == 3) { stick_Right_X = evn.jaxis.value; }
				//* Right Stick Y Axis	   
				if (evn.jaxis.axis == 4) { stick_Right_Y = evn.jaxis.value; }
				//* Right Trigger Axis	   
				if (evn.jaxis.axis == 5) { stick_Right_T = evn.jaxis.value; }

				// Left Trigger Press/ Relaase
				if (evn.jaxis.axis == 2) {
					if (GetLeftTrigger() > 32000) { Dispatch(EventListener::Type::Press, EventListener::Event::TRIGGER_LEFT); }
					if (GetLeftTrigger() < -32000) { Dispatch(EventListener::Type::Release, EventListener::Event::TRIGGER_LEFT); }
				}

				// Right Trigger Press/ Relaase
				if (evn.jaxis.axis == 5) {
					if (GetRightTrigger() > 32000) { Dispatch(EventListener::Type::Hold, EventListener::Event::TRIGGER_RIGHT); }
					if (GetRightTrigger() < -32000) { Dispatch(EventListener::Type::Hold, EventListener::Event::TRIGGER_RIGHT); }
				}
				break;
			}
		}
	}
}

void InputManager::AddListener(EventListener::Event evt, EventListener* listener)
{
	if (listeners.find(evt) == listeners.end())
	{
		listeners[evt] = new std::vector<EventListener*>();
	}

	listeners[evt]->push_back(listener);
}

void InputManager::AddKey(EventListener::Event evt, Command* command, EventListener* listener)
{
	Command*& toBind = bindCommand(evt);

	toBind = command;

	AddListener(evt, listener);

	AddCommand(evt, toBind);
}

void InputManager::ResetKey(EventListener::Event evt)
{
	commands[evt]->clear();
	listeners[evt]->clear();
}

void InputManager::Dispatch(EventListener::Type type, EventListener::Event evt)
{
	if (listeners.find(evt) != listeners.end())
	{
		for (auto const &listener : *listeners[evt])
		{
			if (listener != nullptr)
				listener->onEvent(evt);
		}
	}

	CheckPrevious(type, evt);
}

void InputManager::SetPrevious(EventListener::Event evt, bool isHeld) { beingHeld[evt] = isHeld; }

void InputManager::CheckPrevious(EventListener::Type type, EventListener::Event evt)
{
	if (type == EventListener::Type::Release)
	{
		SetPrevious(evt, false);
	}

	if (beingHeld[evt])
	{
		type = EventListener::Type::Hold;
	}

	Execute(type, evt);
}

void InputManager::AddCommand(EventListener::Event evt, Command* command)
{
	if (commands.find(evt) == commands.end())
	{
		commands[evt] = new std::vector<Command*>();
	}

	commands[evt]->push_back(command);
}

void InputManager::Execute(EventListener::Type type, EventListener::Event evt)
{
	if (evt != 0)
	{

		if (type != EventListener::Type::Hold)
		{
			std::string newLine =
				keyNames[evt] + ","
				+ keyTypes[type] + ","
				+ "" + ",";
			//+ GetTimeStamp(false);
			//logEvent(newLine);
			previousEvent = evt;
		}

		else if (type == EventListener::Type::Hold)
		{
			holdDuration++;
			//logFileValues.pop_back();
			std::string newLine =
				keyNames[evt] + ","
				+ keyTypes[type] + ","
				+ std::to_string(holdDuration / 20) + ",";
			//+ GetTimeStamp(false);
			//logEvent(newLine);
			previousEvent = evt;
		}
		if (previousEvent == evt && type == EventListener::Type::Release)
		{
			holdDuration = 0;
		}
	}

	if (commands.find(evt) != commands.end())
	{
		for (auto const &command : *commands[evt])
		{
			if (type == EventListener::Type::Press)
			{
				command->executePress();
			}
			else if (type == EventListener::Type::Release)
			{
				command->executeRelease();
			}
			else if (type == EventListener::Type::Hold)
			{
				command->executeHold();
			}
			else
			{
				command->execute();
			}
		}
	}

	if (type == EventListener::Type::Press)
	{
		SetPrevious(evt, true);
	}
}

Command*& InputManager::bindCommand(EventListener::Event evt)
{
	if (evt == EventListener::Event::MOUSE_WHEEL_UP) { return  Mouse_Wheel_Up; }
	if (evt == EventListener::Event::MOUSE_WHEEL_DOWN) { return  Mouse_Wheel_Down; }


	if (evt == EventListener::Event::BUTTON_INVALID) { return Button_INVALID; }
	if (evt == EventListener::Event::BUTTON_A)
	{
		return Button_A;
	}
	if (evt == EventListener::Event::BUTTON_B) { return Button_B; }
	if (evt == EventListener::Event::BUTTON_X) { return Button_X; }
	if (evt == EventListener::Event::BUTTON_Y) { return Button_Y; }
	if (evt == EventListener::Event::BUTTON_BACK) { return Button_BACK; }
	if (evt == EventListener::Event::BUTTON_GUIDE) { return Button_GUIDE; }
	if (evt == EventListener::Event::BUTTON_START) { return Button_START; }
	if (evt == EventListener::Event::BUTTON_LEFTSTICK) { return Button_LEFTSTICK; }
	if (evt == EventListener::Event::BUTTON_RIGHTSTICK) { return Button_RIGHTSTICK; }
	if (evt == EventListener::Event::BUTTON_LEFTSHOULDER) { return Button_LEFTSHOULDER; }
	if (evt == EventListener::Event::BUTTON_RIGHTSHOULDER) { return Button_RIGHTSHOULDER; }
	if (evt == EventListener::Event::BUTTON_DPAD_UP) { return Button_DPAD_UP; }
	if (evt == EventListener::Event::BUTTON_DPAD_DOWN) { return Button_DPAD_DOWN; }
	if (evt == EventListener::Event::BUTTON_DPAD_LEFT) { return Button_DPAD_LEFT; }
	if (evt == EventListener::Event::BUTTON_DPAD_RIGHT) { return Button_DPAD_RIGHT; }

	//* Controller Triggers
	if (evt == EventListener::Event::TRIGGER_SOFT_LEFT) { return Button_DPAD_UP; }
	if (evt == EventListener::Event::TRIGGER_LEFT) { return Button_DPAD_DOWN; }
	if (evt == EventListener::Event::TRIGGER_SOFT_RIGHT) { return Button_DPAD_LEFT; }
	if (evt == EventListener::Event::TRIGGER_RIGHT) { return Button_DPAD_RIGHT; }
}

void InputManager::RemoveController(int id)
{
	SDL_GameControllerClose(mGameController);
	mIsConnected = false;
}

void InputManager::AddController(int id)
{
	//* Assign Current Controller
	if (SDL_IsGameController(id))
	{
		mGameController = SDL_GameControllerOpen(id);
		mIsConnected = true;
		/*mJoyStick = SDL_JoystickOpen(id);
		int instanceID = SDL_JoystickInstanceID(mJoyStick);*/

		/*else if (!mSecondIsConnected)
		{
		mGameController2 = SDL_GameControllerOpen(id);
		mSecondIsConnected = true;
		mJoyStick2 = SDL_JoystickOpen(id);
		int instanceID = SDL_JoystickInstanceID(mJoyStick2);
		}*/

		if (mGameController)
		{
			//* Assign Joysticks
			mJoyStick = SDL_JoystickOpen(id);
			int instanceID = SDL_JoystickInstanceID(mJoyStick);
		}
	}
}

Vector2D InputManager::GetLeftStickVector()
{
	if (Vector2D(stick_Left_X, stick_Left_Y).Magnitude() > stick_Dead_Zone)
	{
		return Vector2D(stick_Left_X, stick_Left_Y);
	}
	else
	{
		return Vector2D(0, 0);
	}
}

Vector2D InputManager::GetLeftStickVectorNormal()
{
	if (Vector2D(stick_Left_X, stick_Left_Y).Magnitude() > stick_Dead_Zone)
	{
		return Vector2D(stick_Left_X, stick_Left_Y).Normalize();
	}
	else
	{
		return Vector2D(0, 0);
	}
}

float InputManager::GetLeftStickAngle() { return (180 - (180 * (atan2(stick_Left_X, stick_Left_Y)) / M_PI)); }

float InputManager::GetLeftTrigger() { return stick_Left_T; }

Vector2D InputManager::GetRightStickVector()
{
	if (Vector2D(stick_Right_X, stick_Right_Y).Magnitude() > stick_Dead_Zone)
	{
		return Vector2D(stick_Right_X, stick_Right_Y);
	}
	else
	{
		return Vector2D(0, 0);
	}
}

Vector2D InputManager::GetRightStickVectorNormal()
{
	if (Vector2D(stick_Right_X, stick_Right_Y).Magnitude() > stick_Dead_Zone)
	{
		return Vector2D(stick_Right_X, stick_Right_Y);
	}
	else
	{
		return Vector2D(0, 0);
	}
}

float InputManager::GetRightStickAngle() { return (180 - (180 * (atan2(stick_Right_X, stick_Right_Y)) / M_PI)); }

float InputManager::GetRightTrigger() { return stick_Right_T; }

void InputManager::SetStickDeadZone(int deadZone){ stick_Dead_Zone = deadZone; }