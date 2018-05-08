#include "DNA.h"

using namespace std;

#define father(x) (status[x] & 1023)
#define grandfather(x) ((status[x] >> 10) & 1023)
#define grandgrandfather(x) ((status[x] >> 20) & 1023)

extern double x[MAXN][2];
extern int n;

double dis(const int &n1, const int &n2)
{
	return sqrt((x[n1][0] - x[n2][0]) * (x[n1][0] - x[n2][0]) + (x[n1][1] - x[n2][1]) * (x[n1][1] - x[n2][1]));

	//return 6378 * acos(sin(x[n1][1]) * sin(x[n2][1]) + cos(x[n1][1]) * cos(x[n2][1]) * cos(x[n1][0] - x[n2][0]));
}

void DNA::bloodfill(int now)
{
	bloodfill_OK[now] = 1;
	for(int i = 1; i <= n; i ++)
		if(status[i] == 0 && dis(now, i) <= 50 && !bloodfill_OK[i])
			bloodfill(i);
}

void DNA::calc_val()
{
	memset(bloodfill_OK, 0, sizeof(bloodfill_OK));
	int count0 = 0, countconnections = 0;
	for(int i = 1; i <= n; i ++)
		if(status[i] == 0)
		{
			if(!bloodfill_OK[i])
			{
				bloodfill(i);
				countconnections ++;
			}
			count0 ++;
		}

	price_val = 5 * (n - count0) + 10 * count0 + 50 * ((countconnections - 1) / 8 + 1);

	val = 1/price_val;
	val = val * val * val;
}


/*
   bool have[MAXN];
   int DNA::findnext(const int &now) const
   {
   int p;
   for(int i = 0; i < n; i ++)
   {
   if(a[i] == now)
   {
   p = i;
   break;
   }
   }
   for(int i = 1; i < n; i ++)
   if(!have[a[(p + i) % n]])
   return a[(p + i) % n];

   std::cerr << "Error :: cannot findnext in crossover" << std::endl;
   return -1;
   }
   */

int DNA::findroot(int now)
{
	if(status[now] == 0)
		return now;
	if(grandgrandfather(now) != 0)
		return grandgrandfather(now);
	if(grandfather(now) != 0)
		return grandfather(now);
	if(father(now) != 0)
		return father(now);

	return 0;
}

int DNA::finddepth(int now)
{
	if(status[now] == 0)
		return 0;
	if(grandgrandfather(now) != 0)
		return 3;
	if(grandfather(now) != 0)
		return 2;
	if(father(now) != 0)
		return 1;

	return 0;
}

int root[MAXN];   /* num of SUZHUZHAN*/
int len[MAXN];    /* length to SUZHUZHAN*/
int childs1[MAXN], childs[MAXN]; /* childs1 <= 4, childs <= 6*/
bool occupied[MAXN]; /* if type == 2, 1 means it has a child*/

vector <int> unchosen;
vector <int> unchosen2;
vector <int> available;


void DNA::fill()
{
	memset(childs1, 0, sizeof(childs1));
	memset(childs, 0, sizeof(childs));
	memset(occupied, 0, sizeof(occupied));
	unchosen.clear();
	unchosen2.clear();
	available.clear();

	int count = n ;

	for(int i = 1; i <= n; i ++)
		if(status[i] != -1 && status[i] != 0)
		{
			if(status[father(i)] == 0)
			{
				childs1[father(i)] ++;
				childs[father(i)] ++;
			}
			else if(status[grandfather(i)] == 0)
			{
				childs[grandfather(i)] ++;
				occupied[father(i)] = 1;
			}
			else if(status[grandgrandfather(i)] == 0)
			{
				childs[grandgrandfather(i)] ++;
				occupied[father(i)] = 1;
			}
		}


	for(int i = 1; i <= n; i ++)
	{
		if(status[i] == -1)
			unchosen.push_back(i);
		else if(occupied[i] != 1 && finddepth(i) < 3 && childs1[findroot(i)] < 4 && childs[findroot(i)] < 6)
			available.push_back(i);
	}

	if(unchosen.size() == 0)
		return;

	random_shuffle(available.begin(), available.end());
	random_shuffle(unchosen.begin(), unchosen.end());

	while(unchosen.size() != 0)
	{
		int ii = 0;
		while(ii < unchosen.size())
		{
			int i = unchosen[ii];
			int jj = 0;
			while(jj < available.size())
			{
				int j = available[jj];
				int p = findroot(j);

				if(childs1[p] >= 4 || childs[p] >= 6 || occupied[j] == 1 || finddepth(j) >= 3)
				{
					available.erase(available.begin() + jj);
					continue;
				}

				if(status[j] == 0 && dis(i, j) <= 20)
				{
					status[i] = j;
					//cerr << i << " a " << status[i] << endl;
					childs[j] ++;
					childs1[j] ++;

					occupied[i] = 0;
					if(childs1[j] < 4 && childs[j] < 6 && finddepth(i) < 3)
						available.push_back(i);
					break;
				}
				else if(status[j] != 0 && dis(i, j) <= 10)
				{
					childs[p] ++;
					status[i] = (status[j] << 10) + j;
					/*
					   cerr << j << " b " << status[j] << endl;
					   cerr << i << " b " << status[i] << endl;
					   cerr << finddepth(j) << endl;
					   */

					occupied[j] = 1;
					occupied[i] = 0;
					if(childs1[p] < 4 && childs[p] < 6 && finddepth(i) < 3)
						available.push_back(i);
					break;
				}

				jj ++;
			}
			if(jj < available.size())
				unchosen.erase(unchosen.begin() + ii);
			else
				ii ++;
		}

		if(unchosen.size() != 0)
		{
			ii = rand() % unchosen.size();
			int i = unchosen[ii];
			unchosen.erase(unchosen.begin() + ii);

			status[i] = childs[i] = childs1[i] = occupied[i] = 0;
			available.push_back(i);
		}
	}
}

