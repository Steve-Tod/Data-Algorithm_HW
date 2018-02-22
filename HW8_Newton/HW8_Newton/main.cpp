#include "math.h"
#include "stdio.h"
#include <complex>

using namespace std;

complex<double> F(const complex<double> x, const complex<double> y, double **a)
{
    complex<double> x0[4] = {1, x, x*x, x*x*x}, y0[4] = {1, y, y*y, y*y*y}, sum = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            sum += a[i][j] * x0[i] * y0[j];
        }
    }
    return sum;
}

complex<double> Fx(complex<double> x, complex<double> y, double **a)
{
    complex<double> x0[4] = {0, 1, 2.0*x, 3.0*x*x}, y0[4] = {1, y, y*y, y*y*y}, sum = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            sum += a[i][j] * x0[i] * y0[j];
        }
    }
    return sum;
}

complex<double> Fy(complex<double> x, complex<double> y, double **a)
{
    complex<double> x0[4] = {1, x, x*x, x*x*x}, y0[4] = {0, 1, 2.0*y, 3.0*y*y}, sum = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            sum += a[i][j] * x0[i] * y0[j];
        }
    }
    return sum;
}

void NewtonRaf(double **a1, double **a2, complex<double> *xy)
{
    int term = 0, solved = 0;
    complex<double> y1, y2, dx1, dx2, dy1, dy2;
    double Res = 1.0;
    while (term < 200) {
        //Calc y
        y1 = F(xy[0], xy[1], a1);
        y2 = F(xy[0], xy[1], a2);
        Res = abs(y1)>abs(y2) ? abs(y1):abs(y2);
        if (Res < 1e-6)
        {
            solved = 1;
            break;
        }
        //Jacobi
        dx1 = Fx(xy[0], xy[1], a1);
        dx2 = Fx(xy[0], xy[1], a2);
        dy1 = Fy(xy[0], xy[1], a1);
        dy2 = Fy(xy[0], xy[1], a2);
        //Change x
        complex<double> det = dx1*dy2 - dy1*dx2;
        xy[0] -= (dy2*y1 - dy1*y2)/det;
        xy[1] -= (-dx2*y1 + dx1*y2)/det;
        term += 1;
    }
}

int main() {
    double **a1 = new double*[4], **a2 = new double*[4];
    complex<double> xy[2] = {complex<double>(1, 1), complex<double>(1, 2)};
    for (int i = 0; i < 4; i++)
    {
        a1[i] = new double[4];
        a2[i] = new double[4];
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            scanf("%lf", &a1[i][j]);
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            scanf("%lf", &a2[i][j]);
        }
    }
    NewtonRaf(a1, a2, xy);
    printf("%.15lf %.15lf\n", real(xy[0]), imag(xy[0]));
    printf("%.15lf %.15lf\n", real(xy[1]), imag(xy[1]));
    return 0;
}
