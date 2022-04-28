#include <stdio.h>

typedef struct
{
	char name[20];
	float weight, value, cost;
	int select;
} Item;

typedef struct
{
	float upperbound;
	float total;
} Node;

int readdata(Item items[], int &n, const char *filepath)
{
	n = 0;
	FILE *f = fopen(filepath, "r");
	int W;
	fscanf(f, "%d", &W);	
	while(!feof(f))
	{
		fscanf(f, "%f%f %[^\n]", &items[n].weight, &items[n].value, items[n].name);
		items[n].cost = items[n].value / items[n].weight;
		n++;
	}
	
	fclose(f);
	return W;
}

void swap(Item &a, Item &b)
{
	Item c = a;
	a = b;
	b = c;
}

void sort(Item items[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = n - 1; j > i; j--)
			if (items[j].cost > items[j - 1].cost)
				swap(items[j], items[j - 1]);
}

int maxvaluecache;

void branchbound(Item items[], int step, int n, int W, Node parent, int x[])
{
	int maxoption = (int) (W / items[step].cost);
	while (maxoption-- >= 0)
	{
		int total = parent.total + items[step].value * maxoption;
		x[step] = maxoption;
		if (step == n - 1)
			if (total > maxvaluecache)
			{
				maxvaluecache = total;
				int k;
				for (k = 0; k < n; k++)
					items[k].select = x[k];
				continue;
			}
		int w = W - maxoption * items[step].weight;
		int upperbound = w * items[step + 1].cost;
		if (upperbound <= maxvaluecache)
			continue;
		Node node = {upperbound, total};
		branchbound(items, step + 1, n, w, node, x);
	}
}

void printItems(Item items[], int n)
{
	int i;
	const char *div = "+------------------------------------------------------------------------+";
	puts(div);
	printf("| %5s%25s%10s%10s%10s%10s |\n", "#", "Name", "Weight", "Value", "Cost", "Select");
	
	for (i = 0; i < n; i++)
		printf("| %5d%25s%10.2f%10.2f%10.2f%10d |\n", i + 1, items[i].name, items[i].weight, items[i].value, items[i].cost, items[i].select);
	
	puts(div);
}

int main()
{
	Item items[100];
	int n;
	int W = readdata(items, n, "./caibalo1.txt");
	sort(items, n);
	Node node = {W * items[0].cost, 0};
	maxvaluecache = 0;
	int x[100];
	branchbound(items, 0, n, W, node, x);
	printItems(items, n);
	return 0;
}
