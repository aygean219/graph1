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
	int distanta;
    nod* parinte;
};

int main()
{
	vector<nod>* g=new vector<nod>;

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
		n.distanta = INF;
		n.parinte = NULL;
		Adj->at(x)->push_back(n);
	}
	cout << "Dati nodul de start: ";
	int s;
	cin >> s;
	nod start;
	start.color = "gri";
	start.distanta = 0;
	start.parinte = NULL;
	start.varf = s;
	queue<nod>* coada = new queue<nod>;
	coada->push(start);
	while (!coada->empty())
	{
		nod* u = new nod;
		(*u)=coada->front();
		coada->pop();
		vector<nod>::iterator v;
		for (v = Adj->at(u->varf)->begin(); v != Adj->at(u->varf)->end(); v++)
		{
			if (v->color == "alb")
			{
				v->color = "gri";
				v->distanta = u->distanta + 1;
				v->parinte = u;
				coada->push((*v));
			}
		}
		u->color = "negru";
		
	}
	for (int i = 0; i < n; i++)
	{
		vector<nod>::iterator j;
		for (j = Adj->at(i)->begin(); j != Adj->at(i)->end(); j++)
		{
			if (j->color != "alb" && j->varf != s)
			{
				cout << "Varful " << j->varf << " a fost descoperit la distanta " << j->distanta << endl;
			}
		}
	}
	return 0;
}