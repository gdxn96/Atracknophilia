#pragma once
#include <vector>
#include <algorithm>
#include <iostream>

namespace AutoList
{
	template<typename T>
	std::vector<T *>& get()
	{
		static std::vector<T *> instances;
		return instances;
	}
}

//Automagically lists every object that inherits from it
//must pass type of self in as template param see: CRTP
//access list by calling AutoList::get<TYPE>();
template<typename T>
class AutoLister
{
public:
	AutoLister()
	{
		AddElement<T>(static_cast<T *>(this));
	}

	template<typename T>
	static void RemoveElement(T* element)
	{
		auto& instances = AutoList::get<T>();
		instances.erase(std::remove(instances.begin(), instances.end(), element), instances.end());
	}

	template<typename T>
	static void AddElement(T* element)
	{
		auto& instances = AutoList::get<T>();
		instances.push_back(element);
	}

	virtual ~AutoLister()
	{
		RemoveElement<T>(static_cast<T *>(this));
	}
};