#include <vector>

using namespace std;

typedef struct
{
    int key;
    float other;
} Recordtype;

void swap(Recordtype &a, Recordtype &b)
{
    Recordtype c = b;
    b = a;
    a = c;
}

void bubblesort(vector<Recordtype> &data)
{
    for (int i = (int)data.size(); i > 0; i--)
    {
        for (int j = 0; j < i - 1; j++)
            if (data[j].key > data[j + 1].key)
                swap(data[j], data[j + 1]);
    }
}