#pragma once

#include "Composite.h"

class Selector : public Composite
{
public:
	void Initialize() override
	{
		index = 0;
	}

	Status Update() override
	{
		if (HasNoChildren()) {
			return Status::Success;
		}

		// Keep going until a child behavior says it's running.
		while (1) {
			auto &child = children.at(index);
			auto status = child->Tick();

			// If the child succeeds, or keeps running, do the same.
			if (status != Status::Failure) {
				return status;
			}

			// Hit the end of the array, it didn't end well...
			if (++index == children.size()) {
				return Status::Failure;
			}
		}
	}

	using Ptr = std::shared_ptr<Selector>;
};

static Selector::Ptr MakeSelector()
{
	return std::make_shared<Selector>();
}