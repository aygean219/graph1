#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
using namespace std;
#define STERS -1000
std::ifstream fin("7-in.txt");
std::ofstream fout("out.txt");
//verifica daca are si alte varfuri decat radacina
bool verificaFrunze(vector<int>* parinti, int n)
{
    int m = 0;
    for (int i = 0; i < n; i++)
    {
        if (parinti->at(i) != -1 && parinti->at(i) != STERS)
        {
            m++;
            if (m > 0)
                return true;
        }
    }
    return false;
}
//cauta frunza n
int findFrunza(vector<int>* parinti, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (parinti->at(i) != -1 && parinti->at(i) != STERS)
        {
            bool verifica = true;
            for (int j = 0; j < n; j++)
            {
                if (i == parinti->at(j))
                {
                    verifica = false;
                }
            }
            if (verifica == true)
                return i;
        }
    }
}
void codificare(vector<int>* parinti,int n,vector<int>* prufer)
{
    int frunza;
    while (verificaFrunze(parinti, n))
    {
        frunza = findFrunza(parinti, n);
        prufer->push_back(parinti->at(frunza));
        parinti->at(frunza) = STERS;
    }
}
int main(){//int argc,char* argv[]) {
   
    int n;
    fin >> n;
    vector<int>* parinti=new vector<int>;
    for (int i = 0; i < n; i++)
    {
        int x;
        fin >> x;
        parinti->push_back(x);
    }
    vector<int>* prufer=new vector<int>;
    codificare(parinti, n, prufer);
    fout << n - 1 << "\n";
    vector<int>::iterator i;
    for(i=prufer->begin();i!=prufer->end();i++)
    {
        fout << (*i) << " ";
    }
    fin.close();
    fout.close();
    return 0;
}