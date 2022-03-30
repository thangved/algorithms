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

int findpivot(const RecordType data[], int begin, int end)
{
    int i;
    for (i = begin; i <= end; i++)
        if (data[begin].key != data[i].key)
            return data[begin].key > data[i].key ? begin : i;
    return -1;
}

int partition(RecordType data[], int pl, int pr, int pivot)
{
    while (pl <= pr)
    {
        while (data[pl].key < pivot)
            pl++;
        while (data[pr].key >= pivot)
            pr--;
        if (pl < pr)
            swap<RecordType>(data[pl], data[pr]);
    }
    return pl;
}

void quicksort(RecordType data[], int begin, int end)
{
    int pid = findpivot(data, begin, end);
    if (pid == -1)
        return;

    int partitionindex = partition(data, begin, end, data[pid].key);
    quicksort(data, 0, partitionindex - 1);
    quicksort(data, partitionindex, end);
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
    quicksort(data, 0, len - 1);
    cout << "Sorted!!!" << endl;
    printrecords(data, len);
    return 0;
}