#include <iostream>
#include <fstream>
#include <vector>

#include "define.h"

using namespace std;

int main()
{
    ifstream file = ifstream("./data.txt");

    vector<recordtype> data;
    int key;
    float value;

    while (file >> key >> value)
    {
        recordtype temp = {key, value};
        data.push_back(temp);
    }

    file.close();

    quicksort(data, 0, data.size() - 1);
    for (int i = 0; i < (int)data.size(); i++)
        cout << data[i].key << ": " << data[i].other << endl;

    return 0;
}