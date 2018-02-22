#include "stdio.h"
using namespace std;

bool *visited, pathFlag = false;
char **rawMat;
int L;

struct Stack
{
    int Max, top;
    short *elems;
    Stack(int m): Max(m)
    {
        elems = new short[m];
        top = -1;
    }
    void push(short elem)
    {
        elems[++top] = elem;
    }
    void pop()
    {
        top--;
    }
    void Print()
    {
        for (int i = 0; i<=top; i++)
        {
            printf("%hd ", elems[i]);
        }
        printf("\n");
    }
};
Stack *path;

void inputMat()//input mat v2, tri
{
    short temp;
    for (int i = 0; i < L; i++)
    {
        rawMat[i] = new char[i + 1];
        visited[i] = false;
        {
            for (int j = 0; j <= i; j++)
            {
                scanf("%hd", &temp);
                rawMat[i][j] = char(temp);
            }
            for (int j = i + 1; j < L; j++)
            {
                scanf("%hd", &temp);
            }
        }
    }
}

short vecMultiply(int i, int j)
{
    short cnt = 0;
    if (i > j)//let i < j
    {
        int temp;
        temp = i;
        i = j;
        j = temp;
    }
    for (int m = 0; m <= i; m++)
    {
        cnt += rawMat[i][m] & rawMat[j][m];
    }
    for (int m = i + 1; m <= j; m++)
    {
        cnt += rawMat[m][i] & rawMat[j][m];
    }
    for (int m = j + 1; m < L; m++)
    {
        cnt += rawMat[m][i] & rawMat[m][j];
    }
    return cnt;
}

void recomMat()//verson2, triangle
{
    char **tri = new char*[L], temp;
    for (int i = 0; i < L; i++)
    {
        tri[i] = new char[i + 1];
        for (int j = 0; j <= i; j++)
        {
            if (rawMat[i][j] || i == j)
            {
                tri[i][j] = 0;
            }
            else
            {
                temp = vecMultiply(i, j);
                if (temp < 3)
                {
                    tri[i][j] = 0;
                }
                else
                {
                    tri[i][j] = 1;
                }
            }
            
        }
    }
        //Print
        for (int i = 0; i < L; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                printf("%d ", tri[i][j]);
            }
            for (int j = i + 1; j < L; j++)
            {
                printf("%d ", tri[j][i]);
            }
            printf("\n");
        }
}

int nextAdj(int v, int c)
{
    for (int i = c + 1; i < L; i++)
    {
        if (i <= v)
        {
            if (rawMat[v][i] == 1)
            {
                return i;
            }
        }
        else{
            if (rawMat[i][v] == 1)
            {
                return i;
            }
        }
    }
    return -2;
}
void findPath(int s, int e)
{
    path->push(s);
    if (s == e)
    {
        pathFlag = true;
        return;
    }
    visited[s] = true;
    for (int t = -1; t != -2;)
    {
        t = nextAdj(s, t);
        if (t == -2)
        {
            path->pop();
            break;
        }
        if (!visited[t])
        {
            findPath(t, e);
            if (pathFlag)
                return;
        }
    }
}

int main() {
    int s, e;
    scanf("%d", &L);
    visited = new bool[L];
    rawMat = new char*[L];
    inputMat();
    scanf("%d %d", &s, &e);
    recomMat();
    path = new Stack(L);
    findPath(s, e);
    if (pathFlag)
        path->Print();
    else
        printf("-1\n");
    return 0;
}
