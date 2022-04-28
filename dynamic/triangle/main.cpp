#include <iostream>
#include <vector>
#include <fstream>

#define MAX_N 100

void readdata(int Data[][MAX_N], int &n, const std::string &filepath)
{
    n = 0;
    std::ifstream f = std::ifstream(filepath);

    while (!f.eof())
    {
        n++;
        for (int i = 1; i <= n; i++)
            f >> Data[n][i];
    }

    f.close();
}

int printpath(int P[][MAX_N], int F[][MAX_N], int row, int col)
{
    if (!row)
        return 0;

    int p = printpath(P, F, row - 1, P[row][col]);
    std::cout << "(" << row << ", " << col << "): " << (F[row][col] - p) << std::endl;
    return F[row][col];
}

void foundpath(const int Data[][MAX_N], int n)
{
    int F[MAX_N][MAX_N] = {};
    int P[MAX_N][MAX_N] = {};
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            int maxindex = j - 1;
            if (F[i - 1][maxindex] < F[i - 1][j])
                maxindex = j;
            if (F[i - 1][maxindex] < F[i - 1][j + 1])
                maxindex = j + 1;
            F[i][j] = Data[i][j] + F[i - 1][maxindex];
            P[i][j] = maxindex;
        }
    }

    int maxindex = 1;
    for (int i = 2; i <= n; i++)
        if (F[n][maxindex] < F[n][i])
            maxindex = i;

    std::cout << "MAX: " << F[n][maxindex] << std::endl;
    printpath(P, F, n, maxindex);
}

int main()
{
    int Data[MAX_N][MAX_N] = {};
    int n;
    readdata(Data, n, "./tam_giac_so.txt");
    foundpath(Data, n);
    return 0;
}