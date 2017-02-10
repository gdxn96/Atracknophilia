#pragma once
#include "AutoList.h"

template<typename T>
T* getComponentById(int id)
{
	auto& list = AutoList::get<T>();
	for (auto& el : list)
	{
		if (el->ID == id)
		{
			return el;
		}
	}

	return nullptr;
}

class ISystem
{
public:
	virtual void process() = 0;
};

struct IComponent : public AutoLister<IComponent>
{
	IComponent(int id) : ID(id) {};

	template<typename T>
	T* getComponent()
	{
		return getComponentById<T>(ID);
	}

	virtual ~IComponent() {};
	const int ID;
};

class IEntity : public AutoLister<IEntity>
{
public:
	IEntity(int id, std::vector<IComponent*> list) : ID(id), m_components(list)
	{
	}
	const int ID;
protected:
	std::vector<IComponent*> m_components;

};