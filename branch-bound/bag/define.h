#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

typedef struct
{
    int u, v;
    float w;
} Edge;

typedef struct
{
    int n;
    std::vector<Edge> edges;
} Graph;

void initgraph(Graph &g, int n)
{
    g.n = n;
}

void addedge(Graph &g, int u, int v, float w)
{
    Edge e = {u, v, w};
    g.edges.push_back(e);
}

void removeedge(Graph &g, int u, int v)
{
    for (int i = 0; i < (int)g.edges.size(); i++)
    {
        if (g.edges[i].u == u && g.edges[i].v == v)
            g.edges.erase(g.edges.begin() + i);
        if (g.edges[i].v == u && g.edges[i].u == v)
            g.edges.erase(g.edges.begin() + i);
    }
}

int degree(Graph &g, int u)
{
    int d = 0;
    for (auto e = g.edges.begin(); e != g.edges.end(); e++)
        d += e->u == u || e->v == u;
    return d;
}

vector<int> neighbours(Graph g, int u)
{
    vector<int> data;
    for (auto e = g.edges.begin(); e != g.edges.end(); e++)
    {
        if (e->u == u)
            data.push_back(e->v);

        if (e->v == u)
            data.push_back(e->u);
    }

    return data;
}

Graph readgraphfromfile(string filepath)
{
    ifstream file = ifstream(filepath);
    int n;
    file >> n;
    Graph g;
    initgraph(g, n);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            float w;
            file >> w;
            if (i > j || !w)
                continue;
            addedge(g, i, j, w);
        }
    return g;
}
