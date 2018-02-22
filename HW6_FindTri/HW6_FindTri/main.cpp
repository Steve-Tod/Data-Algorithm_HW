#include <iostream>
#include <algorithm>
using namespace std;

int cmp(const int a, const int b)
{
    return a < b;
}

int main()
{
    int l, a, b;
    long long cnta = 0, cntb = 0;
    cin >> l >> a >> b;
    int *data = new int[l];
    for (int i = 0; i < l; i++)
    {
        cin >> data[i];
    }
    sort(data, data + l, cmp);
    int sum_temp;
    for (int i = 0; i < l; i++)
    {
        int s = i + 1, e = l - 1;
        while(s < e)
        {
            sum_temp = data[i] + data[s] + data[e];
            if (sum_temp <= b)
            {
                cntb += e - s;
                s++;
            }
            if (sum_temp > b)
            {
                e--;
            }
        }
    }
    for (int i = 0; i < l; i++)
    {
        int s = i + 1, e = l - 1;
        while(s < e)
        {
            sum_temp = data[i] + data[s] + data[e];
            if (sum_temp < a)
            {
                cnta += e - s;
                s++;
            }
            if (sum_temp >= a)
            {
                e--;
            }
        }
    }
    cout << cntb - cnta << endl;
    return 0;
}
