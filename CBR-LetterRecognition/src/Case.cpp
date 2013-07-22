#include <stdio.h>
#include "Case.h"

Case::Case(){
	nCaseID = 0;
	xbox = 0;
	ybox = 0;
	width = 0;
	height = 0;
	onpix = 0;
	xbar = 0;
	ybar = 0;
	x2bar = 0;
	y2bar = 0;
	xybar = 0;
	x2ybr = 0;
	xy2br = 0;
	xege = 0;
	xegvy = 0;
	yege = 0;
	yegvx = 0;
	solution = '*';
}

Case::Case(int id, int a, int b, int c, int d, int e, int f, int g,
											 int h, int i, int j, int k, int l, int m, int n,
											 int o, int p, char answer){
	nCaseID = id;
	xbox = a;
	ybox = b;
	width = c;
	height = d;
	onpix = e;
	xbar = f;
	ybar = g;
	x2bar = h;
	y2bar = i;
	xybar = j;
	x2ybr = k;
	xy2br = l;
	xege = m;
	xegvy = n;
	yege = o;
	yegvx = p;
	solution = answer;
}

Case::Case(int id, int data[], char answer){
	nCaseID = id;
	xbox = data[0];
	ybox = data[1];
	width = data[2];
	height = data[3];
	onpix = data[4];
	xbar = data[5];
	ybar = data[6];
	x2bar = data[7];
	y2bar = data[8];
	xybar = data[9];
	x2ybr = data[10];
	xy2br = data[11];
	xege = data[12];
	xegvy = data[13];
	yege = data[14];
	yegvx = data[15];

	solution = answer;
}

Case& Case::operator =(const Case& c){
	if(this == &c)	return *this;

	nCaseID = c.getCaseID();
	int* data = c.getData();
	xbox = *data;
	ybox = *(data+1);
	width = *(data+2);
	height = *(data+3);
	onpix = *(data+4);
	xbar = *(data+5);
	ybar = *(data+6);
	x2bar = *(data+7);
	y2bar = *(data+8);
	xybar = *(data+9);
	x2ybr = *(data+10);
	xy2br = *(data+11);
	xege = *(data+12);
	xegvy = *(data+13);
	yege = *(data+14);
	yegvx = *(data+15);
	solution = c.getSolution();

	return *this;
}

Case::~Case(){
}

int* Case::getData()const{
	int data[CASE_SIZE];

	data[0] = xbox;
	data[1] = ybox;
	data[2] = width;
	data[3] = height;
	data[4] = onpix;
	data[5] = xbar;
	data[6] = ybar;
	data[7] = x2bar;
	data[8] = y2bar;
	data[9] = xybar;
	data[10] = x2ybr;
	data[11] = xy2br;
	data[12] = xege;
	data[13] = xegvy;
	data[14] = yege;
	data[15] = yegvx;

	return data;
}

void Case::setCase(int id, int data[], char answer){
	nCaseID = id;
	xbox = data[0];
	ybox = data[1];
	width = data[2];
	height = data[3];
	onpix = data[4];
	xbar = data[5];
	ybar = data[6];
	x2bar = data[7];
	y2bar = data[8];
	xybar = data[9];
	x2ybr = data[10];
	xy2br = data[11];
	xege = data[12];
	xegvy = data[13];
	yege = data[14];
	yegvx = data[15];
	solution = answer;
}

void Case::printCase(){
	printf("===== Print Case =====\n");

	printf("Case ID = %d\n", nCaseID);
	printf("Index = %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", xbox, ybox,
		width, height, onpix, xbar, ybar, x2bar, y2bar, xybar, x2ybr, xy2br, xege, xegvy,
		yege, yegvx);
	printf("Output = %c\n", solution);

	printf("===== ========== =====\n");
}
