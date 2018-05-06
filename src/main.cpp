	#include "DNA.h"
#define Debug(x) cerr << #x << "=" << x << endl

using namespace std;

string name[MAXN];
int n;                                          /* n is the number of cities */
int m;                                          /* m is the size of population */
int mm;											/* new size of population */
int T;                                          /* T is the number of iterations */

const double pc = 0.6, pm = 0.4;               /* pc is the possibility of crossover */
                                                /* pm is the possibility of mutation */

double x[MAXN][2];                              /* the coordinate of each city */

DNA *now, *nowp;                                /* population */

/*
void Debug_print(const DNA &now)
{
	for(int i = 0; i < n; i ++)
		cerr << name[now.a[i]] << " " ;
}

void Debug_printn()
{
	for(int i = 0; i < n; i ++)
	{
		cerr << i << ": ";
		Debug_print(now[i]);
		cerr << "   " << now[i].dis_val << endl;
	}

	cerr << "----------------" << endl;
}


*/
int choose[MAXN];


double rand1()
{
	return double(rand()) / double(RAND_MAX) + 1e-8;
}

void choosen()
{
	memset(choose, 0, sizeof(choose));
	double totalval = 0;
	for(int i = 0; i < mm; i ++)
		totalval += now[i].val;
	//cerr << totalval << "TOTAL" << endl;

	double sprob[MAXM];

	sprob[0] = now[0].val / totalval;
	for(int i = 1; i < mm; i ++)
		sprob[i] = sprob[i - 1] + now[i].val / totalval;

	for(int i = 0; i < m; i ++)
	{
		double nowrand = rand1();
		for(int j = 0; j < m; j ++)
			if(nowrand < sprob[j])
			{
				nowp[i] = now[j];
				break;
			}
	}
	for(int i = 0; i < m; i ++)
		now[i] = nowp[i];
}

int main(int argc, char *argv[]) 
{
	srand(time(0));
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	cin >> n;

	m = n * 50;                                 /* the size of population */

	T = n * 300;

	for(int i = 0; i < n; i ++)
		cin >> x[i][0] >> x[i][1];

	now = new DNA[m];
	nowp = new DNA[m];

	for(int i = 0; i < m; i ++)
	{
		for(int j = 1; j <= n; j ++)
			now[i].status[j] = -1;
		now[i].fill();
		now[i].calc_val();

	}

	int ii = 1;
	while(T--)
	{
		choosen();
//		Debug_printn();

		for(int i = 0; i < m; i ++)
			if(rand1() <= pc)
			{
				int n2 = rand() % m;

				while(n2 == i)
					n2 = rand() % m;

				now[i].Crossover(now[n2]);
			}

		for(int i = 0; i < m; i ++)
			if(rand1() <= pm)
			{
				int n1 = rand() % m;
				now[n1].mutation();
			}

		double mi = 2147483647;
		for(int i = 0; i < m; i ++)
		{
			now[i].calc_val();
			mi = min(mi, now[i].price_val);
		}

		cerr << "Turn #" << ii << "	Current best price = " << mi << endl;
		ii ++;
	}

	return 0;
}

