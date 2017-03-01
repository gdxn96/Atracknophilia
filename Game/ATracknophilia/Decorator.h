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
	Status Update(IEntity* p) override
	{
		child->Tick(p);
		return Status::Success;
	}
};

class Failer : public Decorator
{
public:
	Status Update(IEntity* p) override
	{
		child->Tick(p);
		return Status::Failure;
	}
};

class Inverter : public Decorator
{
public:
	Status Update(IEntity* p) override
	{
		auto s = child->Tick(p);

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
	Repeater(int limit = 0) 
		: limit(limit)
		, counter(0)
	{}

	Status Update(IEntity* p) override
	{
		while (1) 
		{
			auto s = child->Tick(p);

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
				Reset();
				return Status::Success;
			}

			child->Reset();
		}
	}

protected:
	int limit;
	int counter;
};

class UntilFail : public Decorator
{
public:
	Status Update(IEntity* p) override
	{
		while (1) 
		{
			auto status = child->Tick(p);

			if (status == Status::Failure) 
			{
				return Status::Success;
			}
		}
	}
};

class UntilSuccess : public Decorator
{
public:
	Status Update(IEntity* p) override
	{
		while (1) 
		{
			auto status = child->Tick(p);

			if (status == Status::Success)
			{
				return Status::Success;
			}
		}
	}
};