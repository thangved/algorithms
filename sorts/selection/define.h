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

void selectionsort(std::vector<Recordtype> &data)
{
    for (int i = 0; i < (int)data.size() - 1; i++)
    {
        int sid = i;
        int mid = i;
        for (int j = i + 1; j < (int)data.size(); j++)
            if (data[j].key < data[mid].key)
                mid = j;

        swap(data[sid], data[mid]);
    }
}