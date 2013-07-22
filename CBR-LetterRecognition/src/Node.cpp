#include "Node.h"

Node::Node(){
	parent = NULL;
}

Node::Node(Case c){
	_case = c;
}

Node::Node(const Node& n){
	_case = n.getData();
	parent = n.parent;
	for(int i = 0; i < n.children.size(); i++){
		children.push_back(n.children[i]);
	}
}

Node& Node::operator =(const Node &n){
	if(this == &n)	return *this;

	_case = n.getData();
	for(int i = 0; i < n.children.size(); i++){
		children.push_back(n.children[i]);
	}
	parent = n.parent;

	return *this;
}

void Node::setData(Case c){
	_case = c;
}

void Node::addChild(Node* node){
	children.push_back(node);
}

void Node::printNode(){
	_case.printCase();
}