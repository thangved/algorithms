#include <vector>
#include <iostream>
#include <fstream>

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

void pushdown(std::vector<Recordtype> &data, int begin, int end)
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

void heapsort(std::vector<Recordtype> &data)
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