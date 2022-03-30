#include "define.h"

int main()
{
    vector<Moneytype> moneytypes = readmoneytypes("./ATM.txt");
    decrease(moneytypes);

    cout << "Nhap so tien can rut" << endl;
    cout << "So tien can rut phai la boi so cua" << (moneytypes.end() - 1)->other << endl;

    int withdrawcost;
    cin >> withdrawcost;

    vector<int> withdraws = greedy(moneytypes, withdrawcost);

    cout << "Ban can phai rut" << endl;

    cout << "---" << endl;
    int count = 0;
    for (int i = 0; i < (int)withdraws.size(); i++)
        if (withdraws[i])
        {
            count += withdraws[i];
            cout << withdraws[i] << " to" << moneytypes[i].other << endl;
        }

    cout << "---" << endl
         << "Tong cong: " << count << " to tien" << endl;

    return 0;
}