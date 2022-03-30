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

void insertionsort(RecordType data[], int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        int minindex = i;
        int j = i;
        while (data[j].key < data[j - 1].key && j > 0)
        {
            swap<RecordType>(data[j], data[j - 1]);
            j--;
        }
    }
}

int main()
{
    RecordType data[100];
    int len;
    cout << "Insertion Sort" << endl;
    readdata(data, len);
    cout << "Example array" << endl;
    printrecords(data, len);
    cout << endl
         << "Sorting..." << endl;
    insertionsort(data, len);
    cout << "Sorted!!!" << endl;
    printrecords(data, len);
    return 0;
}