#include <stdio.h>
#define MAX_M 500
typedef struct
{
    int u, v;
} Edge;

typedef struct
{
    int n, m;
    Edge edges[MAX_M];
} Graph;

// Khởi tạo đồ thị
void init_graph(Graph *pG, int n)
{
    pG->n = n;
    pG->m = 0;
}
// Thêm cung (u, v)
void add_edge(Graph *pG, int u, int v)
{
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->m++;
}
// Tính bậc của u
int degree(Graph *pG, int u)
{
    int d = 0;
    for (int i = 0; i < pG->m; i++)
    {
        if (pG->edges[i].u == u)
            d++;
        if (pG->edges[i].v == u)
            d++;
    }
    return d;
}

// Chương trình chính
int main()
{
    Graph G;
    //Đọc dữ liệu vào đồ thị G
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }

    // In bậc của các đỉnh
    for (int u = 1; u <= n; u++)
        printf("deg[%d] = %d\n", u, degree(&G, u));
    return 0;
}
