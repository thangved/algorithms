#include <vector>
#include <iostream>

typedef struct
{
    int key;
    std::string other;
} recordtype;

void swap(recordtype &a, recordtype &b)
{
    recordtype c = b;
    b = a;
    a = c;
}

void insertionsort(std::vector<recordtype> &data)
{
    for (int i = 1; i < (int)data.size(); i++)
    {
        int j = i;
        while (data[j].key < data[j - 1].key && j != 0)
        {
            swap(data[j], data[j - 1]);
            j--;
        }
    }
}