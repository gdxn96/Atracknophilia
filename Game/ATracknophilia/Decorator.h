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