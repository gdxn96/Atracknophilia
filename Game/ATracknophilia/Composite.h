#pragma once
#include "Node.h"

class Composite : public Node
{
public:
	virtual ~Composite() {}

	void AddChild(Node* child) { children.push_back(child); }
	bool HasNoChildren() const { return children.empty(); }
	int GetIndex() const { return index; }

protected:
	std::vector<Node*> children;
	int index = 0;
};
