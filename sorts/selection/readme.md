# Selection sort (Sắp xếp chọn)

## Ý tưởng 🔅

Ý tưởng chính của sắp xếp chọn là duyệt qua hết tất cả các phần tử của mảng và chuyển dần phần tử có giá trị nhỏ nhất về đầu mảng.

```cpp
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
```
