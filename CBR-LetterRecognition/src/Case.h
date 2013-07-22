#ifndef _CASE_H
#define _CASE_H

#define CASE_SIZE	16

class Case{
private:
	int nCaseID;
	int xbox;
	int ybox;
	int width;
	int height;
	int onpix;
	int xbar;
	int ybar;
	int x2bar;
	int y2bar;
	int xybar;
	int x2ybr;
	int xy2br;
	int xege;
	int xegvy;
	int yege;
	int yegvx;
	char solution;
public:
	Case();
	Case(int, int, int, int, int, int, int, int, int,
		int, int, int, int, int, int, int, int, char);
	Case(int, int[], char);
	Case& operator=(const Case&);
	~Case();
	int getCaseID()const { return nCaseID; };
	char getSolution()const{ return solution; };
	int* getData()const;
	void setCaseID(int id){ nCaseID = id; };
	void setCase(int, int[], char);
	void printCase();
};

#endif
