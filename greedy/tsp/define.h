#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <array>
#include <stack>

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

bool compare(const Edge &a, const Edge &b)
{
    return a.w < b.w;
}

void sortedges(std::vector<Edge> &data)
{
    sort(data.begin(), data.end(), compare);
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

#define WHITE 0
#define GRAY -1
#define BLACK 1

bool hascircled;
int circlestart;
int circleend;
array<bool, 100> marked;
array<int, 100> parents;
array<int, 100> colors;

int circled(const Graph &g, int u, int p)
{
    colors[u] = GRAY;
    marked[u] = true;
    parents[u] = p;

    vector<int> nbs = neighbours(g, u);

    for (auto i = nbs.begin(); i != nbs.end(); i++)
    {
        if (!marked[*i])
        {
            circled(g, *i, u);
            continue;
        }
        if (marked[*i] && colors[*i] == GRAY && *i != p)
        {
            hascircled = true;
            circlestart = *i;
            circleend = u;
        }
    }

    colors[u] = BLACK;

    return hascircled;
}

Graph greedy(Graph g)
{
    sortedges(g.edges);

    Graph _return;
    initgraph(_return, g.n);

    for (auto e = g.edges.begin(); e != g.edges.end(); e++)
    {
        addedge(_return, e->u, e->v, e->w);

        // Xoa cung neu co dinh bac 3
        if (degree(_return, e->u) == 3 || degree(_return, e->v) == 3)
            removeedge(_return, e->u, e->v);

        // Xoa cung neu tao thanh chu trinh thieu
        marked.fill(false);
        hascircled = false;
        if ((circled(_return, e->u, -1)) && (_return.n != (int)_return.edges.size()))
            removeedge(_return, e->u, e->v);

        marked.fill(false);
        hascircled = false;
        if ((circled(_return, e->v, -1)) && (_return.n != (int)_return.edges.size()))
            removeedge(_return, e->u, e->v);
    }
    return _return;
}

void printpath(array<int, 100> prs, int start, int end)
{
    stack<int> st;
    while (prs[end] != -1)
    {
        st.push(end);
        end = prs[end];
    }

    cout << start << " -> ";
    while (!st.empty())
    {
        cout << st.top() << " -> ";
        st.pop();
    }
    cout << start << endl;
}

float pathlen(const Graph &g)
{
    float len = 0;
    for (auto e = g.edges.begin(); e != g.edges.end(); e++)
        len += e->w;
    return len;
}