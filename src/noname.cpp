#include "DNA.h"

extern double x[MAXN][2];
extern int n;

double dis(const int &n1, const int &n2)
{
	return sqrt((x[n1][0] - x[n2][0]) * (x[n1][0] - x[n2][0]) 
		+ (x[n1][1] - x[n2][1]) * (x[n1][1] - x[n2][1]));
}

void DNA::calc_val()
{
	int count[3];
	for(int i = 0; i < n; i ++)
		count[rank[i]] ++;

	price_val = 5 * count[0] + 10 * count[1] + 50 + count[2];
	
	val = 1/dis_val;
	val = val * val * val;
}

/*
DNA DNA::upgrade()
{
	DNA newDNA = this;
	int list[MAXN], list2[MAXN];
	for(int i = 1; i <= n; i ++)
		list[i] = list2[i] = i;

	random_shuffle(list, list + n);
	bool succeed = 0;
	for(int i = 1; i <= n; i ++)
		if(status[list[i]].type == 0)
		{
			int now = list[i];
			for(int j = 1; j <= n; i ++)
				if(status[j].root == now)
				{
					bool added = 0;
					random_shuffle(list2, list2 + N);
					for(int kk = 1; kk <= n; kk ++)
					{
						int k = list2[kk];
						if(newDNA.add(j, k))
						{
							added = 1;
							break;
						}
					}
					if(added == 0)
					{
						newDNA.valid = 0;
						return newDNA;
					}
				}
		}



}

*/

/*
void DNA::rot()
{
	int a2[MAXN];
	int rot1 = rand() % n;
	for(int i = 0; i < n; i ++)
		a2[i] = a[(i + rot1) % n];
	for(int i = 0; i < n; i ++)
		a[i] = a2[i];
}
*/
