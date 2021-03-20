#include <iostream>
#include <vector>
#include <queue>
#include <iterator>
#include <fstream>
#include <string>
using namespace std;
#define INF 1000
ifstream f("graf.txt");
using namespace std;
void Moore(int s,int n, vector<int>* drum,vector<int>* parinte ,vector<vector<int>*>* Adj)
{
    for (int i = 0; i < n; i++)
    {
        drum->push_back(INF);
    }
    drum->at(s) = 0;
    queue<int>* coada=new queue<int>;
    coada->push(s);
    while (!coada->empty())
    {
        int x = coada->front();
        coada->pop();
        vector<int>::iterator i;
        for (i = Adj->at(x)->begin(); i != Adj->at(x)->end(); i++)
        {
            if (drum->at(*i) == INF)
            {
                parinte->at(*i) = x;
                drum->at(*i) = drum->at(x) + 1;
                coada->push(*i);
            }
        }

    }
}

int main() {
    int n;
    f >> n;//nr noduri
    int x, y;
    vector<int>* drum=new vector<int>;
    vector<int>* parinte=new vector<int>;
    vector<vector<int>*>* Adj=new vector<vector<int>*>;
    for (int i = 0; i < n; i++)
    {
        vector<int>* v = new vector<int>;
        Adj->push_back(v);
        parinte->push_back(0);
    }
    while (f >> x >> y)
    {
        Adj->at(x)->push_back(y);
        parinte->at(x) = x;
    }
    int s;
    cout << "Dati nodu de start: ";
    cin >> s;
    Moore(s, n, drum, parinte, Adj);
    for (int i = 0; i < n; i++)
    {
        cout << "Nodul: " << i << " are ca si parinte pe: " << parinte->at(i) << " si lungimea drumului este: " << drum->at(i) << endl;
    }
    f.close();
}