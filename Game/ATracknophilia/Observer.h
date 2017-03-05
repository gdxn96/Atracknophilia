#pragma once

class Observer
{
public:
	enum Event
	{
		START_RACE,			// need gameplay polish
		HOOK,				// DONE
		SWAP_SHOT,			// DONE
		SHOOT,				// DONE
		DROP,				// DONE
		HIT,				// DONE
		DYING,				// need gameplay polish
		SIREN,				// need gameplay polish
		JUMP,				// DONE
		BUTTON_MOVE,		// need menus
		BUTTON_CLICK,		// need menus
		MAIN_MENU,			// need menus
		GAME_SCENE,			// need menus
		CREDITS				// need menus
	};

	virtual ~Observer() {}
	virtual void onNotify(Event event) = 0;
};
