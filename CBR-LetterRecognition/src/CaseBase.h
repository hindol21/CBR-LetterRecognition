#ifndef _CASEBASE_H
#define _CASEBASE_H

#include "Case.h"
#include <vector>
using namespace std;

class CaseBase{
	private:
		vector<Case> _casebase;
		int nSize;
	public:
		CaseBase();
		~CaseBase();
		int getSize(){ return nSize; };
		Case getCase(int);
		void addACase(Case);
		void addCases(vector<Case>);
		void dumpCaseBaseToFile(char*);
		void printCaseBase();
};

#endif
