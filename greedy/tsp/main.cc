#include "define.h"

int main()
{
    graph g = readgraphfromfile("./TSP.txt");
    graph result = greedy(g);
    marked.fill(false);
    hascircled = false;

    circled(result, 1, -1);
    printpath(parents, circlestart, circleend);
    cout << "Path Length: " << pathlen(result);

    return 0;
}