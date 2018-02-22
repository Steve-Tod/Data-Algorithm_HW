#include "stdio.h"
#include <vector>
#include <iostream>
#include <map>
#include <string>
using namespace std;

char getOppo(char c)
{
    char Res;
    switch (c) {
        case 0: Res = 5;break;
        case 1: Res = 3;break;
        case 2: Res = 4;break;
        case 3: Res = 1;break;
        case 4: Res = 2;break;
        case 5: Res = 0;break;
        default: Res = -1;break;
    }
    return Res;
}


class Phase {
public:
    vector<char> Condi;
    int before;
    string ForeAct;
    Phase() {before = NULL;}
    //Phase(Phase &p): Condi(p.Condi) {}
    //~Phase() {};
    void Init()
    {
        int temp;
        for (int i = 0; i < 24; i++)
        {
            scanf("%d", &temp);
            Condi.push_back((char)temp);
        }
    }
    void ZInit()
    {
        for (int i = 0; i < 24; i++)
        {
            Condi.push_back(-1);
        }
    }
    void CInit(const vector<char> &a)
    {
        for (int i = 0; i < 24; i++)
        {
            Condi.push_back(a[i]);
        }
    }
    Phase F();
    Phase Fanti();
    Phase F2();
    Phase R();
    Phase Ranti();
    Phase R2();
    Phase U();
    Phase Uanti();
    Phase U2();
    Phase Act(int i)
    {
        i += 1;
        switch(i)
        {
            case 1: return F(); break;
            case 2: return Fanti(); break;
            case 3: return F2(); break;
            case 4: return R(); break;
            case 5: return Ranti(); break;
            case 6: return R2(); break;
            case 7: return U(); break;
            case 8: return Uanti(); break;
            case 9: return U2(); break;
            default: return *this; break;
        }
    }
    Phase getTarget();
    bool Same(Phase &b)
    {
        return Condi == b.Condi;
    }
    void Print()
    {
        printf("    %d %d\n    %d %d\n", Condi[0], Condi[1], Condi[2], Condi[3]);
        for (int i = 4; i < 20; i++)
        {
            printf("%d ", Condi[i]);
            if (i == 11 || i == 19)
                printf("\n");
        }
        printf("    %d %d\n    %d %d\n", Condi[20], Condi[21], Condi[22], Condi[23]);
    }
    
};

Phase Phase::getTarget()
{
    //12 19 22
    Phase Res;
    Res.ZInit();
    Res.Condi[4] = Res.Condi[5] = Res.Condi[12] = Res.Condi[13] = Condi[12];
    Res.Condi[10] = Res.Condi[11] = Res.Condi[18] = Res.Condi[19] = Condi[19];
    Res.Condi[20] = Res.Condi[21] = Res.Condi[22] = Res.Condi[23] = Condi[22];
    Res.Condi[8] = Res.Condi[9] = Res.Condi[16] = Res.Condi[17] = getOppo(Condi[12]);
    Res.Condi[6] = Res.Condi[7] = Res.Condi[14] = Res.Condi[15] = getOppo(Condi[19]);
    Res.Condi[0] = Res.Condi[1] = Res.Condi[2] = Res.Condi[3] = getOppo(Condi[22]);
    return Res;
}

Phase Phase::F()
{
    Phase Res;
    Res.CInit(Condi);
    Res.Condi[2] = Condi[13]; Res.Condi[3] = Condi[5]; Res.Condi[8] = Condi[2]; Res.Condi[16] = Condi[3];
    Res.Condi[21] = Condi[8]; Res.Condi[20] = Condi[16]; Res.Condi[13] = Condi[21]; Res.Condi[5] = Condi[20];
    Res.Condi[7] = Condi[6]; Res.Condi[15] = Condi[7]; Res.Condi[14] = Condi[15]; Res.Condi[6] = Condi[14];
    return Res;
}

