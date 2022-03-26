#include <vector>
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

void insertionsort(std::vector<Recordtype> &data)
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