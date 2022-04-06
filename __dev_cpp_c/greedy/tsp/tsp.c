#include <stdio.h>

#define MAXNODE 100

typedef struct
{
    int n, m;
    int A[MAXNODE][MAXNODE];
} Graph;

void initgraph(Graph *pG, int n)
{
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            pG->A[i][j] = 0;
}

void addedge(Graph *pG, int u, int v, int w)
{
    pG->A[u][v] = w;
    pG->A[v][u] = w;
    pG->m++;
}

int main()
{
    return 0;
}