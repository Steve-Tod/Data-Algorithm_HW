#include <stdio.h>
#include <memory.h>
#include "math.h"

bool shoulian = true;
class Node
{
public:
    int x, y;
    double val;
    Node *next_v, *next_h;
    Node(int x0, int y0, double n, Node* v = NULL, Node* h = NULL): x(x0), y(y0), val(n), next_v(v), next_h(h) {}
};


class Matrix
{
public:
    int num;
    Node **heads_v, **heads_h;
    Matrix(int n): num(n)
    {
        heads_v = new Node*[n];
        heads_h = new Node*[n];
        for (int i = 0; i < n; i++)//确保每个表头节点都初始化为NULL，方便后面检验
        {
            heads_h[i] = NULL;
            heads_v[i] = NULL;
        }
    }
    ~Matrix()
    {
        delete [] heads_v;
        delete [] heads_h;
    }
    void NodeIn(Node &NewNode);
    void GSIter1(const double *b, double *x);
    void GSIter(double *b, double *x);
    bool Val(const double *b, const double *x);
};

void Matrix::NodeIn(Node &NewNode)
{
    int x = NewNode.x, y = NewNode.y;
    //横向插入
    if (heads_h[x] == NULL)//无表头就把新节点作为表头
    {
        heads_h[x] = &NewNode;
    }
    else
    {
        //横向插入
        if (heads_h[x]->y > y)//原x向头指针在新节点右边
        {
            Node *temp = heads_h[x];
            heads_h[x] = &NewNode;
            NewNode.next_h = temp;
        }
        else//遍历插入
        {
            bool flag = false;
            Node *i;
            for (i = heads_h[x]; i->next_h != NULL; i = i->next_h)
            {
                if (i->y < y && i->next_h->y > y)
                {
                    Node* temp = i->next_h;
                    i->next_h = &NewNode;
                    NewNode.next_h = temp;
                    flag = true;
                    break;
                }
            }
            if (!flag)//之前未曾插入说明是最后一个点
            {
                i->next_h = &NewNode;
            }
        }
    }
    //纵向插入
    if (heads_v[y] == NULL)
    {
        heads_v[y] = &NewNode;
    }
    else
    {
        //纵向插入
        if (heads_v[y]->x > x)//原y向头指针在新节点下方
        {
            Node *temp =heads_v[y];
            heads_v[y] = &NewNode;
            NewNode.next_v = temp;
        }
        else//遍历插入
        {
            bool flag = false;
            Node *i;
            for (i = heads_v[y]; i->next_v != NULL; i = i->next_v)
            {
                if (i->x < x && i->next_v->x > x)
                {
                    Node *temp = i->next_v;
                    i->next_v = &NewNode;
                    NewNode.next_v = temp;
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                i->next_v = &NewNode;
            }
        }
    }
}

void Matrix::GSIter1(const double *b, double *x)//Directly
{
    for (int i = 0; i < num; i++)
    {
        x[i] = b[i];
        double midVal = 0;
        for (Node *j = heads_h[i]; j != NULL; j = j->next_h)
        {
            if (j->y == i)
            {
                midVal = j->val;
            }
            else
            {
                x[i] -= j->val * x[j->y];
            }
        }
        if (midVal == 0)
        {
            printf("Mid = 0\n");
        }
        x[i] /= midVal;//可能除0错？
    }
}

bool Matrix::Val(const double *b, const double *x)
{
    double Res = 0;
    for (int i = 0; i < num; i++)
    {
        double sum = 0;
        for (Node* j = heads_h[i]; j != NULL; j = j->next_h)
        {
            sum += j->val * x[j->y];
        }
        sum -= b[i];
        Res += sum * sum;
    }
    if (Res < 0.01)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Matrix::GSIter(double *b, double *x)
{
    int max = 11;//Max iters
    int i;
    for (i = 0; i < max; i++)
    {
        GSIter1(b, x);
        if (Val(b, x))
        {
            break;
        }
    }
    if (i == max)
        shoulian = false;
    else
        shoulian = true;
}

inline int selectPivot(double **a, int col, int n)
{
    double max = 0, val;
    int k = n - 1;
    for (int i = n - 1; i >= col; i--)
    {
        val = fabs(a[i][col]);
        if (max < val)
        {
            max = val;
            k = i;
        }
    }
    return k;
}
void Gauss(const Matrix &mat, double *b, double *x)
{
    int n = mat.num;
    double **a = new double*[n];
    //Initialize
    for (int i = 0; i < n; i++)
    {
        a[i] = new double[n];
        for (int j = 0; j < n; j++)
        {
            a[i][j] = 0;
        }
        for (Node* j = mat.heads_h[i]; j != NULL; j = j->next_h)
        {
            a[i][j->y] = j->val;
        }
    }
    //消去
    for (int i = 0; i < n; i++)
    {
        
        //选主元
        int k = selectPivot(a, i, n);
        if (k != i)
        {
            double *temp = a[i];
            a[i] = a[k];
            a[k] = temp;
            double v_temp = b[i];
            b[i] = b[k];
            b[k] = v_temp;
        }
        /*
        for (int m = 0; m < n; m++)
        {
            for (int g = 0; g < n; g++) {
                printf("%lf ", a[m][g]);
            }
            printf("\n");
        }
        printf("\n");
        */
        for (k = i + 1; k < n; k++)
        {
            double s = -a[k][i] / a[i][i];
            for(int j = i + 1; j < n; j++)
            {
                a[k][j] += s*a[i][j];
            }
            a[k][i] = 0;
            b[k] += s * b[i];
        }
    }
    //回带
    for (int i = n - 1; i >= 0; i--)
    {
        double s =b[i];
        for(int k = i + 1; k < n; k++)
        {
            s -= a[i][k]*x[k];
        }
        x[i] = s/a[i][i];
    }
}

int main() {
    //Input
    int m, k, xt, yt;
    scanf("%d %d", &m, &k);
    Matrix mat(m);
    double vt;
    Node *temp;
    for (int i = 0; i < k; i++)
    {
        scanf("%d %d %lf", &xt, &yt, &vt);
        temp = new Node(xt, yt, vt);
        mat.NodeIn(*temp);
    }
    double *b = new double[m], *x = new double[m];
    for (int i = 0; i < m; i++)
    {
        scanf("%lf", b + i);
        x[i] = 0;
    }
    mat.GSIter(b, x);
    if (!shoulian)
    {
        Gauss(mat, b, x);
    }
    for (int i = 0; i < m; i++)
    {
        printf("%lf\n", x[i]);
    }
    return 0;
}
