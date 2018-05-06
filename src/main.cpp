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
		srand[i] = srand[i - 1] + now[i].val / totalval;

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
	freopen(argv[1], "r", stdin);
	freopen(argv[2], "w", stdout);
	cin >> n;

	m = n * 50;                                 /* the size of population */

	T = n * 300;

	for(int i = 0; i < n; i ++)
		cin >> name[i] >> x[i][0] >> x[i][1];

	now = new DNA[m];
	nowp = new DNA[m];

	for(int i = 0; i < m; i ++)
	{
		for(int j = 0; j < n; j ++)
			now[i].a[j] = j;
		random_shuffle(now[i].a, now[i].a + n);
		now[i].calc_val();
	}

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
		for(int i = 0; i < m; i ++)
			now[i].calc_val();
	}


	double ansmax = -1;
	int ansp;

	for(int i = 0; i < m; i ++)
		if(now[i].val > ansmax)
			ansp = i;

	for(int i = 0; i < n; i ++)
		cout << name[now[ansp].a[i]] << " ";

	cout << now[ansp].dis_val << endl;

	return 0;
}

