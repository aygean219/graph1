#include <iostream>
#include <vector>
#include <queue>
#include <iterator>
#include <fstream>
#include <string>
using namespace std;
#define INF 1000
/// <summary>
/// Aici puteti pune direct numarul de la fisier ele deja exista toate in folder
/// </summary>
ifstream fin("1-in.txt");
ofstream fout("1-out.txt");
typedef struct nod
{
	int varf;
	int pondere;
	int distanta;
	nod* parinte;
};
void Dijkstra_queue(int V, int E, int start, vector<vector<nod*>*>* Adj, vector<nod*>* distance)
{
	///INITIALIZARE///
	for (int i = 0; i < V; i++)
	{
		nod* n = new nod;
		n->distanta = INF;
		n->parinte = NULL;
		distance->push_back(n);
	}
	distance->at(start)->distanta = 0;
	vector<int>* S = new vector<int>;//vectorul cu varfuri
	queue<int>* Q = new queue<int>;
	for (int i = 0; i < V; i++)
	{
		Q->push(i);
	}
	while (!Q->empty())
	{
		int u = Q->front();
		Q->pop();
		S->push_back(u);
		vector<nod*>::iterator j;
		for (j = Adj->at(u)->begin(); j != Adj->at(u)->end(); j++)
		{
			///RELAX///
			if (distance->at(u)->distanta > distance->at((*j)->varf)->distanta + (*j)->pondere)
			{
				distance->at(u)->distanta = distance->at((*j)->varf)->distanta + (*j)->pondere;
				distance->at(u)->parinte = distance->at((*j)->varf);
			}
		}
	}

}
int BellmanFord(int V, int E, int S, vector<vector<nod*>*>* Adj, vector<nod*>* distance )
{	///INITIALIZARE///
	for (int i = 0; i <= V; i++)
	{
		nod* n = new nod;
		n->distanta = INF;
		n->parinte = NULL;
		distance->push_back(n);
	}
	distance->at(S)->distanta = 0;
 /////////////////////////////////////
	for (int k = 1; k <= V - 1; k++)
	{
		for (int i = 0; i <= V - 1; i++)
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
bool sortare(nod* n1, nod* n2)
{
	return (n1->varf < n2->varf);
}
int main()
{
	int V, E;
	fin >> V >> E;
	int x, y, w;
	vector<vector<nod*>*>* Adj = new vector<vector<nod*>*>;
	for (int i = 0; i <=V; i++)
	{
		vector<nod*>* v = new vector<nod*>;
		Adj->push_back(v);
	}
	while (fin >> x >> y >> w)
	{ 
		nod* n = new nod;
		n->varf = x;
		n->pondere = w;
		n->distanta = INF;
		n->parinte = NULL;
		Adj->at(y)->push_back(n);
		/////Adaug nodul S=V/////
		nod* new_n = new nod;
		new_n->varf = x;
		new_n->pondere = 0;
		new_n->distanta = INF;
		new_n->parinte = NULL;
		Adj->at(V)->push_back(new_n);
	}
	vector<nod*>* distance = new vector<nod*>;
	vector<int>* h = new vector<int>;
	for (int i = 0; i <= V; i++)
	{
		h->push_back(0);
	}
	if (BellmanFord(V, E, V, Adj, distance) == 0)
	{
		fout << "-1";
	}
	else {
		for (int i = 0; i <= V; i++)
		{
			h->at(i) = distance->at(i)->distanta;
		}
		for (int i = 0; i <= V - 1; i++)
		{
			vector<nod*>::iterator j;
			for (j = Adj->at(i)->begin(); j != Adj->at(i)->end(); j++)
			{
				(*j)->pondere = (*j)->pondere + h->at((*j)->varf) - h->at(i);
			}
		}
		//////PRINT/////
		//Pentru ca trebui afisate in ordine crescatoare creez 
		// un nou vector unde o sa am noduri:
		//varf->nodul sursa
		//distantaa->varful destinatie
		//pondere->ponderea drumului
		vector<nod*>* afisare_varfuri = new vector<nod*>;
		for (int i = 0; i <= V - 1; i++)
		{
			vector<nod*>::iterator j;
			for (j = Adj->at(i)->begin(); j != Adj->at(i)->end(); j++)
			{
				nod* n = new nod;
				n->varf = (*j)->varf;
				n->distanta = i;
				n->pondere = (*j)->pondere;//costu drumului
				afisare_varfuri->push_back(n);
			}
		}
		sort(afisare_varfuri->begin(), afisare_varfuri->end(), sortare);
		vector<nod*>::iterator j;
		for (j = afisare_varfuri->begin(); j != afisare_varfuri->end(); j++)
		{
			fout << (*j)->varf << " " << (*j)->distanta << " " << (*j)->pondere << endl;
		}
		vector<vector<int>*>* matrice = new vector<vector<int>*>;
		for (int i = 0; i < V; i++)
		{
			vector<int>* vect = new vector<int>;
			matrice->push_back(vect);
		}
		for (int i = 0; i < V; i++)
		{
			for (int j = 0; j < V; j++)
			{
				if (i == j)
				{
					matrice->at(i)->push_back(0);
				}
				else
				{
					matrice->at(i)->push_back(INF);
				}
			}
		}
		for (int i = 0; i <V; i++)
		{
			vector<nod*>* distante2 = new vector<nod*>;
			Dijkstra_queue(V, E, i, Adj, distante2);
			vector<nod*>::iterator j;
			for (j = Adj->at(i)->begin(); j != Adj->at(i)->end(); j++)
			{
					(matrice->at(i))->at((*j)->varf) = (*j)->pondere - h->at((*j)->varf) + h->at(i);
			}
		}
		for (int j = 0; j < V; j++)
		{
			for (int i = 0; i < V; i++)
			{
				if (matrice->at(i)->at(j) == INF)
				{
					fout << "INF" << " ";
				}
				else
				{
					fout << matrice->at(i)->at(j) << " ";
				}
			}
			fout << endl;
		}
	}
}