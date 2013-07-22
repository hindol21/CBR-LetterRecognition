#ifndef RSTree_H_
#define RSTree_H_

#include "Case.h"
#include "ANN/ANN.h"
#include <vector>
#include <stdlib.h>

using namespace std;

#define RANDNM(N,M) N + ((M-N) * (rand() / ((double)RAND_MAX + 1))) // random # between N&M

#define rstate vector<double>

rstate operator-(const rstate& v1, const rstate& v2);
ostream& operator<<(ostream& os,const rstate& l);

static inline double rstateSub(rstate &a, rstate &b, rstate &c){
	if ((a.size() != b.size()) && (a.size() != c.size()))
		perror("vector sizes do not match");

	double sd=0;
	for (int i = 0; i < (int)a.size(); ++i) {
		double d = a[i] - b[i];
		c[i] = d;
		sd += d * d;
	}
	return sd;
}

static inline double rstateSD(rstate &a, rstate &b){
	if (a.size() != b.size())
		perror("vector sizes do not match");

	double sd = 0;
	for (int i = 0; i < (int)a.size(); ++i) {
		double d = a[i] - b[i];
		sd += d * d;
	}
	return sd;
}

class RSTree {
public:
	RSTree();
	~RSTree();

	void initialize(rstate &ic, rstate &gc, rstate &mins, rstate &maxs, double ss = 0.05, int mn = 100000, int ll = 1000, double AE = 0);

	virtual void Init_extras();

	void Init_ANN();

	virtual void cleanup();

	int ndim;
	double step_size;
	int max_nodes;
	int linear_limit;
	double ANNeps;

	rstate initRstate;
	rstate goalRstate;

	rstate qtmp;

	rstate minRstate;
	rstate maxRstate;

	rstate bestRstate; 
	int bestRstateIDX;
	double bestSD;

	vector<int> parentVector;
	vector<rstate> rstateVector;
	vector<rstate> path;

	int 				linearNNstart;
	int					nPts;					// actual number of data points
	ANNpointArray		dataPts;				// data points
	ANNpoint			queryPt;				// query point
	ANNidxArray			nnIdx;					// near neighbor indices
	ANNdistArray		dists;					// near neighbor distances
	ANNkd_tree*			kdTree;					// search structure


	void connect(rstate &target);
	virtual void tryStep(rstate qtry, int NNidx);
	void addNode(rstate &qnew, int parentID);
	virtual rstate& getRandomRstate();
	int getNearestNeighbor(rstate &qsamp);

};



#endif /* RSTree_H_ */
