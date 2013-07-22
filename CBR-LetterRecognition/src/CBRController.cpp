#include "CBRController.h"
#include "Node.h"
#include "config.h"
#include <time.h>
#include <iostream>
using namespace std;

CBRController::CBRController(){
}

CBRController::~CBRController(){
}

void CBRController::loadCaseBase(){
	char* line = new char[128];
	char* templine = new char[128];
	char* temp;
	char answer;
	int data[CASE_SIZE];
	int index = 0;
	int numOfCase = 1; 
	FILE* infile; 
	infile = fopen(CASEBASE_FILE, "r");

	if (infile != NULL){
		while(fgets(line, 128, infile) != NULL){
			index = 0;
			
			templine = line;
			temp = strtok(templine, ",");
			
			answer = *temp;
			
			while(temp != NULL){
				temp = strtok(NULL, ",");
			
				if(temp != NULL)
					data[index] = atoi(temp);
				index += 1;
			}
			
			Case c(numOfCase, data, answer);
			casebase.addACase(c);//put into casebase
			numOfCase += 1;
		}
		fclose(infile);
	}
	else{
		printf("Fail to open file\n");
		exit(0);
	}
	delete line;//cmhuang
}

void CBRController::buildCoverTree(){
	Case c;

	for(int i = 0; i < casebase.getSize(); i++){
		c = casebase.getCase(i);
		ct.insert(c);
	}
}

void CBRController::buildRS(){
	Case c;
	
	for(int i = 0; i < casebase.getSize(); i++){
		c = casebase.getCase(i);
		rs.insert(c);
	}
}

void CBRController::preCycle(){
	//do all the pre-settings here
	loadCaseBase();
	printf("load casebase done..\n");
	printf("casebase size: %d\n", casebase.getSize());

	//convert casebase to cover tree
	buildCoverTree();
	printf("build cover tree done..\n");
	//ct.printTree(ct.getRoot(), ct.getTopLevel());
}

void CBRController::postCycle(){
	//do all the post processes here
	//dump casebase to file
	dumpCaseBaseToFile();
}

void CBRController::cycle(){
	//queryUI();
	bool satisfied = false;
	int userInput;
	vector<char> predictions;
	
	while(satisfied == false){
		queries.clear();
		readQueriesFromFile(QUERY_FILE);
		predictions.clear();
		printQueries();

		vector<Case*> retrievedCases;
		clock_t start = clock();//measure query time
		for(int i = 0; i < queries.size(); i++){
			retrievedCases = retrieve((Index*)queries[i], K);
			printSolutions(retrievedCases);
			printPrediction(retrievedCases);
			predictions.push_back(getPrediction(retrievedCases));
		}	
		printf("Time elapsed: %f\n", ((double)clock() - start) / CLOCKS_PER_SEC);

		retainUI();
		cin >> userInput;
		switch(userInput){
			case 1:
				//retain
				retain(queries, predictions);
				satisfied = false;
				break;
			case 2:
				//retain
				retain(queries, predictions);
				satisfied = true;
				break;
			case 3:
				satisfied = false;
				break;
			case 4:
				satisfied = true;
				break;
			default:
				satisfied = true;
				break;
		}
	}
	
}

void CBRController::retain(std::vector<Index*> indices, std::vector<char> predictions){
	Case* newCase;
	int* data;

	for(int i = 0; i < indices.size(); i++){
		data = new int[CASE_SIZE];
		for(int j = 0; j < CASE_SIZE; j++){
			*(data+j) = *(((int*)((Index*)indices[i])->getData())+j);
		}
		newCase = new Case(casebase.getSize()+i, data, (char)predictions[i] );
		casebase.addACase(*newCase);
		delete data;//cmhuang
		delete newCase;//cmhuang
	}
	printf("%d new cases are retained. Casebase size = %d\n", indices.size(), casebase.getSize());
}

//covertree
vector<Case*> CBRController::retrieve(Index* index, int k){
	vector<Node*> nn;
	vector<Case*> solutions;
	
	Node* p = new Node();
	Case c(-1, index->getData(), '#');
	p->setData(c);

	nn = ct.findKNN(p, k);

	delete p;

	for(int i = 0; i < nn.size(); i++){
		int* data = new int[CASE_SIZE];
		for(int j = 0; j < CASE_SIZE; j++){
			*(data+j) = *(((Node*)nn[i])->getData().getData()+j);
		}
		Case* cc = new Case( ((Node*)nn[i])->getData().getCaseID(), 
			data, ((Node*)nn[i])->getData().getSolution() );
		solutions.push_back(cc);

		delete data;//cmhuang
	}

	return solutions;
}

