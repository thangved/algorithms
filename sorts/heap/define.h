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

void pushdown(vector<Recordtype> &data, int begin, int end)
{
    while (begin <= (end - 2) / 2)
    {
        if (end == 2 * begin + 1)
        {
            if (data[begin].key > data[end].key)
                swap(data[begin], data[end]);
            break;
        }
        if ((data[begin].key > data[begin * 2 + 1].key) && (data[begin * 2 + 1].key <= data[begin * 2 + 2].key))
        {
            swap(data[begin], data[begin * 2 + 1]);
            begin *= 2;
            begin += 1;
            continue;
        }

        if ((data[begin].key > data[begin * 2 + 2].key) && (data[begin * 2 + 1].key > data[begin * 2 + 2].key))
        {
            swap(data[begin], data[begin * 2 + 2]);
            begin *= 2;
            begin += 2;
            continue;
        }

        break;
    }
}

void heapsort(vector<Recordtype> &data)
{
    for (int i = (data.size() - 2) / 2; i >= 0; i--)
        pushdown(data, i, data.size() - 1);

    for (int i = data.size() - 1; i >= 2; i--)
    {
        swap(data[0], data[i]);
        pushdown(data, 0, i - 1);
    }
    swap(data[0], data[1]);
}

#endif
