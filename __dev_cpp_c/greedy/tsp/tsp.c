/**
 * KIM MINH THANG
 * B2007210
 * GREEDY - TSP
*/
#include <stdio.h>

#define MAXEDGE 100

typedef struct
{
    int u, v;
    float w;
} Edge;

typedef struct
{
    int n, m;
    Edge edges[MAXEDGE];
} Graph;

void initgraph(Graph *pG, int n)
{
    pG->n = n;
    pG->m = 0;
}

void addedge(Graph *pG, int u, int v, float w)
{
    Edge edge = {u, v, w};
    pG->edges[pG->m++] = edge;
}

void popedge(Graph *pG)
{
    pG->m--;
}

Graph readdata(const char *filepath)
{
    Graph G;
    FILE *file = fopen(filepath, "r");
    int n;
    fscanf(file, "%d", &n);
    initgraph(&G, n);
    int u, v;

    for (u = 1; u <= n; u++)
        for (v = 1; v <= n; v++)
        {
            float w;
            fscanf(file, "%f", &w);
            if (u >= v)
                continue;
            addedge(&G, u, v, w);
        }
    fclose(file);
    return G;
}

int adjcent(Graph *pG, int u, int v)
{
    int i;
    for (i = 0; i < pG->m; i++)
    {
        if (pG->edges[i].u == u && pG->edges[i].v == v)
            return 1;
        if (pG->edges[i].v == u && pG->edges[i].u == v)
            return 1;
    }
    return 0;
}

int degree(Graph *pG, int u)
{
    int d = 0, i;

    for (i = 0; i < pG->m; i++)
        d += pG->edges[i].u == u || pG->edges[i].v == u;
    return d;
}

void swap(Edge *a, Edge *b)
{
    Edge t = *a;
    *a = *b;
    *b = t;
}

void insertionsort(Edge edges[], int n)
{
    int i;
    for (i = 1; i < n; i++)
    {
        int j = i;
        while (j && edges[j - 1].w > edges[j].w)
        {
            swap(&edges[j - 1], &edges[j]);
            j--;
        }
    }
}

#define WHITE 0
#define BLACK 1
#define GRAY -1

int colors[MAXEDGE];
int parents[MAXEDGE];
int hascircle;
int startcircle;
int endcircle;

void dfs(Graph *pG, int u, int p)
{
	if(hascircle)
		return;
    colors[u] = GRAY;
    parents[u] = p;

    int i;
    for (i = 1; i <= pG->n; i++)
    {
        if (!adjcent(pG, u, i))
            continue;
        if (colors[i] == BLACK)
            continue;
        if (parents[u] == i)
            continue;
        if (colors[i] == GRAY)
        {
            hascircle = 1;
            startcircle = u;
            endcircle = i;
            return;
        }
        if (colors[i] == WHITE)
            dfs(pG, i, u);
    }
    colors[u] = BLACK;
}

int checkcircle(Graph *pG, int u)
{
    int i;
    for (i = 0; i < MAXEDGE; i++)
    {
        colors[i] = WHITE;
        parents[i] = -1;
    }
    hascircle = 0;
    dfs(pG, u, -1);
    return hascircle;
}

float finpathlen(const Graph *pG)
{
	float len = 0;
	const Edge *edge = pG->edges;
	while(edge != pG->edges + pG->m)
	{
		len += edge->w;
		edge++;
	}
	return len;
}

void findpath(const Graph *pG)
{
    Graph G;
    initgraph(&G, pG->n);
    int i;
    for (i = 0; i < pG->m; i++)
    {
        int u = pG->edges[i].u;
        int v = pG->edges[i].v;
        float w = pG->edges[i].w;
        addedge(&G, u, v, w);
        if (degree(&G, u) > 2 || degree(&G, v) > 2)
            popedge(&G);

        if (G.m == G.n)
            continue;
        if (checkcircle(&G, u) || checkcircle(&G, v))
            popedge(&G);
    }

    checkcircle(&G, 1);

    int path[MAXEDGE];
    int len = 0;

    int u = endcircle;
    while (u != startcircle && u != -1)
    {
        path[len++] = u;
        u = parents[u];
    }
    puts("Chu trinh co the la ngan nhat tim duoc voi tham an la");
    printf("%d -> ", startcircle);
    for (i = len - 1; i >= 0; i--)
        printf("%d -> ", path[i]);
    printf("%d", startcircle);
    printf("\nTong do dai la: %.2f", finpathlen(pG));
}

int main()
{
    Graph G = readdata("./TSP.txt");
    insertionsort(G.edges, G.m);
    findpath(&G);
    return 0;
}