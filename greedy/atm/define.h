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
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
typedef struct
{
    int key;
    string other;
} Recordtype;

typedef Recordtype Moneytype;

void swap(Recordtype &a, Recordtype &b)
{
    Recordtype c = b;
    b = a;
    a = c;
}

bool compare(const Recordtype &a, const Recordtype &b)
{
    return a.key > b.key;
}

void decrease(vector<Recordtype> &data)
{
    sort(data.begin(), data.end(), compare);
}

vector<Moneytype> readmoneytypes(string filepath)
{
    vector<Moneytype> data;
    ifstream file = ifstream(filepath);
    int key;
    string value;
    while (file >> key)
    {
        getline(file, value);
        Recordtype r = {key, value};
        data.push_back(r);
    }
    file.close();
    return data;
}

vector<int> greedy(vector<Moneytype> moneytypes, int withdrawcost)
{
    vector<int> withdraws;
    for (auto money = moneytypes.begin(); money != moneytypes.end(); money++)
    {
        withdraws.push_back(withdrawcost / money->key);
        withdrawcost -= money->key * (withdrawcost / money->key);
    }
    return withdraws;
}

#endif
