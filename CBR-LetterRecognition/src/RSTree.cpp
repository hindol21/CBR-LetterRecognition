#include "RSTree.h"

rstate operator-(const rstate& v1, const rstate& v2) {
	rstate result(v1);
	for (unsigned int i=0; i < v1.size(); ++i) {
		result[i] = v1[i] - v2[i];
	}
	return result;
}

ostream& operator<<(ostream& os, const rstate& c) {
	for (unsigned int i=0; i<c.size(); ++i){
		os << c[i];
		if (i<c.size()-1)
			os << " ";
	}
	return os;
}

RSTree::RSTree() {

}

void RSTree::initialize(rstate &ic, rstate &gc, rstate &mins, rstate &maxs, double ss, int mn, int ll, double AE)
{
	// clean-up from previous
	cleanup();

	ndim = ic.size();
	step_size = ss;
	max_nodes = mn;
	linear_limit = ll;
	ANNeps = AE;

	initRstate = rstate(ic);
	goalRstate = rstate(gc);

	qtmp = rstate(ic);

	minRstate = rstate(mins);
	maxRstate = rstate(maxs);

	parentVector.clear();
	rstateVector.clear();

	bestRstateIDX = -1;
	bestSD = DBL_MAX;

	srand(time(NULL));

	Init_extras();

	Init_ANN();
}

void RSTree::Init_extras()
{
	// Empty Function
}

RSTree::~RSTree() {
	cleanup();
}

void RSTree::cleanup()
{
	parentVector.clear();
	rstateVector.clear();
	parentVector.resize(0);
	rstateVector.resize(0);
}

void RSTree::Init_ANN()
{
	//int maxPts = max_nodes;
	int k = 1;

	linearNNstart=0;

	queryPt = annAllocPt(ndim);					// allocate query point
	for(int i=0; i<ndim; i++)
		queryPt[i] = 0.1*i;

	dataPts = annAllocPts(max_nodes, ndim);		// allocate data points
	nnIdx = new ANNidx[k];						// allocate near neighbor indices
	dists = new ANNdist[k];						// allocate near neighbor dists

	nPts = 0;									// counter for number of data points

	addNode(initRstate, bestRstateIDX); 				// Add initRstate rstate and "-1" to rstate vectors and ANN

	kdTree = new ANNkd_tree(		// build search structure
		dataPts,					// the data points
		nPts,						// current number of points
		ndim);						// dimension of space
}


void RSTree::connect(rstate &target) {
	//TODO: check if this works
	unsigned int numstates = rstateVector.size();

	int NNidx = getNearestNeighbor(target);
	tryStep(target, NNidx);

	while (rstateVector.size() > numstates) {
		numstates = rstateVector.size();
		tryStep(target, rstateVector.size() - 1);

		if (bestSD <= pow(step_size, 2)) {
			break;
		}
	}
}


void RSTree::tryStep(rstate qtry, int NNidx)
{
	rstate qnear(ndim);
	rstate qnew(ndim);
	qnear = rstateVector[NNidx];

	double sumsq = rstateSub(qtry, qnear, qnew);
	double edist = sqrt(sumsq);

	double scale = (double)step_size / edist;
	for (int i=0; i<ndim; ++i){
		qnew[i] = qnear[i] + qnew[i] * scale;
	}

	if (!edist) {

		addNode(qnew, NNidx);

		double sd = rstateSD(qnew, goalRstate);

		if (sd < bestSD) {
			bestRstateIDX = rstateVector.size()-1;	// if last node is closest, mark idx as greatestConf
			bestSD = sd;
			bestRstate = rstateVector[bestRstateIDX];
			cout << "achieved best SD: " << bestSD << " (treesize=" << rstateVector.size() << ")" << endl;
		}
	}

}

void RSTree::addNode(rstate &qnew, int parentID)
{
		rstateVector.push_back(qnew);
		parentVector.push_back(parentID);

		// add points to ANN data set
		for(int i=0; i<ndim; i++)
			dataPts[nPts][i] = qnew[i];
		nPts++;

		// after "linear_limit" steps build new tree
		if((int)rstateVector.size()-linearNNstart > linear_limit){
			delete kdTree;
			kdTree = new ANNkd_tree(dataPts,nPts,ndim);
			linearNNstart = rstateVector.size();
		}
}

rstate& RSTree::getRandomRstate()
{
	for (int i = 0; i < ndim; ++i) {
		qtmp[i] = RANDNM(minRstate[i], maxRstate[i]);
	}

	return qtmp;
}

int RSTree::getNearestNeighbor(rstate &qsamp)
{
	double min = DBL_MAX;
	double sd = 0.0;
	int nearest=0;

	for(unsigned int i = linearNNstart; i < rstateVector.size(); ++i){
		sd = rstateSD(qsamp, rstateVector[i]); // joint space version

		if(sd < min) {
			min = sd;
			nearest = i;
		}
	}

	if(nPts>linear_limit){
		for(int i = 0; i < ndim; ++i)
			queryPt[i] = qsamp[i];

		kdTree->annkSearch(queryPt, 1, nnIdx, dists, ANNeps);

		// take best result from ANN & list
		if (dists[0] < min)
			nearest = nnIdx[0];
	}
	return nearest;
}


