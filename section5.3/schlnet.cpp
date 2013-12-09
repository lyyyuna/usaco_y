/*
ID: lyyyuna
PROG: schlnet
LANG: C++
*/

#include <fstream>
#include <cstring>
#include <iomanip>

using namespace::std;

int links[101][101];
bool con[101][101];

// DFN˳����¼��ǰ�ڵ���û�б����ʹ�
int DFN[101]; int step; // ʱ���
int LOW[101]; // ���������Сʱ���
bool instack[101]; // ��¼��Ԫ���Ƿ���ջ��
int stack[101]; int sp;

int Bcnt;
int Belong[101];

// http://www.lyyyuna.com/?p=29
// 
void Tarjan(int u)
{
    LOW[u] = DFN[u] = ++step;
    instack[u] = true;
    stack[++sp] = u;

    for (int i = 1; i <= links[u][0]; ++i) {
        int v = links[u][i];
        if (!DFN[v]) {
            Tarjan(v);
            LOW[u] = min(LOW[u], LOW[v]);
        }
        else {
            if (instack[v])
                LOW[u] = min(LOW[u], DFN[v]);
        }
    }

    // ˵���ҵ�һ����ͨͼ
    if (LOW[u] == DFN[u]) {
        // ��ͬһ����ͨͼ��Ⱦ��ͬһ����ɫ
        Bcnt ++;
        int vv;
        do {
            vv = stack[sp--];
            Belong[vv] = Bcnt;
            instack[vv] = false;
        } while (u != vv);
    }
}

int main(void)
{
    ifstream ifile("schlnet.in");
    ofstream ofile("schlnet.out");
    int N;
    ifile >> N;
    for (int i = 1; i <= N; ++i) {
        int to;
        ifile >> to;
        while (to) {
            // i�ڵ�������ڽӽڵ�
            links[i][++links[i][0]] = to;
            // ��¼ĳ�����ڵ��Ƿ����������ӹ�ϵ
            con[i][to] = true;
            ifile >> to;
        }
    }

    for (int i = 1; i <= N; ++i)
        if (!DFN[i])
            Tarjan(i);

    int ind[101];
    int outd[101];
    memset(ind, 0, sizeof(ind));
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            // ����������ͨͼ������iָ��j
            if (Belong[i] != Belong[j] && con[i][j])
                // j�����+1
                ind[Belong[j]] ++;
    int A=0;
    // �����Ϊ0�Ķ����������Ҫ���������������ѧУ
    for (int i = 1; i <= Bcnt; ++i)
        if (!ind[i])
            A++;
    ofile << A << endl;

    memset(ind, 0, sizeof(ind));
    memset(outd, 0, sizeof(ind));
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            if (Belong[i] != Belong[j] && con[i][j]) {
                ind[Belong[j]] ++;
                outd[Belong[i]] ++;
            }
    // ����֪����"����һ���������Ϊ0���߳���Ϊ0"��"��ͼһ��
    // ����ǿ��ͨ��"�ǵȼ۵����⡣Ϊ��ʹ��ӵı����٣���Ӧ��
    // �����Ϊ0����ͳ���Ϊ0�Ķ���ÿ���������1���ߣ�ʹͼ��
    // ���������Ϊ0����ͳ���Ϊ0�Ķ��㡣

    // �����Ϊ0�Ķ�����ڳ���Ϊ0�Ķ��㣬��Ӧ��ӵı���ӦΪ��
    // ��Ϊ0�Ķ���ĸ�����������Ϊ0�Ķ�����ڳ����Ϊ0�Ķ��㣬��
    // Ӧ��ӵı���ӦΪ����Ϊ0�Ķ���ĸ����� 
    int innum=0, outnum=0;
    for (int i = 1; i <= Bcnt; ++i) {
        if (!ind[i])
            innum ++;
        if (!outd[i])
            outnum ++;
    }

    if (Bcnt == 1)
        ofile << "0" << endl;
    else
        // ȡ������ͳ�����������һ��
        ofile << max(innum, outnum) << endl;

    return 0;
}