#pragma once
#include "Node.h"

class Decorator : public Node
{
public:
	virtual ~Decorator() {}

	void SetChild(Node* child) { this->child = child; }
	bool HasNoChild() const { return child == nullptr; }

protected:
	Node* child = nullptr;
};

class Succeeder : public Decorator
{
public:
	Status Update() override
	{
		child->Tick();
		return Status::Success;
	}
};

class Failer : public Decorator
{
public:
	Status Update() override
	{
		child->Tick();
		return Status::Failure;
	}
};

class Inverter : public Decorator
{
public:
	Status Update() override
	{
		auto s = child->Tick();

		if (s == Status::Success) 
		{
			return Status::Failure;
		}
		else if (s == Status::Failure) 
		{
			return Status::Success;
		}

		return s;
	}
};

class Repeater : public Decorator
{
public:
	Repeater(int limit = 0) : limit(limit) {}

	void Initialize() override
	{
		counter = 0;
	}

	Status Update() override
	{
		while (1) 
		{
			auto s = child->Tick();

			if (s == Status::Running)
			{
				return Status::Running;
			}

			if (s == Status::Failure) 
			{
				return Status::Failure;
			}

			if (limit > 0 && ++counter == limit) 
			{
				return Status::Success;
			}

			child->Reset();
		}
	}

protected:
	int limit;
	int counter = 0;
};

class UntilFail : public Decorator
{
public:
	Status Update() override
	{
		while (1) 
		{
			auto status = child->Tick();

			if (status == Status::Failure) 
			{
				return Status::Success;
			}
			else
			{
				return Status::Failure;
			}
		}
	}
};

class UntilSuccess : public Decorator
{
public:
	Status Update() override
	{
		while (1) 
		{
			auto status = child->Tick();

			if (status == Status::Success)
			{
				return Status::Success;
			}
			else
			{
				return Status::Failure;
			}
		}
	}
};