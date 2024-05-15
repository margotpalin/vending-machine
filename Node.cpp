#include "Node.h"

Node::Node(Meal* _data, Node* _next) : data(_data), next(_next) {}
Node::~Node(){ delete data; } 
