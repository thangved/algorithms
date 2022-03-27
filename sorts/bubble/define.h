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

void bubblesort(vector<Recordtype> &data)
{
    for (int i = (int)data.size(); i > 0; i--)
        for (int j = 0; j < i - 1; j++)
            if (data[j].key > data[j + 1].key)
                swap(data[j], data[j + 1]);
}

#endif
