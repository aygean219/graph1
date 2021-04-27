#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;
bool BFS(vector< vector<int>* >* resAdjMatrix, int& source, int& sink, vector<int>* parent)
{
    int n = resAdjMatrix->size();
    vector<bool>* visited = new vector<bool>;
    for (int i = 0; i < n; i++)
    {
        visited->push_back(false);
    }
    queue<int>* q=new queue<int>;
    q->push(source);
    visited->at(source) = true;
    parent->at(source) = -1;

    while (q->empty() == false)
    {
        int u = q->front();
        q->pop();

        for (int i = 0; i < n; i++)
        {
            int v = i;
            int capacity = resAdjMatrix->at(u)->at(v);

            // am gasit vecin care nu a fost vizitat si cu capacitatea mai mare decat 0
            if (visited->at(v) == false && capacity > 0)
            {
               //pune in coada si marcheaza ca vizitat
                q->push(v);
                parent->at(v) = u;
                visited->at(v) = true;
            }
        }
    }
    // vf a fost vizitat si am gasit drum
    if (visited->at(sink) == true)
    {
        return true;
    }
    return false;
}

int FordFulkerson(vector< vector<int>* >* adjMatrix, int& source, int& sink)
{
    int maxflow = 0;
    // Creaza graful rezidual
    vector< vector<int>* >* resAdjMatrix=new vector<vector<int>*>;
    int n = adjMatrix->size();
    for (int i = 0; i < n; i++)
    {
        vector<int>* vect=new vector<int>;
        resAdjMatrix->push_back(vect);
        for (int j = 0; j < n; j++)
        {
            resAdjMatrix->at(i)->push_back(adjMatrix->at(i)->at(j));
        }
    }

    // creaza un vector de parinti 
    vector<int>* parent=new vector<int>;
    for (int i = 0; i < n; i++)
    {
        parent->push_back(-1);
    }

    // 3. Keep calling BFS to check for an augmenting path (from the source to the sink...
    while (BFS(resAdjMatrix, source, sink, parent) == true)
    {
        // 4. Find the max flow through the path we just found.
        int maxi = 10000007;
        int v = sink;
        while (v != source)
        {
            int u = parent->at(v); // parintele
            //minimul
            int capacity = resAdjMatrix->at(u)->at(v);
            maxi = min(maxi, capacity);

            // Setup for the next edge in the path.
            //urmatorul vf 
            v = u;
        }

        //update capacitatile reziduale si schimba nodurile
        v = sink;
        while (v != source)
        {
            int u = parent->at(v); // parintele

            // Update capacitatile.

            resAdjMatrix->at(u)->at(v) -=maxi;
            resAdjMatrix->at(v)->at(u) += maxi;

            // Setup for the next edge in the path.
            v = u;
        }

        // 6. Add this path's flow to our total max flow so far.
        maxflow += maxi;
    }

    return maxflow;
}
int main()
{
    ifstream fin("7-in.txt");
    vector< vector<int>* >* adjMatrix = new vector<vector<int>*>;
    int E, V;
    fin >> V >> E;
    for (int i = 0; i < V; i++)
    {
        vector<int>* vect = new vector<int>;
        adjMatrix->push_back(vect);
        for (int j = 0; j < V; j++)
        {
            adjMatrix->at(i)->push_back(0);
        }
    }
    int x, y,c;
    while (fin >> x >> y>> c)
    {
        adjMatrix->at(x)->at(y) = c;
    }
    
    int source = 0;
    int sink = V-1;
    cout << FordFulkerson(adjMatrix, source, sink) << endl;
    return 0;
}
