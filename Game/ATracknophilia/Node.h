#pragma once
#include <memory>
#include <vector>
#include "ECSInterfaces.h"

struct State
{
	Vector2D position;
	Vector2D velocity;
	bool isHooked;
};

class Node
{
public:
	enum class Status
	{
		Invalid,
		Success,
		Failure,
		Running,
	};

	virtual ~Node() {}

	virtual Status Update(IEntity* p) = 0;
	virtual void Initialize() {}
	virtual void Terminate(Status status) {}

	Status Tick(IEntity* p)
	{
		if (status != Status::Running) {
			Initialize();
		}

		status = Update(p);

		if (status != Status::Running) {
			Terminate(status);
		}

		return status;
	}

	bool IsSuccess() const { return status == Status::Success; }
	bool IsFailure() const { return status == Status::Failure; }
	bool IsRunning() const { return status == Status::Running; }
	bool IsTerminated() const { return IsSuccess() || IsFailure(); }
	void Reset() { status = Status::Invalid; }

	//static std::map<IEntity*, Node*> playersLastNode;

protected:
	Status status = Status::Invalid;
};