Phase Phase::Fanti()
{
    Phase Res;
    Res.CInit(Condi);
    Res.Condi[13] = Condi[2]; Res.Condi[5] = Condi[3]; Res.Condi[2] = Condi[8]; Res.Condi[3] = Condi[16];
    Res.Condi[8] = Condi[21]; Res.Condi[16] = Condi[20]; Res.Condi[21] = Condi[13]; Res.Condi[20] = Condi[5];
    Res.Condi[6] = Condi[7]; Res.Condi[7] = Condi[15]; Res.Condi[15] = Condi[14]; Res.Condi[14] = Condi[6];
    return Res;
}

Phase Phase::F2()
{
    Phase Res = F();
    Res = Res.F();
    return Res;
}

Phase Phase::R()
{
    Phase Res;
    Res.CInit(Condi);
    Res.Condi[7] = Condi[21]; Res.Condi[15] = Condi[23]; Res.Condi[1] = Condi[7]; Res.Condi[3] = Condi[15];
    Res.Condi[18] = Condi[1]; Res.Condi[10] = Condi[3]; Res.Condi[21] = Condi[18]; Res.Condi[23] = Condi[10];
    Res.Condi[9] = Condi[8]; Res.Condi[17] = Condi[9]; Res.Condi[16] = Condi[17]; Res.Condi[8] = Condi[16];
    return Res;
}

Phase Phase::Ranti()
{
    Phase Res;
    Res.CInit(Condi);
    Res.Condi[21] = Condi[7]; Res.Condi[23] = Condi[15]; Res.Condi[7] = Condi[1]; Res.Condi[15] = Condi[3];
    Res.Condi[1] = Condi[18]; Res.Condi[3] = Condi[10]; Res.Condi[18] = Condi[21]; Res.Condi[10] = Condi[23];
    Res.Condi[8] = Condi[9]; Res.Condi[9] = Condi[17]; Res.Condi[17] = Condi[16]; Res.Condi[16] = Condi[8];
    return Res;
}

Phase Phase::R2()
{
    Phase Res = R();
    Res = Res.R();
    return Res;
}

Phase Phase::U()
{
    Phase Res;
    Res.CInit(Condi);
    Res.Condi[4] = Condi[6]; Res.Condi[5] = Condi[7]; Res.Condi[6] = Condi[8]; Res.Condi[7] = Condi[9];
    Res.Condi[8] = Condi[10]; Res.Condi[9] = Condi[11]; Res.Condi[10] = Condi[4]; Res.Condi[11] = Condi[5];
    Res.Condi[1] = Condi[0]; Res.Condi[3] = Condi[1]; Res.Condi[2] = Condi[3]; Res.Condi[0] = Condi[2];
    return Res;
}

Phase Phase::Uanti()
{
    Phase Res;
    Res.CInit(Condi);
    Res.Condi[6] = Condi[4]; Res.Condi[7] = Condi[5]; Res.Condi[8] = Condi[6]; Res.Condi[9] = Condi[7];
    Res.Condi[10] = Condi[8]; Res.Condi[11] = Condi[9]; Res.Condi[4] = Condi[10]; Res.Condi[5] = Condi[11];
    Res.Condi[0] = Condi[1]; Res.Condi[1] = Condi[3]; Res.Condi[3] = Condi[2]; Res.Condi[2] = Condi[0];
    return Res;
}

Phase Phase::U2()
{
    Phase Res = U();
    Res = Res.U();
    return Res;
}


vector<Phase> forV, backV;
short AnotherSide = -1;
Phase *Side = NULL;
char forAct[9][3] = {"F+", "F-", "F2", "R+", "R-", "R2", "U+", "U-", "U2"};
char backAct[9][3] = {"F-", "F+", "F2", "R-", "R+", "R2", "U-", "U+", "U2"};

