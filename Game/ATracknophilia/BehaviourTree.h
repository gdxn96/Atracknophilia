#pragma once
#include "Node.h"

class BehaviourTree : public Node
{
public:
	BehaviourTree()
		: root(nullptr)
	{}

	BehaviourTree(Node* rootNode)
		: root(rootNode)
	{}

	Status Update(IEntity* p)
	{
		if (p != nullptr)
		{
			return root->Tick(p);
		}
		else
		{
			return Status::Failure;
		}
	}

	void SetRoot(Node* node) { root = node; }

private:
	Node* root;
};