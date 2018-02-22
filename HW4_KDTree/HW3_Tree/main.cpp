#include "stdio.h"
#include <iostream>
#include <algorithm>
using namespace std;


struct Point//点类
{
    int num, x, y;
    Point(int num=-1, int x=-1, int y=-1): num(num), x(x), y(y) {}
    void set(int n, int x0, int y0)
    {
        num = n;
        x = x0;
        y = y0;
    }
    int xy(bool split)
    {
        if (split)
            return x;
        else
            return y;
    }
};

struct Range//范围类
{
    int low, high;
    Range(int l=-1, int h=-1): low(l), high(h) {}
    Range(Range &c): low(c.low), high(c.high) {}
    void set(int l, int h)
    {
        low = l;
        high = h;
    }
    bool IncludeP(Point &p, bool xy)
    {
        return p.xy(xy) >= low && p.xy(xy) <= high;
    }
    bool IncludeR(const Range &r)
    {
        return r.low > low && r.high < high;
    }
    bool CrossR(const Range &r)
    {
        return !(r.low > high || r.high < low);
    }
};

class kdt
{
private:
    Point *data;
    int num;
    Range Trange;
    bool split;//分裂轴,true=以x为依据
    kdt *lc, *rc, *p;
public:
    kdt(Point *dataset, int setlen, kdt *parent, bool spAxis,int low, int high);
    void find(Range &rx, Range &ry, int &count, bool x_ok, bool y_ok);
};

bool xcomp(const Point &a, const Point &b)
{
    return a.x < b.x;
}

bool ycomp(const Point &a, const Point &b)
{
    return a.y < b.y;
}

kdt::kdt(Point *dataset, int setlen, kdt *parent, bool spAxis,int l, int h): lc(NULL), rc(NULL), p(parent), split(spAxis), Trange(l, h), num(setlen)
{
    if (split)
    {
        sort(&dataset[0], &dataset[setlen], xcomp);
    }
    else
    {
        sort(&dataset[0], &dataset[setlen], ycomp);
    }
    if (setlen == 1)//只剩一个节点
    {
        data = &dataset[0];
        return;
    }
    if (setlen == 2)//只剩两个节点
    {
        data = &dataset[1];
        lc = new kdt(dataset, 1, this, !split, dataset[0].xy(split), dataset[0].xy(split));
        return;
    }
    int n1, n2;
    if (setlen % 2 == 0)
    {
        n1 = setlen / 2;
        n2 = n1 - 1;
        data = &dataset[n1];
    }
    else
    {
        n1 = setlen / 2;
        n2 = n1;
        data = &dataset[n1];
    }
    
    int llow = dataset[0].xy(split), lhigh = dataset[n1 - 1].xy(split), rlow = dataset[n1 + 1].xy(split), rhigh = dataset[setlen - 1].xy(split);
    lc = new kdt(dataset, n1, this, !split, llow, lhigh);
    rc = new kdt(&(dataset[n1 + 1]), n2, this, !split, rlow, rhigh);
}

void kdt::find(Range &rx, Range &ry, int &count, bool x_ok, bool y_ok)
{
    //判断节点覆盖区域是否与指定区域有交叉，若没有就可以简化
    if (split)//Trange对应覆盖的y范围
    {
        if (!ry.CrossR(Trange))
            return;
    }
    else//x
    {
        if (!rx.CrossR(Trange))
            return;
    }
    //判断节点覆盖区域是否被包含
    if (split)
    {
        if (ry.IncludeR(Trange))
        {
            y_ok = true;
        }
    }
    else
    {
        if (rx.IncludeR(Trange))
        {
            x_ok = true;
        }
    }
    if (x_ok && y_ok)
    {
        count += num;
        return;
    }
    //判断节点本身在不在区域内
    if (rx.IncludeP(*data, true) && ry.IncludeP(*data, false))
    {
        count++;
    }
    if (rc != NULL)
    {
        rc->find(rx, ry, count, x_ok, y_ok);
    }
    if (lc != NULL)
    {
        lc->find(rx, ry, count, x_ok, y_ok);
    }
}

int main()
{
    int n, m, x, y, ylow, yhigh;
    cin >> n >> m;
    Point *fulldata = new Point[n];
    cin >> x >> y;
    ylow = yhigh = y;
    fulldata[0].set(0, x, y);
    for (int i = 1; i < n; i++)
    {
        scanf("%d %d", &x, &y);
        if (y < ylow)
            ylow = y;
        if (y > yhigh)
            yhigh = y;
        fulldata[i].set(i, x, y);
    }
    kdt a(fulldata, n, NULL, true, ylow, yhigh);//构造树，默认第一次分割x
    int d, Count = 0;
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &x, &y, &d);
        Range rx(x - d, x + d), ry(y - d, y + d);
        a.find(rx, ry, Count, false, false);
        printf("%d\n", Count);
        Count = 0;
    }
}
