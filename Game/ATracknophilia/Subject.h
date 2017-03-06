#pragma once

#include "Observer.h"
#include <vector>

class Subject
{
public:
	void addObserver(Observer* observer)
	{
		observers.push_back(observer);
		numObservers++;
	}

	~Subject() 
	{
		observers.clear();
	}

private:
	std::vector<Observer*> observers;
	int numObservers = 0;

protected:
	void notify(Observer::Event event)
	{
		for (int i = 0; i < numObservers; i++)
		{
			observers[i]->onNotify(event);
		}
	}
};
