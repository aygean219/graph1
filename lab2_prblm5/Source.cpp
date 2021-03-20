#include <iostream>
#include <vector>
#include <queue>
#include <iterator>
#include <fstream>
#include <string>
using namespace std;
#define INF 1000
ifstream f("graf.txt");
typedef struct nod
{
	int varf;
	string color;
	int d;
	int f;
	nod* parinte;
};
void DFS_VISIT(nod* u, vector<vector<nod>*>* Adj,int time)
{
	cout << u->varf<<" ";
	nod* vv = new nod;
	time++;
	u->d = time;
	u->color = "gri";
	vector<nod>::iterator v;
	for (v = Adj->at(u->varf)->begin(); v != Adj->at(u->varf)->end(); v++)
	{
		if (v->color == "alb")
		{
			//(*vv) = *v;
			v->parinte = u;
			DFS_VISIT(&*v, Adj, time);
		}
	}
	u->color = "negru";
	time++;
	u->f = time;
}
int main()
{
	int n;
	f >> n;
	int x, y;
	vector<vector<nod>*>* Adj = new vector<vector<nod>*>;
	for (int i = 0; i < n; i++)
	{
		vector<nod>* v = new vector<nod>;
		Adj->push_back(v);
	}

	while (f >> x >> y)
	{
		nod n;
		n.varf = y;
		n.color = "alb";
		n.parinte = NULL;
		Adj->at(x)->push_back(n);
	}
	int time = 0;
	vector<nod>* v = new vector<nod>;
	for (int i = 0; i < n; i++)
	{
		nod nn;
		nn.varf = i;
		nn.color = "alb";
		nn.parinte = NULL;
		v->push_back(nn);
	}
	vector<nod>::iterator i;
	cout << "De unde sa inceapa explorarea? R: ";
	int s;
	cin >> s;
	for (i =v->begin(); i!=v->end(); i++)
	{	
		if (i->varf == s) {
			if (i->color == "alb")
			{
				cout << "Se incepe explorarea: ";
				nod* nn = new nod;
				(*nn) = v->at(i->varf);
				DFS_VISIT(nn, Adj, time);
				cout << endl;
			}
		}

	}
	return 0;
}