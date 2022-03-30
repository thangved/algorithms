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

void bubblesort(RecordType data[], int len)
{
    int i;
    for (i = 0; i < len - 1; i++)
    {
        int j;
        for (j = len - 1; j > 0; j--)
            if (data[j - 1].key > data[j].key)
                swap<RecordType>(data[j - 1], data[j]);
    }
}

int main()
{
    RecordType data[100];
    int len;
    cout << "Bubble Sort" << endl;
    readdata(data, len);
    cout << "Example array" << endl;
    printrecords(data, len);
    cout << endl
         << "Sorting..." << endl;
    bubblesort(data, len);
    cout << "Sorted!!!" << endl;
    printrecords(data, len);
    return 0;
}