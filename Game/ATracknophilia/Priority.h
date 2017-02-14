#pragma once
#include "ECSInterfaces.h"

struct PriorityComponent : public IComponent, public AutoLister<PriorityComponent>
{
	PriorityComponent(int id, int priority) 
		:	IComponent(id)
		,	m_priority(priority)
	{
	}

	int m_priority;
};
