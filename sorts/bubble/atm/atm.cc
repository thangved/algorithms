#include <iostream>
#include <fstream>
#include <vector>

#include "define_atm.h"

using namespace std;

int main()
{
    ifstream file = ifstream("./data.txt");

    vector<recordtype> data;
    int key;
    string value;

    while (file >> key)
    {
        getline(file, value);
        recordtype temp = {key, value};
        data.push_back(temp);
    }

    file.close();

    bubblesort(data);
    for (int i = 0; i < (int)data.size(); i++)
        cout << data[i].key << ": " << data[i].other << endl;

    return 0;
}