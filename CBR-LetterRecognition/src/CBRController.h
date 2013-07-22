#ifndef _CBRCONTROLLER_H
#define _CBRCONTROLLER_H

#include "Case.h"
#include "CaseBase.h"
#include "Index.h"
#include "CoverTree.h"
#include "RelationalSimilarity.h"
//#include "RSTree.h"

#include <vector>
using namespace std;

class CBRController{
	protected:
		CaseBase casebase;
		//Index currentIndex;
		vector<Index*> queries;
		CoverTree ct;
		RelationalSimilarity rs;
//		RSTree rstree;
	
	public:
		CBRController();
		~CBRController();
		vector<Case*> retrieve(Index*, int);
		vector<Case*> retrieve2(Index*, int);
		void preCycle();
		void postCycle();
		void cycle();
		void loadCaseBase();
		void buildCoverTree();
		void buildRS();
		void queryUI();
		void retainUI();//new
		void retain(vector<Index*>, vector<char>);// new
		char getPrediction(vector<Case*>);//new
		void readQueriesFromFile(char*);
		void printSolutions(vector<Case*>);
		void printQueries();
		void printPrediction(vector<Case*>);
		void dumpCaseBaseToFile();//new
};

#endif
