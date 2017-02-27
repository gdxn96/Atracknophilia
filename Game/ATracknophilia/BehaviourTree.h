#pragma once
#include "Node.h"
#include "Entities.h"

class BehaviourTree : public Node
{
public:
	BehaviourTree()
		: player(nullptr)
		, root(nullptr)
	{}

	BehaviourTree(AIPlayer* p) 
		: player(p)
		, root(nullptr)
	{}

	BehaviourTree(AIPlayer* p, Node* rootNode)
		: player(p)
		, root(rootNode)
	{}

	Status Update() { return root->Tick(); }

	void SetRoot(Node* node) { root = node; }
	void SetAIPlayer(AIPlayer* p) { player = p; }
	AIPlayer* GetAIPlayer() { return player; }

private:
	Node* root = nullptr;
	AIPlayer* player = nullptr;
};