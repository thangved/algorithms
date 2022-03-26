#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

typedef struct
{
    string name;
    int weight, cost;
    float value;
    int count;
} Item;

typedef struct
{
    vector<Item> items;
    int maxweight, totalweight, totalvalue;
} Bagtype;

Bagtype readbagfromfile(const string &filepath, const bool haslimit = false)
{
    vector<Item> data;
    ifstream file = ifstream(filepath);

    int maxweight;
    file >> maxweight;

    int weight, cost;

    while (file >> weight >> cost)
    {
        int count = 0;
        if (haslimit)
            file >> count;
        string name;
        getline(file, name);
        Item item = {name, weight, cost, ((float)cost / weight), count};

        data.push_back(item);
    }

    file.close();

    return {data, maxweight, 0, 0};
}

bool compare(const Item &a, const Item &b)
{
    return a.value > b.value;
}
void greedy(Bagtype &bag, int(limit(const Item &item)))
{
    // Sorting...
    sort(bag.items.begin(), bag.items.end(), compare);
    // Sorted!!!

    // Initial totalvalue, emptyweight
    bag.totalvalue = 0;
    int emptyweight = bag.maxweight;

    // Starting...
    for (auto b = bag.items.begin(); b != bag.items.end(); b++)
    {
        int count = emptyweight / b->weight;

        if (limit(*b))
            count = min(limit(*b), count);

        b->count = count;
        bag.totalvalue += count * b->cost;
        emptyweight -= count * b->weight;
        continue;
    }
    bag.totalweight = bag.maxweight - emptyweight;
    // End!!!
}