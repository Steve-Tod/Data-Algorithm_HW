#include "stdio.h"

int length = 0;

struct Stop
{
    int gold;
    Stop* next;
    Stop(int g)
    {
        gold = g;
        next = NULL;
    }
    void Add(int g)
    {
        next = new Stop(g);
    }
};

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}
int MaxSum(int *M_Stops)
{
    int **Maxin = new int*[2], **Maxmay = new int*[2];
    for (int i = 0; i < 2; i++)
    {
        Maxin[i] = new int[4];
        Maxmay[i] = new int[4];
        for (int j = 0; j < 4; j++)
        {
            Maxin[i][j] = -1e9;
            Maxmay[i][j] = -1e9;
        }
    }
    Maxin[0][0] = 0;
    Maxmay[0][0] = 0;
    for (int i = 1; i < length+1; i++)
    {
        Maxin[i%2][0] = 0;
        Maxmay[i%2][0] = 0;
        for (int j = 1; j < 4; j++)
        {
            Maxin[i%2][j] = max(Maxmay[(i-1)%2][j-1] + M_Stops[i-1], Maxin[(i-1)%2][j] + M_Stops[i-1]);
            Maxmay[i%2][j] = max(Maxin[i%2][j], Maxmay[(i-1)%2][j]);
        }
    }
    
    int m = Maxmay[length%2][3];
    return m;
}

int MinSum(int *M_Stops)
{
    int **Maxin = new int*[2], **Maxmay = new int*[2], Main_sum = M_Stops[0];
    for (int i = 0; i < 2; i++)
    {
        Maxin[i] = new int[4];
        Maxmay[i] = new int[4];
        for (int j = 0; j < 4; j++)
        {
            Maxin[i][j] = 1e9;
            Maxmay[i][j] = 1e9;
        }
    }
    Maxin[0][0] = 0;
    Maxmay[0][0] = 0;
    for (int i = 1; i < length+1; i++)
    {
        if (i < length)
        {
            Main_sum += M_Stops[i];
        }
        Maxin[i%2][0] = 0;
        Maxmay[i%2][0] = 0;
        for (int j = 1; j < 4; j++)
        {
            Maxin[i%2][j] = min(Maxmay[(i-1)%2][j-1] + M_Stops[i-1], Maxin[(i-1)%2][j] + M_Stops[i-1]);
            Maxmay[i%2][j] = min(Maxin[i%2][j], Maxmay[(i-1)%2][j]);
        }
    }
    int m = Main_sum - Maxmay[length%2][3];
    return m;
}

int main() {
    int n, g_temp;
    short IsPos = -1;
    scanf("%d", &n);
    scanf("%d", &g_temp);
    Stop *head = new Stop(g_temp), *current = head;
    IsPos = (g_temp > 0);
    for (int i = 1; i < n; i++)
    {
        scanf("%d", &g_temp);
        if (IsPos == (g_temp > 0))
        {
            current->gold += g_temp;
        }
        else
        {
            current->Add(g_temp);
            IsPos = !IsPos;
            current = current->next;
        }
    }
    if ((head->gold > 0) == (current->gold > 0) && head != current)
    {
        head->gold += current->gold;
        current->gold = 0;
        //
    }
    for (Stop *j = head; j != NULL; j = j->next)
    {
        if (j->gold != 0)
        {
            length++;
        }
    }
    int *Mod_Stops = new int[length], cnt = 0;
    for (Stop *j = head; j != NULL; j = j->next)
    {
        if (j->gold != 0)
        {
            Mod_Stops[cnt++] = j->gold;
        }
    }
    if (current == head)
    {
        Mod_Stops[0] = head->gold;
    }
    Stop *D;
    for (Stop *j = head; j != NULL; )
    {
        D = j;
        j = j->next;
        delete D;
    }
    int m1 = MaxSum(Mod_Stops);
    int m2 = MinSum(Mod_Stops);
    printf("%d", max(m1, m2));
    return 0;
}
