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

int findpivot(std::vector<recordtype> data, int begin, int end)
{
    for (int i = begin; i <= end; i++)
        if (data[i].key != data[begin].key)
            return data[begin].key > data[i].key ? begin : i;

    return -1;
}

int partition(std::vector<recordtype> &data, int begin, int end, int pivot)
{
    while (begin <= end)
    {
        while (data[begin].key < pivot)
            begin++;
        while (data[end].key >= pivot)
            end--;
        if (end > begin)
            swap(data[end], data[begin]);
    }

    return begin;
}

void quicksort(std::vector<recordtype> &data, int begin, int end)
{
    int pivotindex = findpivot(data, begin, end);

    if (pivotindex == -1)
        return;

    int pid = partition(data, begin, end, data[pivotindex].key);
    quicksort(data, begin, pid - 1);
    quicksort(data, pid, end);
}