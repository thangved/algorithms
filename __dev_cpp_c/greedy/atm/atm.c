/**
 * KIM MINH THANG
 * B2007210
 * GREEDY - ATM
 */

#include <stdio.h>
#include <string.h>

#define MAXLABELLENGTH 40

typedef struct
{
    int value;
    char label[MAXLABELLENGTH];
} MoneyType;

void readdata(MoneyType moneytypes[], int *len, const char *filepath)
{
    FILE *file = fopen(filepath, "r");
    while (!feof(file))
    {
        fscanf(file, "%d %39[^\n]", &moneytypes[*len].value, moneytypes[*len].label);
        *len = *len + 1;
    }

    fclose(file);
}

void swap(MoneyType *a, MoneyType *b)
{
    MoneyType c = *a;
    *a = *b;
    *b = c;
}

void pushdown(MoneyType moneytypes[], int first, int last)
{
    while (first * 2 + 1 <= last)
    {
        if (first * 2 + 1 == last)
        {
            if (moneytypes[first].value > moneytypes[last].value)
                swap(&moneytypes[first], &moneytypes[last]);
            break;
        }
        if (moneytypes[first].value > moneytypes[first * 2 + 1].value && moneytypes[first * 2 + 1].value <= moneytypes[first * 2 + 2].value)
        {
            swap(&moneytypes[first], &moneytypes[first * 2 + 1]);
            first = first * 2 + 1;
            continue;
        }
        if (moneytypes[first].value > moneytypes[first * 2 + 2].value && moneytypes[first * 2 + 1].value > moneytypes[first * 2 + 2].value)
        {
            swap(&moneytypes[first], &moneytypes[first * 2 + 2]);
            first = first * 2 + 2;
            continue;
        }
        break;
    }
}
void descrease(MoneyType moneytypes[], const int len)
{
    int i;
    for (i = (len - 2) / 2; i >= 0; i--)
        pushdown(moneytypes, i, len - 1);
    for (i = len - 1; i > 1; i--)
    {
        swap(&moneytypes[0], &moneytypes[i]);
        pushdown(moneytypes, 0, i - 1);
    }
    swap(&moneytypes[0], &moneytypes[1]);
}

void returnmoneys(const MoneyType moneytypes[], const int len, const int withdrawvalue)
{
    int overbalance = withdrawvalue;
    int returns[100] = {};
    const MoneyType *money = moneytypes;
    while (money != moneytypes + len)
    {
        returns[money - moneytypes] = overbalance / money->value;
        overbalance %= money->value;
        money++;
    }

    puts("+----------------------------------------------------------------------+");
    printf("| TT\tGia tri\t%40s\tSo to  |\n", "Menh gia");
    puts("+----------------------------------------------------------------------+");

    int i;
    int tt = 1;
    int total = 0;
    for (i = 0; i < len; i++)
    {
        total += returns[i] * moneytypes[i].value;
        if (returns[i])
            printf("| %d\t%d\t%40s\t%d      |\n+----------------------------------------------------------------------+\n", tt++, moneytypes[i].value, moneytypes[i].label, returns[i]);
    }

    printf("So tien can rut: %d\n", withdrawvalue);
    printf("So tien thuc te: %d\n", total);
    if (withdrawvalue - total)
        printf("Khong the rut so tien tren do ATM khong the tra menh gia: %d", withdrawvalue - total);
}

int main()
{
    MoneyType moneytypes[100];
    int len = 0;
    readdata(moneytypes, &len, "./ATM.TXT");
    descrease(moneytypes, len);
    int withdrawvalue;
    scanf("%d", &withdrawvalue);
    returnmoneys(moneytypes, len, withdrawvalue);
    return 0;
}