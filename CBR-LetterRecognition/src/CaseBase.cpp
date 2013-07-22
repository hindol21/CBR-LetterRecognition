#include "CaseBase.h"

CaseBase::CaseBase(){
	nSize = 0;
}

CaseBase::~CaseBase(){}

Case CaseBase::getCase(int i){
	Case c = (Case)_casebase[i];
	return c;
}

void CaseBase::addACase(Case inCase){
	_casebase.push_back(inCase);
	nSize += 1;
}

void CaseBase::addCases(vector<Case> inCases){
	for(int i = 0; i < inCases.size(); i++){
		_casebase.push_back((Case)inCases[i]);
	}
	nSize += inCases.size();
}

void CaseBase::dumpCaseBaseToFile(char* filename){
	//need to be implemented..
}

void CaseBase::printCaseBase(){
	Case temp;
	printf("####################\n");
	printf("case base size = %d\n", _casebase.size());
	for(int i = 0; i < _casebase.size(); i++){
		temp = (Case)_casebase[i];
		temp.printCase();	
	}
	printf("####################\n");
}
