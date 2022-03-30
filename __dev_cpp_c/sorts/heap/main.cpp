#include <iostream>
#include <fstream>

using namespace std;

typedef struct
{
    int key;
    float other;
} RecordType;

void readdata(RecordType data[], int &len, string filepath = "data.txt")
{
    len = 0;
    ifstream f;
    f.open(filepath, ios::binary);
    int key;
    float other;
    while (f >> key >> other)
    {
        RecordType temp = {key, other};
        data[len++] = temp;
    }

    f.close();
}

void printrecords(const RecordType data[], int len)
{
    int i;
    for (i = 0; i < len; i++)
        cout << data[i].key << "\t" << data[i].other << endl;
}

void pushdown(RecordType data[], int begin, int end)
{
    while (begin <= (end - 1) / 2)
    {
        if (begin * 2 + 1 == end)
        {
            if (data[begin].key > data[end].key)
                swap<RecordType>(data[begin], data[end]);
            break;
        }

        if ((data[begin].key > data[begin * 2 + 1].key) && (data[begin * 2 + 1].key <= data[begin * 2 + 2].key))
        {
            swap<RecordType>(data[begin], data[begin * 2 + 1]);
            begin = begin * 2 + 1;
            continue;
        }

        if ((data[begin].key > data[begin * 2 + 2].key) && (data[begin * 2 + 1].key > data[begin * 2 + 2].key))
        {
            swap<RecordType>(data[begin], data[begin * 2 + 2]);
            begin = begin * 2 + 2;
            continue;
        }

        break;
    }
}

void heapsort(RecordType data[100], int len)
{
    int i;
    for (i = (len - 2) / 2; i >= 0; i--)
        pushdown(data, i, len - 1);

    for (i = len - 1; i >= 2; i--)
    {
        swap<RecordType>(data[0], data[i]);
        pushdown(data, 0, i - 1);
    }
    swap<RecordType>(data[0], data[1]);
}

int main()
{
    RecordType data[100];
    int len;
    cout << "Quick Sort" << endl;
    readdata(data, len);
    cout << "Example array" << endl;
    printrecords(data, len);
    cout << endl
         << "Sorting..." << endl;
    heapsort(data, len);
    cout << "Sorted!!!" << endl;
    printrecords(data, len);
    return 0;
}