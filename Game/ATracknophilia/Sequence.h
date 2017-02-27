#pragma once

#include "Composite.h"

class Sequence : public Composite
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

			// If the child fails, or keeps running, do the same.
			if (status != Status::Success) {
				return status;
			}

			if (++index == children.size()) {
				return Status::Success;
			}
		}
	}

	using Ptr = std::shared_ptr<Sequence>;
};

static Sequence::Ptr MakeSequence()
{
	return std::make_shared<Sequence>();
}