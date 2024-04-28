#include <bits/stdc++.h>
#include <iostream>
#include <omp.h>

using namespace std;

const int N = 20;
vector<int> g[N];
bool visited[N];
bool vis[N];
queue<int> q;

void bfs()
{
    while (!q.empty())
    {
        int current;
        #pragma omp critical
        {
            current = q.front();
            q.pop();
        }

        cout << current << " ";

        #pragma omp parallel for
        for (int i = 0; i < g[current].size(); ++i)
        {
            int it = g[current][i];
            if (!vis[it])
            {
                #pragma omp critical
                {
                    vis[it] = true;
                    q.push(it);
                }
            }
        }
    }
}

void dfs(int startVertex)
{
    stack<int> stk;
    stk.push(startVertex);

    while (!stk.empty())
    {
        int vertex = stk.top();
        stk.pop();

        if (!visited[vertex])
        {
            cout << vertex << " ";
            visited[vertex] = true;

            #pragma omp parallel for
            for (int i = 0; i < g[vertex].size(); ++i)
            {
                #pragma omp critical
                {
                    int child = g[vertex][i];
                    stk.push(child);
                }
            }
        }
    }
}


int main()
{
    int vertices = 4;
    int edges = 4;
    int arr[] = {0,1,0,2,1,3,2,3};
    for (int i = 0; i < 2*edges; i = i + 2)
    {
        int v1 = arr[i];
        int v2 = arr[i + 1];
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }

    cout << "DFS: ";
    dfs(0);

    cout << endl << "BFS: ";
    int starting = 0;
    vis[0] = true;
    q.push(starting);
    bfs();

    return 0;
}
