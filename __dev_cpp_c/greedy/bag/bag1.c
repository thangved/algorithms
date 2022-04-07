#include <stdio.h>

typedef struct 
{
	char label[100];
	int weight, cost, count;
	float value;
} Itemtype;

typedef struct {
	int maxweight;
	Itemtype items[100];
	int countitems;
} Bagtype;

Bagtype readdata(const char * filepath)
{
	Bagtype bag;
	bag.countitems = 0;
	FILE * f = fopen(filepath, "r");

	fscanf(f, "%d", &bag.maxweight);

	while(!feof(f))
	{
		fscanf(f, "%d%d %99[^\n]", &bag.items[bag.countitems].weight, &bag.items[bag.countitems].cost, bag.items[bag.countitems].label);	
		bag.items[bag.countitems].value = (float)bag.items[bag.countitems].cost / (float) bag.items[bag.countitems].weight;
		bag.countitems++;
	}
	fclose(f);
	return bag;
}

int main()
{
	Bagtype bag = readdata("CaiBalo1.txt");
	int i;
	for(i = 0; i < bag.countitems; i++)
		printf("%d %d %.2f %s\n", bag.items[i].weight, bag.items[i].cost, bag.items[i].value, bag.items[i].label);
    return 0;
}