/**
 * @file define.h
 * @author thangved (thangved02@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-03-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _DEFINE_H
#define _DEFINE_H

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

int findpivot(vector<Recordtype> data, int begin, int end)
{
    for (int i = begin; i <= end; i++)
        if (data[i].key != data[begin].key)
            return data[begin].key > data[i].key ? begin : i;

    return -1;
}

int partition(vector<Recordtype> &data, int begin, int end, int pivot)
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

void quicksort(vector<Recordtype> &data, int begin, int end)
{
    int pivotindex = findpivot(data, begin, end);

    if (pivotindex == -1)
        return;

    int pid = partition(data, begin, end, data[pivotindex].key);
    quicksort(data, begin, pid - 1);
    quicksort(data, pid, end);
}

#endif
