#ifndef _INDEX_H
#define _INDEX_H

#include "Case.h"

class Index{
private:
	int* data;
public:
	Index();
	Index(int*);
	~Index();
	int* getData(){ return data; };
	void printIndex();
};

#endif 