void DNA::Crossover(DNA &that)
{
	vector<int> listthis, listthat;
	listthis.clear();
	listthat.clear();

	DNA newDNA1, newDNA2;
	for(int i = 1; i <= n; i ++)
	{
		newDNA1.status[i] = newDNA2.status[i] = -1;

		if(status[i] == that.status[i] && findroot(i) == that.findroot(i))
			newDNA1.status[i] = newDNA2.status[i] = status[i];
		else if(status[i] == 0)
			listthis.push_back(i);
		else if(that.status[i] == 0)
			listthat.push_back(i);

	}

	random_shuffle(listthis.begin(), listthis.end());
	random_shuffle(listthat.begin(), listthat.end());


	for(int ii = 0; ii < listthis.size() / 3; ii ++)
		newDNA1.status[listthis[ii]] = 0;
	for(int i = 1; i <= n; i ++)
		if(findroot(i) != 0 && newDNA1.status[findroot(i)] == 0)
			newDNA1.status[i] = status[i];

	for(int i = 0; i < listthat.size() / 3; i ++)
		newDNA1.status[listthat[i]] = 0;
	for(int i = 1; i <= n; i ++)
		if(that.findroot(i) != 0 && newDNA1.status[that.findroot(i)] == 0)
			newDNA1.status[i] = that.status[i];

	newDNA1.fill();


	for(int i = listthat.size() / 3; i < listthat.size() * 2 / 3; i ++)
		newDNA2.status[listthat[i]] = 0;
	for(int i = 1; i <= n; i ++)
		if(that.findroot(i) != 0 && newDNA2.status[that.findroot(i)] == 0)
			newDNA2.status[i] = that.status[i];

	for(int i = listthis.size() / 3; i < listthis.size() * 2 / 3; i ++)
		newDNA2.status[listthis[i]] = 0;
	for(int i = 1; i <= n; i ++)
		if(findroot(i) != 0 && newDNA2.status[findroot(i)] == 0)
			newDNA2.status[i] = status[i];

	newDNA2.fill();

	that = newDNA2;

	for(int i = 1; i <= n; i ++)
		status[i] = newDNA1.status[i];

	bool p1 = 0, p2 = 0;
	for(int i = 1; i <= n; i ++)
	{
		if(status[i] == 0)
			p1 = 1;
		if(that.status[i] == 0)
			p2 = 1;
	}

}


void DNA::mutation()
{
	int nowdel;
	do{
		nowdel = rand() % n + 1;
		//cerr << "OMG" << endl;
	} while(status[nowdel] != 0);

	vector <int> tokill;
	tokill.clear();

	for(int i = 1; i <= n; i ++)
	{
		if(findroot(i) == nowdel)
			tokill.push_back(i);
	}



	for(int i = 0; i < tokill.size(); i ++)
		status[tokill[i]] = -1;


	fill();

	bool p1 = 0, p2 = 1, p3 = 0;
	for(int i = 1; i <= n; i ++)
	{
		if(status[i] == 0)
			p1 = 1;
		if(status[i] < 0)
			p2 = 0;
		if(status[i] != 0 && finddepth(i) == 1)
			p3 = 1;
	}

/*
	if(p1 == 0)
	{
		cerr << "ERROR3" << endl;
		for(int i = 1; i <= n; i ++)
			cerr << status[i] << endl;
		while(1);
	}

	if(p2== 0)
	{
		cerr << "ERROR4" << endl;
		for(int i = 1; i <= n; i ++)
			cerr << status[i] << endl;
		while(1);
	}

	if(p3== 0)
	{
		cerr << "ERROR5" << endl;
		for(int i = 1; i <= n; i ++)
			cerr << status[i] << endl;
		while(1);
	}
	*/

}


