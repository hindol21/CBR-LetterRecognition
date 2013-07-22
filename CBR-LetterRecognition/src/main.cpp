#include "CBRController.h"
#include <time.h>
#include <stdio.h>


int main(void){
	CBRController controller;

	//clock_t start = clock();//measure total execution time

	controller.preCycle();

	controller.cycle();

	controller.postCycle();

	//printf("Time elapsed: %f\n", ((double)clock() - start) / CLOCKS_PER_SEC);

	system("pause"); 

	return 0;
}
