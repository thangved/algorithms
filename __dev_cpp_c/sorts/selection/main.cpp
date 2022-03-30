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

void selectionsort(RecordType data[], int len)
{
    int i;
    for (i = 0; i < len - 1; i++)
    {
        int minindex = i;
        int j;
        for (j = i + 1; j < len; j++)
            if (data[minindex].key > data[j].key)
                minindex = j;

        swap<RecordType>(data[i], data[minindex]);
    }
}

void printrecords(const RecordType data[], int len)
{
    int i;
    for (i = 0; i < len; i++)
        cout << data[i].key << "\t" << data[i].other << endl;
}

int main()
{
    RecordType data[100];
    int len;
    cout << "Selection Sort" << endl;
    readdata(data, len);
    cout << "Example array" << endl;
    printrecords(data, len);
    cout << endl
         << "Sorting..." << endl;
    selectionsort(data, len);
    cout << "Sorted!!!" << endl;
    printrecords(data, len);
    return 0;
}