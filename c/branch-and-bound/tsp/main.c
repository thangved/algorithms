#include <stdio.h>

#define MAX_EDGE 100
typedef struct
{
    int u, v;
    float w;
    int used;
} Edge;

void resetedge(Edge edges[][MAX_EDGE], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            edges[i][j].used = 0;
}

float minedge(const Edge edges[][MAX_EDGE], int n)
{
    float edgemining = __FLT_MAX__;
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            if (edges[i][j].used)
                continue;
            if (edges[i][j].w >= edgemining)
                continue;
            edgemining = edges[i][j].w;
        }
    return edgemining;
}

float lowerbound(const Edge edges[][MAX_EDGE], int n, float totalvalue, int i)
{
    return totalvalue + (n - i) * minedge(edges, n);
}

int hascircle(Edge x[], int k, int next)
{
    int i;
    for (i = 0; i < k; i++)
        if (next == x[i].u)
            return 1;
    return 0;
}

void updatesolution(const Edge edges[][MAX_EDGE], int n, float totalvalue, float *minvaluecache, Edge x[], Edge solution[])
{
    x[n - 1] = edges[x[n - 2].v][x[0].u];
    totalvalue += x[n - 1].w;
    if (*minvaluecache <= totalvalue)
        return;
    *minvaluecache = totalvalue;
    int i;
    for (i = 0; i < n; i++)
        solution[i] = x[i];
}

void branchbound(Edge edges[][MAX_EDGE], int n, int i, int start, float *totalvalue, float *lb, float *minvaluecache, Edge x[], Edge solution[])
{
    int j;
    for (j = 0; j < n; j++)
        if (j != start && !edges[start][j].used && !hascircle(x, i, j))
        {
            *totalvalue = *totalvalue + edges[start][j].w;
            *lb = lowerbound(edges, n, *totalvalue, i + 1);

            if (*lb < *minvaluecache)
            {
                x[i] = edges[start][j];
                edges[start][j].used = 1;
                edges[j][start].used = 1;
                if (i == n - 2)
                    updatesolution(edges, n, *totalvalue, minvaluecache, x, solution);
                else
                    branchbound(edges, n, i + 1, j, totalvalue, lb, minvaluecache, x, solution);
            }
            *totalvalue = *totalvalue - edges[start][j].w;
            edges[start][j].used = 0;
            edges[j][start].used = 0;
        }
}

void readdata(Edge edges[][MAX_EDGE], const char *filepath, int *n)
{
    FILE *f = fopen(filepath, "r");
    fscanf(f, "%d", n);

    int i, j;
    for (i = 0; i < *n; i++)
        for (j = 0; j < *n; j++)
        {
            edges[i][j].u = i;
            edges[i][j].v = j;
            edges[i][j].used = 0;
            fscanf(f, "%f", &edges[i][j].w);
        }

    fclose(f);
}

void printmatrix(Edge edges[][MAX_EDGE], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%c%c = %5.2f\t", edges[i][j].u + 'A', edges[i][j].v + 'A', edges[i][j].w);
        puts("");
    }
}

void printsolution(Edge solution[], int n)
{
    const char *divider = "+-------------------------------------+";
    puts(divider);
    printf("| %5s%10s%10s%10s |\n", "#", "FROM", "TO", "LENGTH");
    puts(divider);
    int i;
    float tt = 0;
    for (i = 0; i < n; i++)
    {
        printf("| %5d", i + 1);
        printf("%10c", solution[i].u + 'A');
        printf("%10c", solution[i].v + 'A');
        printf("%10.2f |\n", solution[i].w);
        tt += solution[i].w;
    }

    puts(divider);

    printf("CIRCLE: %c", solution[0].u + 'A');
    for (i = 0; i < n; i++)
        printf(" -> %c", solution[i].v + 'A');
    puts("");

    printf("MIN LENGTH: %.2f\n", tt);
}

int main()
{
    Edge edges[MAX_EDGE][MAX_EDGE];
    Edge x[MAX_EDGE];
    Edge solution[MAX_EDGE];
    int n;
    readdata(edges, "./TSP1.txt", &n);

    char start, yn;
    int ctn = 1;
    while (ctn)
    {
        resetedge(edges, n);
        printmatrix(edges, n);
        float totalvalue = 0, lb = 0, minvaluecache = __FLT_MAX__;
        puts("Chon thanh pho xuat phat");
        scanf("\n%c", &start);
        branchbound(edges, n, 0, start - 'A', &totalvalue, &lb, &minvaluecache, x, solution);
        printsolution(solution, n);

        puts("Tiep tuc?(y/n)");
        scanf("\n%c", &yn);

        switch (yn)
        {
        case 'y':
        case 'Y':
            break;
        case 'n':
        case 'N':
            ctn = 0;
            break;
        default:
            ctn = 0;
            break;
        }
    }
    return 0;
}