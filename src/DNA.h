#ifndef DNA_H_
#define DNA_H_

#include "main.h"

struct point
{
	unsigned int type;   /* 0 is SUZHUZHAN. type is it's father's number. type >> 10 is it's grandfather's number and so on*/
	int root;   /* num of SUZHUZHAN*/
	int len;    /* length to SUZHUZHAN*/
	int childs1, childs; /* childs1 <= 4, childs <= 6*/
	bool occupied; /* if type == 2, 1 means it has a child*/
};

class DNA
{
public:
	int status[MAXN];
	//unsigned int type;	/* 0 is SUZHUZHAN. type is it's father's number. type >> 10 is it's grandfather's number and so on*/
	double price_val, val;                      /* dis_val is the sum of distance */
                                                /* val is the value of DNA which is used in selection procedure */
	void calc_val();                            /* Calculate the total distance of the DNA */
	void mutation();

	//void upgrade();
	void Crossover(DNA& that);
	void fill();
	//void rot();                                 /* rotate the DNA to improve diversity */

private:
	bool bloodfill_OK[MAXN];

	int findroot(int now);
	int finddepth(int now);
	void bloodfill(int now);
	//int findnext(const int &now) const;         /* A function used in crossover */

};

#endif
