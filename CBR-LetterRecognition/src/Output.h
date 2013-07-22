#ifndef _OUTPUT_H
#define _OUTPUT_H

class Output{
private:
	int nSize;
public:
	Output();
	~Output();
	int getSize(){ return nSize; };
	void printOutput();
};

#endif