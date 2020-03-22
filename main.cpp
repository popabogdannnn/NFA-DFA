#include <bits/stdc++.h>

using namespace std;

ifstream fin("automat.in");
ofstream fout("automat.out");

struct edge
{
    int x, y;
    char c;
};

class automat
{
private:

    int N;
    int initialState;
    set <int> finalState;
    vector < map < char, vector <int> > > E;
    set < pair <int, int> > vis;

    bool DFS(int node, string &X, int index)
    {
        vis.insert(make_pair(node, index));
        if(index == X.size())
            return finalState.find(node) != finalState.end();
        bool ret = false;
        if(E[node].find(X[index]) != E[node].end())
            for(auto it : E[node][X[index]])
                if(vis.find(make_pair(it, index + 1)) == vis.end())
                    ret = ret || DFS(it, X, index + 1);
        return ret;
    }
public:
    automat(int numOfNodes, vector <edge> edges, int q0, vector <int> qf)
    {
        N = numOfNodes;
        initialState = q0;
        for(auto it : qf)
            finalState.insert(it);
        E.resize(N);
        for(auto it : edges)
            E[it.x][it.c].push_back(it.y);
    }
    bool accepts(string X)
    {
        vis.clear();
        return DFS(initialState, X, 0);
    }
    void outputFirstK(int K)
    {
        int cnt = 0;
        queue < pair < int, string > > Q;
        string S;
        Q.push(make_pair(initialState, S));
        while(!Q.empty() && cnt <= 1e8 && K >= 1)
        {
            int node = Q.front().first;
            S = Q.front().second;
            Q.pop();
            if(finalState.find(node) != finalState.end())
            {
                K--;
                cout << S << "\n";
            }
            for(auto it : E[node])
            {
                S.push_back(it.first);
                for(auto it2: it.second)
                    Q.push(make_pair(it2, S));
                S.pop_back();
            }
            cnt++;
        }
    }
};

int N, M, F, q0;
vector <edge> E;
vector <int> fi;

int main()
{
    fin >> N >> M; /// pe prima linie N numarul de stari
        /// M numarul de arce ale automatului
    for(int i = 1; i <= M; i++) /// citesc arcele
    {
        int x, y;
        char c;
        fin >> x >> y >> c;
        E.push_back({x, y, c});
    }
    fin >> q0; /// starea initiala;
    fin >> F; /// starea finala
    for(int i = 1; i <= F; i++) /// citesc starile finale
    {
        int q;
        fin >> q;
        fi.push_back(q);
    }
    automat Q(N, E, q0, fi);
    for(fin >> M; M; M--) /// citesc cuvintele
    {
        string S;
        fin >> S;
        if(Q.accepts(S))
            cout << S << " este acceptat\n";
        else
            cout << S << " nu este acceptat\n";
    }
    Q.outputFirstK(100);
    return 0;
}
