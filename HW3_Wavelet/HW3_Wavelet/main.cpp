#include <iostream>
#include <iomanip>
using namespace std;
int p2(int n)
{
    int temp = 1;
    for (int i = 1; i<=n; i++)
    {
        temp *=2;
    }
    return temp;
}

void fun(float *data, int length)
{
    float *a = new float[length / 2];
    float *b = new float[length / 2];
    for (int i = 0; i < length / 2; i++)
    {
        a[i] = (data[2 * i] + data[2 * i + 1]) / 2;
        b[i] = -(data[2 * i] - data[2 * i + 1]) / 2;
    }
    for (int i = 0; i < length / 2; i++)
    {
        data[i] = a[i];
        data[length / 2 + i] = b[i];
    }
    delete []a;
    delete []b;
}

void Print(float *data, int length)
{
    cout.setf(ios::fixed);
    for (int i = 0; i < length; i++)
    {
        cout << fixed<< setprecision(4) << data[i] << ' ';
    }
}

void main_fun(float *&data, int length)
{
    float *a, *b;
    fun(data, length);
    a = &data[0];
    b = &data[length / 2];
    if (length == 2)
    {
        Print(a, 1);
    }
    else
    {
        main_fun(a, length / 2);
    }
    Print(b, length / 2);
}

int main() {
    int L;
    cin >> L;
    int n = p2(L);
    float *signal = new float[n];
    float temp1, temp2;
    for (int i = 0; i < n / 2; i++)
    {
        cin >> temp1 >> temp2;
        signal[i] = (temp1 + temp2) / 2;
        signal[n / 2 + i] = -(temp1 - temp2) / 2;
    }
    main_fun(signal, n / 2);
    float *temp = &signal[n / 2];
    Print(temp, n / 2);
    delete []signal;
    return 0;
}

