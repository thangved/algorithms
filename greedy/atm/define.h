#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
typedef struct
{
    int key;
    std::string other;
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

std::vector<Moneytype> readmoneytypes(std::string filepath)
{
    std::vector<Moneytype> data;
    std::ifstream file = std::ifstream(filepath);
    int key;
    std::string value;
    while (file >> key)
    {
        getline(file, value);
        Recordtype r = {key, value};
        data.push_back(r);
    }
    file.close();
    return data;
}

std::vector<int> greedy(std::vector<Moneytype> moneytypes, int withdrawcost)
{
    std::vector<int> withdraws;
    for (auto money = moneytypes.begin(); money != moneytypes.end(); money++)
    {
        withdraws.push_back(withdrawcost / money->key);
        withdrawcost -= money->key * (withdrawcost / money->key);
    }
    return withdraws;
}