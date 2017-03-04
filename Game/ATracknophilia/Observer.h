#pragma once

class Observer
{
public:
	enum Event
	{
		START_RACE,
		HOOK,
		SWAP_SHOT,
		SHOOT,
		DROP,
		HIT,
		DYING,
		SIREN,
		LAND,
		MAIN_MENU,
		GAME_SCENE,
		CREDITS
	};

	virtual ~Observer() {}
	virtual void onNotify(Event event) = 0;
};
