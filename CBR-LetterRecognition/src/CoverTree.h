#ifndef _COVERTREE_H
#define _COVERTREE_H

#include "Node.h"
#include "Case.h"
#include "Index.h"
#include <vector>
using namespace std;

class CoverTree{
private:
	Node* root;
	int topLevel;
	int bottomLevel;
public:
	CoverTree();
	~CoverTree();
	void insert(Case);
	bool internalInsert(Case, vector<Node*>, int);
	void setRoot(Node* r){ root = r; };
	void printTree(Node*, int);
	Node* getRoot(){ return root; };
	int getTopLevel(){ return topLevel; };
	float dist_pQ(Node*, vector<Node*>);
	float dist_pq(Node*, Node*);
	void printNodes(vector<Node*>);
	vector<Node*> findKNN(Node*, int);
	void updateKNN(vector<Node*>&, Node*, Node*);
	bool isBottomLayer(vector<Node*>);
};

#endif