#include "Index.h"
#include <stdio.h>

Index::Index(){
	data = new int[CASE_SIZE];
}

Index::Index(int *in){
	data = new int[CASE_SIZE];
	for(int i = 0; i < CASE_SIZE; i++){
		*(data+i) = *(in+i);
	}
}

Index::~Index(){
	delete data;
}

void Index::printIndex(){
	for(int i = 0; i < CASE_SIZE; i++){
		printf("%d ", *(data+i));
	}
	printf("\n");
}