#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
ifstream f("graf.txt");
int main()
{
	int n,a,b;
	f >> n;
	vector<vector<int>*>* matrice=new vector<vector<int>*>; 
	int i,j;
	for (i = 0; i <= n; i++)
	{
		vector<int>* v= new vector<int>;
		matrice->push_back(v);
		for (j = 0; j <= n; j++)
		{
			if (i == j)
			{
				v->push_back(1);
			}
			else
			{
				v->push_back(0);
			}
		}

	}
	while (f >> a >> b)
	{
		matrice->at(a)->at(b) = 1;
	}
	
	for (i = 0; i <= n; i++)
	{
		for (j = 0; j <= n; j++)
		{
			cout<<matrice->at(i)->at(j)<<" ";
		}
		cout << endl;
	}
}