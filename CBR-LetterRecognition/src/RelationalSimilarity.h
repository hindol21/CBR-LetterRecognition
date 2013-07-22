#ifndef _RelationalSimilarity_H
#define _RelationalSimilarity_H

#include "Node.h"
#include "Case.h"
#include "Index.h"
#include <vector>
using namespace std;

class RelationalSimilarity{
private:
	Node* root;
	Node* nb;
	int topLevel;
	int bottomLevel;
public:
	RelationalSimilarity();
	~RelationalSimilarity();
	void insert(Case);
	bool internalInsert(Case, vector<Node*>, int);
	float dist_pQ(Node*, vector<Node*>);
	float dist_pq(Node*, Node*);
	vector<Node*> findNearestCase(Node*, int);
	void updateKNN(vector<Node*>&, Node*, Node*);
};

#endif