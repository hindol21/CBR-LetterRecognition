#include "CoverTree.h"
#include <stdio.h>
#include <vector>
#include <cmath>
using namespace std;

CoverTree::CoverTree(){
	topLevel = 0;
	root = NULL;
}

CoverTree::~CoverTree(){
	//delete all nodes....
	delete root;
}

void CoverTree::insert(Case c){
	if(root == NULL){
		root = new Node(c);
	}
	else{
		vector<Node*> coverSet;
		coverSet.push_back(root);
		
		if(internalInsert(c, coverSet, topLevel));//insert to subtree
		else{//insert under coverset
			Node* node = new Node(c);
			root->addChild(node);
		}
	}
}

/*bool : found parent or not*/
bool CoverTree::internalInsert(Case c, std::vector<Node*> inSet, int level){
	vector<Node*> coverSet;

	Node* n;
	Node* temp;
	for(int i = 0; i < inSet.size(); i++){//1
		n = (Node*)inSet[i];

		for(int j = 0; j < n->children.size(); j++){
			coverSet.push_back(n->children[j]);
		}
	}

	Node p(c);
	if(dist_pQ(&p, coverSet) > pow(2.0, level) ) {
		return false;//2
	}
	else{
		vector<Node*> nextCoverSet;
		for(int j = 0; j < coverSet.size(); j++){//3-(a)
			if(dist_pq(&p, (Node*)coverSet[j]) <= pow(2.0, abs(level)) ){
				nextCoverSet.push_back((Node*)coverSet[j]);
			}
		}

		if((internalInsert(c, nextCoverSet, level-1) == false) && (dist_pQ(&p, coverSet) <= pow(2.0, abs(level))) ){
			//3-(b)
			for(int j = 0; j < coverSet.size(); j++){
				if(dist_pq(&p, (Node*)coverSet[j]) <= pow(2.0, abs(level))){
					Node* newNode = new Node(p);
					((Node*)coverSet[j])->addChild(newNode);
					bottomLevel = level;//!?
					
					return true;
				}
			}
			
		}
		else return false;//3-(c)
	}
}

float CoverTree::dist_pQ(Node* p, vector<Node*> Q){
	int minDist = 100000;
	Node* tempNode;
	int tempValue;
	int* pData, *tempData;

	pData = new int[CASE_SIZE];
	for(int j = 0; j < CASE_SIZE; j++){
		*(pData+j) = *(p->getData().getData()+j);
	}

	for(int i = 0; i < Q.size(); i++){
		tempValue = 0.0;
		tempNode = (Node*)Q[i];
		
		tempData = new int[CASE_SIZE];
		for(int j = 0; j < CASE_SIZE; j++){
			*(tempData+j) = *(tempNode->getData().getData()+j);
		}

		for(int j = 0; j < CASE_SIZE; j++){
			tempValue += (*(pData+j) - *(tempData+j)) * (*(pData+j) - *(tempData+j));
		}
		if(tempValue < minDist){
			minDist = tempValue;
		}		
		delete tempData;//cmhuang
	}

	delete pData;//cmhuang
	
	float dist = sqrt((float)minDist);

	return dist;
}

float CoverTree::dist_pq(Node* p, Node* q){
	int tempValue;
	int* pData, *qData;

	pData = new int[CASE_SIZE];
	qData = new int[CASE_SIZE];
	for(int j = 0; j < CASE_SIZE; j++){
		*(pData+j) = *(p->getData().getData()+j);
		*(qData+j) = *(q->getData().getData()+j);
	}


	tempValue = 0;
		
	for(int j = 0; j < CASE_SIZE; j++){
		tempValue = tempValue +  (*(pData+j) - *(qData+j)) * (*(pData+j) - *(qData+j)) ;
	}

	delete pData;//cmhuang
	delete qData;//cmhuang

	float dist = sqrt((float)tempValue);

	return dist;
}

vector<Node*> CoverTree::findKNN(Node *p, int k){
	vector<Node*> coverSet;
	vector<Node*> nextCoverSet;
	vector<Node*> nn;
	int level = topLevel;

	coverSet.push_back(root);

	//while(level >= bottomLevel){
	//while(isBottomLayer(coverSet) == false){
	while(coverSet.size() != 0){
		for(int i = 0; i < coverSet.size(); i++){
			//form next cover set
			for(int j = 0; j < ((Node*)coverSet[i])->children.size(); j++){
				nextCoverSet.push_back((Node*)((Node*)coverSet[i])->children[j]);
			}

			if(nn.size() < k){
				nn.push_back((Node*)coverSet[i]);
			}
			else{
				updateKNN(nn, p, (Node*)coverSet[i]);
			}
		}

		coverSet.clear();
		coverSet = nextCoverSet;
		nextCoverSet.clear();

		level -= 1;
	}
	return nn;
}

void CoverTree::updateKNN(std::vector<Node*>& nn, Node*p, Node* curNode){
	int position;
	float curDist, minDist, tempDist;
	
	curDist = dist_pq(p, curNode);
	minDist = dist_pQ(p, nn);
	if(curDist >= minDist);//no need to update
	else{
		for(int i = 0; i < nn.size(); i++){
			tempDist = dist_pq(p, (Node*)nn[i]);
			if(tempDist == minDist){
				nn[i] = curNode;
				break;
			}
		}
	}
}

bool CoverTree::isBottomLayer(vector<Node*> layer){
	for(int i = 0; i < layer.size(); i++){
		if(((Node*)layer[i])->children.size() != 0 ) return false;
	}
	return true;
}

void CoverTree::printTree(Node* r, int level){
	printf("level %d : node(case id) = %d\n", level, ((Case)r->getData()).getCaseID());
	printf("children = \n");
	for(int i = 0; i < r->children.size(); i++){
		printf("%d ", ((Node*)r->children[i])->getData().getCaseID());
	}
	printf("\n");
	
	for(int i = 0; i < r->children.size(); i++){
		printTree((Node*)r->children[i], level-1);
	}
}

void CoverTree::printNodes(std::vector<Node*> inNodes){
	printf("# Nodes = %d\n", inNodes.size());
	for(int i = 0; i < inNodes.size(); i++){
		printf("%d ", ((Node*)inNodes[i])->getData().getCaseID());
	}
	printf("\n");
}