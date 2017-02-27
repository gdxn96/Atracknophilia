#pragma once
#include "Node.h"
#include "Entities.h"

class BehaviorTree : public Node
{
public:
	BehaviorTree(AIPlayer* p) : player(p) {}
	BehaviorTree(AIPlayer* p, Node* rootNode)
		: player(p)
		, root(rootNode)
	{}

	Status Update() { return root->Tick(); }

	void SetRoot(Node* node) { root = node; }
	AIPlayer* GetAIPlayer() { return player; }

private:
	Node* root = nullptr;
	AIPlayer* player = nullptr;
};