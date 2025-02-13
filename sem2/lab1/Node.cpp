#include "Node.h"
#include <iostream>
#include <vector>

Node::Node()
{
	is_root = true;
}
Node::Node(char c)
{
	this->c = c;
}
Node::Node(Node* p)
{
	this->front_ptrs[0] = p;
}
