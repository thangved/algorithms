#include <stdio.h>

#define MAX_N 100

void readdata(int A[][MAX_N], int *n, const char *filepath)
{
    FILE *f = fopen(filepath, "r");
    *n = 0;
    while (!feof(f))
    {
        *n = *n + 1;
        int i;
        for (i = 1; i <= *n; i++)
            fscanf(f, "%d", &A[*n][i]);
    }
    fclose(f);
}

void printtriangle(int A[][MAX_N], int n)
{
    int i, j;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= i; j++)
            printf("%d ", A[i][j]);
        puts("");
    }
}

void printpath(int P[][MAX_N], int i, int last)
{
    if (i == 1)
    {
        printf("(%d, %d)", last, i);
        return;
    }

    printpath(P, i - 1, P[i][last]);
    printf(" -> (%d, %d)", last, i);
}

void findpath(int A[][MAX_N], int n)
{
    int F[MAX_N][MAX_N] = {};
    int P[MAX_N][MAX_N] = {};

    int i, j;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= i; j++)
        {
            int maxindex = j - 1;
            if (A[i - 1][j] > A[i][maxindex])
                maxindex = j;
            if (A[i - 1][j + 1] > A[i][maxindex])
                maxindex = j + 1;
            F[i][j] = A[i][j] + A[i - 1][maxindex];
            P[i][j] = maxindex;
        }

    int maxindex = 0;

    for (i = 1; i <= n; i++)
        if (F[n][i] > F[n][maxindex])
            maxindex = i;

    printf("Tong gia tri cua cac so tren duong di: %d\n", F[n][maxindex]);
    printf("Duong di: ");
    printpath(P, n, maxindex);
    puts("");
}

int main()
{
    int A[MAX_N][MAX_N];
    int n;
    readdata(A, &n, "./tam_giac_so.txt");
    printtriangle(A, n);
    findpath(A, n);
    return 0;
}