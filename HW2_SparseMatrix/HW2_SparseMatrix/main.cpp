#include <stdio.h>
using namespace std;

class Node
{
public:
    int x, y, val;
    Node *next_v, *next_h;
    Node(int x0, int y0, int n, Node* v = NULL, Node* h = NULL): x(x0), y(y0), val(n), next_v(v), next_h(h) {}
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
    void PrintT();
    void SumT();
    void MultiplyT();
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

void Matrix::PrintT()//打印转置，一次打印v向链表即可
{
    for (int i = 0; i < num; i++)
    {
        if (heads_v[i] != NULL)
        {
            Node *N;
            for (N = heads_v[i]; N != NULL; N = N->next_v)
            {
                if (N->val != 0)
                    printf("%d %d %d\n", N->y, N->x, N->val);
            }
        }
    }
}

void Matrix::SumT()
{
    for (int n = 0; n < num; n++)//一行一行来
    {
        if (heads_v[n] == NULL)//转置矩阵该行未设定任何元素
        {
            if (heads_h[n] != NULL)//原矩阵该行有元素则直接打印原矩阵该行
            {
                Node *N;
                for (N = heads_h[n]; N != NULL; N = N->next_h)
                {
                    if (N->val != 0)
                        printf("%d %d %d\n", n, N->y, N->val);
                }
            }
        }
        else if (heads_h[n] == NULL)//原矩阵该行未设定任何元素
        {
            if (heads_v[n] != NULL)//转置矩阵该行有元素则直接打印转置矩阵该行
            {
                Node *N;
                for (N = heads_v[n]; N != NULL; N = N->next_v)
                {
                    if (N->val != 0)
                        printf("%d %d %d\n", n, N->x, N->val);
                }
            }
        }
        else//两矩阵都有元素
        {
            Node *h_c = heads_h[n], *v_c = heads_v[n];//双指针同时向后遍历
            while (true)
            {
                if (h_c->y == v_c->x)//指针对应元素位置相同则相加，输出，指针向后走一个
                {
                    int sum = h_c->val + v_c->val;
                    if (sum)
                        printf("%d %d %d\n", n, h_c->y, sum);
                    h_c = h_c->next_h;
                    v_c = v_c->next_v;
                }
                else if (h_c->y < v_c->x)//不同则输出位置靠前的那个，对应指针向后走一个
                {
                    if (h_c->val)
                        printf("%d %d %d\n", n, h_c->y, h_c->val);
                    h_c = h_c->next_h;
                }
                else//同理
                {
                    if (v_c->val)
                        printf("%d %d %d\n", n, v_c->x, v_c->val);
                    v_c = v_c->next_v;
                }
                //处理某行达到末尾的情况
                if (h_c == NULL && v_c == NULL)//均达到末尾则结束
                    break;
                else if (h_c == NULL && v_c != NULL)//一行达到末尾则输出另一行剩下元素
                {
                    for (Node *N = v_c; N != NULL; N = N->next_v)
                    {
                        if (N->val)
                            printf("%d %d %d\n", n, N->x, N->val);
                    }
                    break;
                }
                else if (h_c != NULL && v_c == NULL)//同理
                {
                    for (Node *N = h_c; N != NULL; N = N->next_h)
                    {
                        if (N->val)
                            printf("%d %d %d\n", n, N->y, N->val);
                    }
                    break;
                }
            }
        }
    }
}

void Matrix::MultiplyT()
{
    //一个元素一个元素求
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            if (heads_h[i] != NULL && heads_h[j] != NULL)//双指针同时遍历，原理与加法相似
            {
                int sum = 0;
                Node *x_c = heads_h[i], *y_c = heads_h[j];
                while (true)
                {
                    if (x_c->y == y_c->y)
                    {
                        sum += x_c->val * y_c->val;
                        x_c = x_c->next_h;
                        y_c = y_c->next_h;
                    }
                    else if (x_c->y > y_c->y)
                    {
                        y_c = y_c->next_h;
                    }
                    else
                    {
                        x_c = x_c->next_h;
                    }
                    if (x_c == NULL || y_c == NULL)
                    {
                        break;
                    }
                }
                if (sum)
                    printf("%d %d %d\n", i, j, sum);
            }
        }
    }
}
int main() {
    int m, n, l, i, j, v;
    scanf("%d %d %d", &m, &n, &l);
    Matrix Mat(m);
    for (int k = 0; k < l; k++)
    {
        scanf("%d %d %d", &i, &j, &v);
        Node *temp = new Node(i, j, v);
        Mat.NodeIn(*temp);
    }
    Mat.PrintT();
    Mat.SumT();
    Mat.MultiplyT();
    return 0;
}
