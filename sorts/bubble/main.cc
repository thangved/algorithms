#include <iostream>
#include <fstream>
#include <vector>

#include "define.h"

using namespace std;

int main()
{
    ifstream file = ifstream("./data.txt");

    vector<Recordtype> data;
    int key;
    float value;

    while (file >> key >> value)
    {
        Recordtype temp = {key, value};
        data.push_back(temp);
    }

    file.close();

    bubblesort(data);
    for (int i = 0; i < (int)data.size(); i++)
        cout << data[i].key << ": " << data[i].other << endl;

    return 0;
}