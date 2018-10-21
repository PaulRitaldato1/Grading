#include "stdafx.h"
#include "Node.h"


Node::Node()
{
}
Node::Node(string line) {
	this->line = line;
	next = nullptr;
}


Node::~Node()
{
}
