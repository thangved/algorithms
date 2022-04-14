/**
 * @file TSP - BAG 1
 * @author KIM MINH THANG - B2007210
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	char name[40];
	int v, w, n;
	float c;
} Item;

Item *readdata(int *n, int *w, const char *filepath)
{
	*n = 0;
	Item *items = (Item *)malloc(sizeof(Item));
	FILE *f = fopen(filepath, "r");

	fscanf(f, "%d", w);
	while (!feof(f))
	{
		fscanf(f, "%d%d %39[^\n]", &items[*n].w, &items[*n].v, items[*n].name);
		items[*n].c = (float)items[*n].v / (float)items[*n].w;
		*n = *n + 1;
		items = (Item *) realloc(items, sizeof(Item) * (*n + 1));
	}

	fclose(f);
	return items;
}

void printitems(const Item items[], int n)
{
	const char *divider = "+-----------------------------------------------------------------------------+";
	puts(divider);
	printf("| %5s%30s%10s%10s%10s%10s |\n", "#", "Name", "Weight", "Value", "Cost", "Select");
	puts(divider);

	const Item *item = items;
	int tt = 1;
	for (; item != items + n; item++)
		printf("| %5d%30s%10d%10d%10.2f%10d |\n%s\n", tt++, item->name, item->w, item->v, item->c, item->n, divider);
}

void swap(Item *a, Item *b)
{
	Item temp = *a;
	*a = *b;
	*b = temp;
}

void insertionsort(Item items[], int n)
{
	int i;
	for (i = 1; i < n; i++)
	{
		int j = i;
		while (j > 0 && items[j].c > items[j - 1].c)
		{
			swap(&items[j], &items[j - 1]);
			j--;
		}
	}
}

int min(int a, int b)
{
	return a < b ? a : b;
}
void greedy(Item items[], int n, int w)
{
	int empty = w;

	int i;
	int total = 0;
	for (i = 0; i < n; i++)
	{
		items[i].n = empty / items[i].w;
		items[i].n = min(1, items[i].n);
		empty -= items[i].n * items[i].w;
		total += items[i].n * items[i].v;
	}
	
	printitems(items, n);
	printf("Phuong an: X(%d", items[0].n);
	for (i = 1; i < n; i++)
		printf(", %d", items[i].n);
	puts(")");
	printf("Tong trong luong cua do vat: %d\n", w - empty);
	printf("Trong luong con lai: %d\n", empty);
	printf("Tong gia tri: %d\n", total);
}

int main()
{
	int n;
	int w;
	Item *items = readdata(&n, &w, "./CaiBalo3.txt");
	greedy(items, n, w);
	return 0;
}