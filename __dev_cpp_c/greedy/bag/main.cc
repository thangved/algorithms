#include "define.h"

int limit(const Item &item)
{
    // bag 1 & bag 2
    return item.count;

    // bag 3
    // return 1;
}

int main()
{
    // Bag 1
    Bagtype bag = readbagfromfile("./CaiBalo1.txt");

    // Bag 2
    // Bagtype bag = readbagfromfile("./CaiBalo2.txt", true);

    // Bag 3
    // Bagtype bag = readbagfromfile("./CaiBalo3.txt");

    greedy(bag, limit);

    for (auto i = bag.items.begin(); i != bag.items.end(); i++)
        cout << i->count << i->name << endl;

    cout << "---" << endl;
    cout << "Tong gia tri: " << bag.totalvalue << endl;
    cout << "Tong trong luong: " << bag.totalweight << endl;
    return 0;
}