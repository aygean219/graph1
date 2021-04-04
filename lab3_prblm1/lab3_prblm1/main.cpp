#include <iostream>
#include <vector>
#include <queue>
#include <iterator>
#include <fstream>
#include <string>
using namespace std;
#define INF 1000
ifstream fin("1-in.txt");
ofstream fout("1-out.txt");
typedef struct nod
{	int varf;
	int pondere;
	int distanta;
	nod* parinte;
};
int BellmanFord( int V, int E, int S,vector<vector<nod*>*>* Adj, vector<nod*>* distance = new vector<nod*>)
{
	for (int k = 1; k <= V-1 ; k++)
	{
		for (int i = 0; i <= V-1; i++)
		{
			vector<nod*>::iterator j;
			for (j = Adj->at(i)->begin(); j != Adj->at(i)->end(); j++)
			{
				///RELAX///
				if (distance->at(i)->distanta > distance->at((*j)->varf)->distanta + (*j)->pondere)
				{
					distance->at(i)->distanta = distance->at((*j)->varf)->distanta + (*j)->pondere;
					distance->at(i)->parinte = distance->at((*j)->varf);
				}
			}
		}
	}
	for (int i = 0; i < V; i++)
	{
		vector<nod*>::iterator j;
		for (j = Adj->at(i)->begin(); j != Adj->at(i)->end(); j++)
		{
			if (distance->at(i)->distanta > distance->at((*j)->varf)->distanta + (*j)->pondere)
			{
				return 0;
			}
		}
	}
	return 1;
}
int main()
{
	int V,E,S;
	fin >>V>>E>>S;
	int x, y,w;
	vector<vector<nod*>*>* Adj = new vector<vector<nod*>*>;
	for (int i = 0; i < V; i++)
	{
		vector<nod*>* v = new vector<nod*>;
		Adj->push_back(v);
	}
	while (fin >> x>> y>> w)
	{
		nod* n = new nod;
		n->varf = x;
		n->pondere = w;
		n->distanta = INF;
		n->parinte = NULL;
		Adj->at(y)->push_back(n);
	}
	vector<nod*>* distance = new vector<nod*>;
	for (int i = 0; i <V; i++)
	{
		nod* n = new nod;
		n->distanta = INF;
		n->parinte = NULL;
		distance->push_back(n);
	}
	distance->at(S)->distanta = 0;
	BellmanFord(V, E, S, Adj, distance);
	vector<nod*>::iterator j;
	for (j = distance->begin(); j != distance->end(); j++)
	{
		if ((*j)->distanta == INF)
		{
				fout << "INF" << " ";
		}
		else
		{
			fout << (*j)->distanta<< " ";
		}
	}
	return 0;
}