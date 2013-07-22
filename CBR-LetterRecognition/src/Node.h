#ifndef _NODE_H
#define _NODE_H

#include "Case.h"
#include <vector>
using namespace std;

class Node{
private:
	Case _case;
public:
	Node();
	Node(Case);
	Node(const Node&);
	Node& operator=(const Node&);
	Node* parent;
	vector<Node*> children;
	Case getData()const { return _case; };
	void setData(Case);
	void addChild(Node*);
	void setParent(Node*);
	void printNode();
};

#endif