/**
 * KIM MINH THANG
 * B2007210
 * GREEDY - TSP
 */
#include <stdio.h>

typedef struct
{
    int u, v;
    float w;
} Edge;

void readdata(Edge edges[], int *len, const char *filepath)
{
    FILE *f = fopen(filepath, "r");
    int n;
    fscanf(f, "%d", &n);
    int u, v;
    for (u = 0; u < n; u++)
        for (v = 0; v < n; v++)
        {
            float w;
            fscanf(f, "%f", &w);
            if (u >= v)
                continue;
            edges[*len].u = u;
            edges[*len].v = v;
            edges[*len].w = w;
            *len = *len + 1;
        }

    fclose(f);
}

void swapedges(Edge *a, Edge *b)
{
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

void sortedges(Edge edges[], int len)
{
    int i;
    for (i = 0; i < len - 1; i++)
    {
        int j;
        int mid = i;
        for (j = i + 1; j < len; j++)
            if (edges[j].w < edges[mid].w)
                mid = j;
        swapedges(&edges[i], &edges[mid]);
    }
}

void printedges(const Edge edges[], int len)
{
    puts("+----------------------+");
    puts("| TT\tCung\tDo dai |");
    puts("+----------------------+");
    int i;
    for (i = 0; i < len; i++)
        printf("| %d\t%c%c\t%5.2f  |\n+----------------------+\n", i + 1, edges[i].u + 'A', edges[i].v + 'A', edges[i].w);
}

int findroot(int parents[], int u)
{
    while (u != parents[u])
        u = parents[u];
    return u;
}

int degree(Edge edges[], int len, int u)
{
    int d = 0;
    int i;
    for (i = 0; i < len; i++)
        d += edges[i].u == u || edges[i].v == u;
    return d;
}

void greedy(Edge edges[], int len)
{
    puts("Danh sach cung ban dau");
    printedges(edges, len);
    sortedges(edges, len);
    puts("Danh sach cung sau khi sap xep");
    printedges(edges, len);

    Edge solution[100];
    int parents[100];
    int n = 0;
    float total = 0;
    int i;
    for (i = 0; i < 100; i++)
        parents[i] = i;
    for (i = 0; i < len; i++)
    {
        solution[n] = edges[i];
        int root_u = findroot(parents, solution[n].u);
        int root_v = findroot(parents, solution[n].v);
        if (root_u == root_v)
            continue;
        if (degree(edges, len, solution[n].u) == 3)
            continue;
        if (degree(edges, len, solution[n].v) == 3)
            continue;
        parents[root_v] = parents[root_u];
        total += solution[n].w;
        n++;
    }
    puts("Phuong an");
    printedges(edges, n);
    printf("Tong do dai: %.2f\n", total);
}

int main()
{
    Edge edges[100];
    int len = 0;
    readdata(edges, &len, "./TSP.TXT");
    greedy(edges, len);
    return 0;
}