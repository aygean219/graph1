/*1. Fie un fisier ce contine un graf neorientat reprezentat sub forma:
prima linie contine numarul nodurilor iar urmatoarele randuri muchiile grafului. 
Sa se scrie un program in C/C++ care sa citeasca fisierul si 
sa reprezinte/stocheze un graf folosind matricea de adiacenta, 
lista de adiacenta si matricea de incidenta. Sa se converteasca 
un graf dintr-o forma de reprezentare in alta.
Fisier -> matrice de adiacenta -> lista adiacenta -> 
matrice de incidenta -> lista adiacenta -> 
matrice de adiacenta -> lista.
exemplu fisier
in.txt
4
1 2
3 4
2 3
4 2*/
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <iterator>
using namespace std;
ifstream f_in("in.txt");
vector<int> v;
map<int, vector<int>> m;
int numara_muchii_lista_adiacenta(map<int, vector<int >> lista);
void initializare(vector<int> &v,int n,int m)
{	int i = 0;
	while (i<n)
	{	v.push_back(m);
		i++;
	}
}
void matrice_de_adiacenta(map<int, vector<int>>& m)
{
	vector<int>::iterator itrv;
	map<int, vector<int>>::iterator itrm;
	while (!f_in.eof())
	{
		int x, y;
		f_in >> x >> y;
		for (itrm = m.begin(); itrm != m.end(); itrm++)//incepe de la 0
		{
			int index = distance(m.begin(), itrm);//pozitia in map,dist.. incepe cu 0
			if (index == x - 1)	//daca este egal cu x pun i vector la pozitia y 1
			{
				for (itrv = itrm->second.begin(); itrv != itrm->second.end(); itrv++)
				{
					itrm->second.at(y - 1) = 1;
				}
			}
			if (index == y - 1)//daca este egal cu y pun i vector la pozitia x 1
			{
				for (itrv = itrm->second.begin(); itrv != itrm->second.end(); itrv++)
				{
					itrm->second.at(x - 1) = 1;
				}
			}
		}
	}
}
map<int, vector<int>> matrice_de_adiacenta2(map<int, vector<int>> lista,int n)
{
	map<int, vector<int>>m;
	vector<int>::iterator itrv;
	vector<int>::iterator itrv2;
	vector<int>::iterator itrv3;
	map<int, vector<int>>mi;
	map<int, vector<int>>::iterator itrl;
	map<int, vector<int>>::iterator itrm;
	int k,q, i, j,d;
	for (int it = 0; it < n; it++)
	{
		vector<int> vect;
		initializare(vect, n, 0);
		m.insert(pair<int, vector<int>>(it, vect));
	}
	for (itrl = lista.begin(); (itrl != lista.end()); itrl++)//incepe de la 0 matricea//matricea
	{
		 i=distance(lista.begin(), itrl);
		for (itrv = itrl->second.begin(); itrv != itrl->second.end(); itrv++)//parcurg vectorul corespunzator//vectorul din matrice
		{
			d = distance(itrl->second.begin(), itrv);
			j = itrl->second.at(d)-1;
			for (itrm = m.begin(); itrm != m.end(); itrm++)
			{	 k= distance(m.begin(), itrm);
				for (itrv2 = itrm->second.begin(); itrv2 != itrm->second.end(); itrv2++)
				{	q= distance(itrm->second.begin(), itrv2);
					if ((i == k) && (j == q))
					{
						itrm->second.at(q) = 1;
					}
					if ((i == q) && (j == k))
					{
						itrm->second.at(q) = 1;
					}
				}

			}
		}
		
		
	}
	return m;
}
void lista_adiacenta(map<int, vector<int>> m, map<int, vector<int>> &lista)
{	
	vector<int>::iterator itrv;
	map<int, vector<int>>::iterator itrm;
	map<int, vector<int>>::iterator itrl;
	for (itrm = m.begin(); itrm != m.end(); itrm++)//incepe de la 0 matricea
	{
		vector<int> vector_nou;
		for (itrv = itrm->second.begin(); itrv != itrm->second.end(); itrv++)//parcurg vectorul corespunzator
		{
			int numar = distance(itrm->second.begin(), itrv);//pozitia in vector
			if (itrm->second.at(numar) == 1)
			{
				vector_nou.push_back(numar + 1);
			}
		}
		lista.insert(pair<int, vector<int>>(distance(m.begin(), itrm), vector_nou));
	}
}
map<int, vector<int>> matrice_incidenta1(map<int, vector<int>> lista, map<int, vector<int>> &m)
{
	vector<int>::iterator itrv;
	vector<int>::iterator itrv2;
	vector<int>::iterator itrv3;
	map<int, vector<int>>mi;
	map<int, vector<int>>::iterator itrl;
	map<int, vector<int>>::iterator itrm;
	int numar = 0;
	for (itrl = lista.begin(); itrl != lista.end(); itrl++)//incepe de la 0 matricea//lista
	{
		int i = distance(lista.begin(), itrl);
		for (itrv = itrl->second.begin(); itrv != itrl->second.end(); itrv++)//parcurg vectorul corespunzator//vectorul din lista
		{	
			int j = itrl->second.at(distance(itrl->second.begin(), itrv)) - 1;//pozitia in vector
			int verifica = 0;
			for (itrm = m.begin(); (itrm != m.end()) && (verifica == 0) && (i < j); itrm++)//incepe de la 0 matricea//matricea
			{
				for (itrv2 = itrm->second.begin(); itrv2 != itrm->second.end(); itrv2++)//parcurg vectorul corespunzator//vectorul din matrice
				{
					int d = distance(itrm->second.begin(), itrv2);
					if (d == j) 
					{		verifica = 1;
							itrm->second.at(i) = 1;
							itrm->second.at(j) = 1;
					}
					else
					{
						itrm->second.at(d) = 0;
					}
				}
				vector<int> vv;
				for (itrv2 = itrm->second.begin(); itrv2 != itrm->second.end(); itrv2++)//parcurg vectorul corespunzator//vectorul din matrice
				{
					int d = distance(itrm->second.begin(), itrv2);
					vv.push_back(itrm->second.at(d));
				}
				mi.insert(pair<int, vector<int>>(i+numar, vv));
				numar++;
			}
		}
	}
	return mi;
}
vector<pair<int, int>> lista_finala2(map<int, vector<int>> m)
{
	vector<int>::iterator itrv;
	vector<int>::iterator itrv2;
	vector<pair<int,int>>mi;
	map<int, vector<int>>::iterator itrl;
	map<int, vector<int>>::iterator itrm;
	map<int, vector<int>>::iterator itrm2;
	int k, q, i, j, d;
	for (itrm = m.begin(); itrm != m.end(); itrm++)//incepe de la 0 matricea//matricea
	{
		int i = distance(m.begin(), itrm);
		for (itrv = itrm->second.begin(); itrv != itrm->second.end(); itrv++)//parcurg vectorul corespunzator//vectorul din matrice
		{
			j = distance(itrm->second.begin(), itrv);
			//j = itrm->second.at(d) - 1;
			if (itrm->second.at(j) == 1)
			{
				mi.push_back(pair<int, int>(i + 1, j + 1));
				for (itrm2 = m.begin(); itrm2 != m.end(); itrm2++)//incepe de la 0 matricea//matricea
				{
					int k = distance(m.begin(), itrm2);
					for (itrv2 = itrm2->second.begin(); itrv2 != itrm2->second.end(); itrv2++)//parcurg vectorul corespunzator//vectorul din matrice
					{
						q = distance(itrm2->second.begin(), itrv2);
						if ((i == q) && (j == k))
						{
							itrm2->second.at(i) = 0;
						}
					}
				}
			}
		}
	}
	return mi;
}
void afisare_matrice_incidenta(map<int, vector<int>> m,int A[100][100],int n,int nr)
{
	vector<int>::iterator itrv;
	map<int, vector<int>>::iterator itrm;
	for (itrm = m.begin(); itrm != m.end(); itrm++)//incepe de la 0 matricea//matricea
	{
		int j = distance(m.begin(), itrm);
		for (itrv = itrm->second.begin(); itrv != itrm->second.end(); itrv++)//parcurg vectorul corespunzator//vectorul din matrice
		{
				int i = distance(itrm->second.begin(), itrv);
				A[i][j] = itrm->second.at(i);	
		}
	}
	cout << "      ";
	for (int i = 0; i < n; i++)
	{
		cout << " |m" << i + 1;// << " |";
	}
	cout << endl;
	for (int i = 0; i <n; i++)
	{
		cout << "Varf " << i+1<<" |";
		for (int j = 0; j < nr; j++)

		{
			cout << A[i][j] << "   ";
		}
		cout << endl;
	}
	cout << endl<<endl;
}
int numara_muchii_lista_adiacenta(map<int, vector<int >> lista)
{
	vector<int>::iterator itrv;
	map<int, vector<int>>::iterator itrm;
	int nr = 0;
	for (itrm = lista.begin(); itrm != lista.end(); itrm++)//incepe de la 0 matricea
	{	 
		nr = nr + itrm->second.size();
	}
	return nr/2;
}
void afisare_matrice_adiacenta(map<int, vector<int>> m)
{
	vector<int>::iterator itrv;
	map<int, vector<int>>::iterator itrm;
	cout << "Matricea de adiacenta: " << endl;
	for (itrm = m.begin(); itrm != m.end(); itrm++)
	{
		for (itrv = itrm->second.begin(); itrv != itrm->second.end(); itrv++)
		{
			int numar= distance(itrm->second.begin(), itrv);//pozitia in map
			cout << itrm->second.at(numar) << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
}
//matrice de incidenta->lista adiacenta ->
map<int, vector<int>> lista_adiacenta2( map<int, vector<int>>& m,int n)
{
	map<int, vector<int>>lista_noua;
	vector<int>::iterator itrv;
	vector<int>::iterator itrv2;
	vector<int>::iterator itrv3;
	map<int, vector<int>>mi;
	map<int, vector<int>>::iterator itrl;
	map<int, vector<int>>::iterator itrm;
	int poz1=0, poz2=0,i=0,j=0; 
	vector<int> vv;
	for (int q = 0; q < n; q++)
	{
		lista_noua.insert(pair<int, vector<int>>(q, vv));
	}
	for (itrm = m.begin(); (itrm != m.end()); itrm++)//incepe de la 0 matricea//matricea
	{
		for (itrv = itrm->second.begin(); itrv != itrm->second.end(); itrv++)//parcurg vectorul corespunzator//vectorul din matrice
		{
			 i = distance(itrm->second.begin(), itrv);
			 if (itrm->second.at(i) == 1)
			 {
				 poz1 = i;
				 break;
			 }
		}
		for (itrv = itrm->second.begin(); itrv != itrm->second.end(); itrv++)//parcurg vectorul corespunzator//vectorul din matrice
		{
			 j = distance(itrm->second.begin(), itrv);
			 if ((itrm->second.at(j) == 1) && (j != poz1))
			 {
				 poz2 = j;
				 break;
			 }
		}
		for (itrl = lista_noua.begin(); itrl != lista_noua.end(); itrl++)
		{
			int k = distance(lista_noua.begin(), itrl);
				if (k == i)
				{
					itrl->second.push_back(j+1);
				}
				if (k== j)
				{
					itrl->second.push_back(i+1);
				}
			
		}
	}
	return lista_noua;
}
void afisare_lista_adiacenta(map<int, vector<int>> m)
{
	vector<int>::iterator itrv;
	map<int, vector<int>>::iterator itrm;
	cout << "Lista de adiacenta: " << endl;
	cout << "Varf | Vecini" << endl;
	for (itrm = m.begin(); itrm != m.end(); itrm++)
	{
		cout << itrm->first +1<< "    | ";
		for (itrv = itrm->second.begin(); itrv != itrm->second.end(); itrv++)
		{
			int numar = distance(itrm->second.begin(), itrv);//pozitia in map
			cout << itrm->second.at(numar) << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
}
void afisare_lista_finala(vector<pair<int, int>> v)
{
	vector<pair<int, int>>::iterator itrv;
	for (itrv = v.begin(); itrv != v.end(); itrv++)
	{
		cout << itrv->first << " " << itrv->second << endl;
	}
}
int main()
{
	int n;
	f_in >> n;
	//se initializeaza fiecare vector cu 0
	map<int, vector<int>> m;
	map<int, vector<int>>::iterator itrm;
	for (int it = 1; it <= n; it++)
	{
		vector<int> vect;
		initializare(vect, n, 0);
		m.insert(pair<int, vector<int>>(it, vect));
	}
	matrice_de_adiacenta(m);
	afisare_matrice_adiacenta(m);
	//lista de adiacenta
	map<int, vector<int>> lista;
	map<int, vector<int>> lista2;
	lista_adiacenta(m, lista);
	afisare_lista_adiacenta(lista);
	//matrice de incidenta
	int nr = numara_muchii_lista_adiacenta(lista);//numar muchii lista de adiacenta
	map<int, vector<int>> mi;
	map<int, vector<int>> mii;
	for (int it = 1; it <= nr; it++)
	{
		vector<int> vect;
		initializare(vect, n, -1);
		mi.insert(pair<int, vector<int>>(it, vect));
	}
	mii=matrice_incidenta1(lista, mi);
	int A[100][100];
	afisare_matrice_incidenta(mii,A,n,nr);
	lista2 = lista_adiacenta2(mii, n);
	afisare_lista_adiacenta(lista2);
	map<int, vector<int>> ma;
	ma = matrice_de_adiacenta2(lista2, n);
	afisare_matrice_adiacenta(ma);
	//lista 
	vector<pair<int, int>> lista_finala;
	lista_finala = lista_finala2(ma);
	afisare_lista_finala(lista_finala);
}