int find_i(Phase& x, vector<Phase> &V)
{
    for (int i = 0; i < (int)V.size(); i++)
    {
        if (x.Same(V[i]))
            return i;
    }
    return -1;
}

void Back(int *middle, Phase &start, Phase &target)
{
    string Res;
    int next, cnt = 0;
    if(middle[0] == -1)
    {
        //back = start
        next = find_i(backV[middle[1]], forV);
        while (!forV[next].Same(start))
        {
            Res = forV[next].ForeAct + '\n' + Res;
            next = forV[next].before;
            cnt++;
        }
        //bact to target
        next = middle[1];
        while (1)
        {
            Res += backV[next].ForeAct + '\n';
            next = backV[next].before;
            cnt++;
            if (backV[next].Same(target))
                break;
        }
    }
    else
    {
        next = middle[0];
        while (!forV[next].Same(start))
        {
            Res = forV[next].ForeAct + '\n' + Res;
            next = forV[next].before;
            cnt++;
        }
        next = find_i(forV[middle[0]], backV);
        while (1)
        {
            Res += backV[next].ForeAct + '\n';
            next = backV[next].before;
            cnt++;
            if (backV[next].Same(target))
                break;
        }
    }
    printf("%d\n%s", cnt, Res.data());
}

void BiBFS(Phase &start, Phase &target)
{
    map<vector<char>, char> Visited;
    bool solved = false, For = true;
    int middle[2] = {-1, -1}, head[2] = {0, 0}, tail[2] = {0, 0}, cnt1 = 1, cnt2 = 1;
    Visited.insert(pair<vector<char>, char>(start.Condi, 1));
    Visited.insert(pair<vector<char>, char>(target.Condi, 2));
    forV.push_back(start); tail[0]++;
    backV.push_back(target); tail[1]++;
    while (head[0] != tail[0] && head[1] != tail[1])
    {
        if (For)
        {
            int cnt1_temp = 0;
            for (int j = 0; j < cnt1; j++)
            {
                for (int i = 0; i < 9 ;i++)
                {
                    
                    if (Visited[forV[head[0]].Act(i).Condi] != 1)
                    {
                        cnt1_temp++;
                        forV.push_back(forV[head[0]].Act(i));
                        forV[tail[0]].before = head[0];
                        forV[tail[0]].ForeAct = forAct[i];
                        if (Visited[forV[tail[0]].Condi] == 2)
                        {
                            middle[0] = tail[0];
                            solved = true;
                            break;
                        }
                        else
                        {
                            Visited[forV[tail[0]].Condi] = 1;
                        }
                        tail[0]++;
                    }
                }
                head[0]++;
                if (solved)
                    break;
            }
            cnt1 = cnt1_temp;
            if (solved)
                break;
        }
        else
        {
            int cnt2_temp = 0;
            for (int j = 0; j < cnt2; j++)
            {
                for (int i = 0; i < 9 ;i++)
                {
                    if (Visited[backV[head[1]].Act(i).Condi] != 2)
                    {
                        cnt2_temp++;
                        backV.push_back(backV[head[1]].Act(i));
                        backV[tail[1]].before = head[1];
                        backV[tail[1]].ForeAct = backAct[i];
                        if (Visited[backV[tail[1]].Condi] == 1)
                        {
                            middle[1] = tail[1];
                            solved = true;
                            break;
                        }
                        else
                        {
                            Visited[backV[tail[1]].Condi] = 2;
                        }
                        tail[1]++;
                    }
                }
                head[1]++;
                if (solved)
                    break;
            }
            cnt2 = cnt2_temp;
            if (solved)
                break;
        }
        For = !For;
    }
    if (solved)
    {
        Back(middle, start, target);
    }
}



int main() {
    Phase start;
    start.Init();
    Phase target = start.getTarget();
    //start.Print();
    //target.Print();
    if (start.Same(target))
    {
        printf("0\n");
    }
    else
    {
        BiBFS(start, target);
    }
    return 0;
}
