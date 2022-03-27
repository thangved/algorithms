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

void selectionsort(vector<Recordtype> &data)
{
    for (int i = 0; i < (int)data.size() - 1; i++)
    {
        // Khoi tao min index
        int mid = i;

        // Tìm vị trí có giá trị key nhỏ nhất
        for (int j = i + 1; j < (int)data.size(); j++)
            if (data[j].key < data[mid].key)
                mid = j;

        // Hoán đổi phần tử có key nhỏ nhất với phần tử tại vị trí i
        swap(data[i], data[mid]);
    }
}

#endif