//RelationalSimilarity
vector<Case*> CBRController::retrieve2(Index* index, int k){
	vector<Node*> nn;
	vector<Case*> solutions;
	
	Node* p = new Node();
	Case c(-1, index->getData(), '#');
	p->setData(c);
	
	nn = rs.findNearestCase(p, k);
	
	delete p;
	
	for(int i = 0; i < nn.size(); i++){
		int* data = new int[CASE_SIZE];
		for(int j = 0; j < CASE_SIZE; j++){
			*(data+j) = *(((Node*)nn[i])->getData().getData()+j);
		}
		Case* cc = new Case( ((Node*)nn[i])->getData().getCaseID(), 
							data, ((Node*)nn[i])->getData().getSolution() );
		solutions.push_back(cc);
		
		delete data;
	}
	
	return solutions;
}

void CBRController::retainUI(){
	printf("##### Retain Interface #####\n");
	printf("Please Input your choice\n");
	printf("1) Retain current query and Query more\n");
	printf("2) Retain current query and EXIT\n");
	printf("3) Do NOT retain current query and Query more\n");
	printf("4) Do NOT retain current query and EXIT\n");
}

void CBRController::queryUI(){
	printf("##### Query Interface #####\n");

	printf("Input Query file\n");
}

void CBRController::readQueriesFromFile(char* filename){
	char* line = new char[128];
	char* templine = new char[128];
	char* temp;
	int data[CASE_SIZE];
	int index = 0;
 
	FILE* infile; 
	infile = fopen(filename, "r");

	if (infile != NULL){
		while(fgets(line, 128, infile) != NULL){
			index = 0;
			
			templine = line;
			temp = strtok(templine, ",");
			
			while(temp != NULL){
				if(temp != NULL)
					data[index] = atoi(temp);
				
				temp = strtok(NULL, ",");
				index += 1;
			}
			
			Index* in = new Index(data);
			queries.push_back(in);//put into index
		}
		fclose(infile);
	}
	else{
		printf("Fail to open file\n");
		exit(0);
	}
	delete line;//cmhunag
}

void CBRController::printQueries(){
	printf("########## Queries ##########\n");

	for(int i = 0; i < queries.size(); i++){
		((Index*)queries[i])->printIndex();
	}

	printf("########## ####### ##########\n");
}

void CBRController::printSolutions(std::vector<Case*> cases){
	printf("########## Solutions ##########\n");

	for(int i = 0; i < cases.size(); i++){
		((Case*)cases[i])->printCase();
	}

	printf("########## ######### ##########\n");
}

void CBRController::printPrediction(std::vector<Case*> cases){
	int scoreBoard[26] = {0};
	int highestValue = -1;
	int highestPos = -1;

	printf("Cases Size = %d\n", cases.size());
	for(int i = 0; i < cases.size(); i++){
		scoreBoard[(int)(((Case*)cases[i])->getSolution()) - 65] += 1;
		printf("Retrieved cases = %c\n", ((Case*)cases[i])->getSolution());

	}

	for(int i = 0; i < 26; i++){
		if(scoreBoard[i] > highestValue){
			highestValue = scoreBoard[i];
			highestPos = i;
		}
	}

	printf("Prediction = %c, %d\n", highestPos+65, scoreBoard[highestPos]);
}

char CBRController::getPrediction(std::vector<Case*> cases){
	int scoreBoard[26] = {0};
	int highestValue = -1;
	int highestPos = -1;

	for(int i = 0; i < cases.size(); i++){
		scoreBoard[(int)(((Case*)cases[i])->getSolution()) - 65] += 1;
	}

	for(int i = 0; i < 26; i++){
		if(scoreBoard[i] > highestValue){
			highestValue = scoreBoard[i];
			highestPos = i;
		}
	}

	//printf("Prediction = %c\n", highestPos+65);
	return highestPos+65;
}

void CBRController::dumpCaseBaseToFile(){
	FILE *file;

	file = fopen(CASEBASE_FILE,"w");
	for(int i = 0; i < casebase.getSize(); i++){
		fprintf(file, "%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", (casebase.getCase(i)).getSolution(),
			*((casebase.getCase(i)).getData()), *((casebase.getCase(i)).getData()+1), *((casebase.getCase(i)).getData()+2),
			*((casebase.getCase(i)).getData()+3), *((casebase.getCase(i)).getData()+4), *((casebase.getCase(i)).getData()+5),
			*((casebase.getCase(i)).getData()+6), *((casebase.getCase(i)).getData()+7), *((casebase.getCase(i)).getData()+8),
			*((casebase.getCase(i)).getData()+9), *((casebase.getCase(i)).getData()+10), *((casebase.getCase(i)).getData()+11),
			*((casebase.getCase(i)).getData()+12), *((casebase.getCase(i)).getData()+13), *((casebase.getCase(i)).getData()+14),
			*((casebase.getCase(i)).getData()+15) );
	}
	fclose(file);
}