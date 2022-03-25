#include <vector>
typedef struct
{
    int key;
    float other;
} recordtype;

void swap(recordtype &a, recordtype &b)
{
    recordtype c = b;
    b = a;
    a = c;
}

void bubblesort(std::vector<recordtype> &data)
{
    for (int i = (int)data.size(); i > 0; i--)
    {
        for (int j = 0; j < i - 1; j++)
            if (data[j].key > data[j + 1].key)
                swap(data[j], data[j + 1]);
    }
}