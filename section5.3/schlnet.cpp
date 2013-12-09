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

// DFN顺带记录当前节点有没有被访问过
int DFN[101]; int step; // 时间戳
int LOW[101]; // 这颗树的最小时间戳
bool instack[101]; // 记录该元素是否在栈中
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

    // 说明找到一个连通图
    if (LOW[u] == DFN[u]) {
        // 把同一个连通图都染成同一个颜色
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
            // i节点的所有邻接节点
            links[i][++links[i][0]] = to;
            // 记录某两个节点是否是有向连接关系
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
            // 属于两个连通图，且是i指向j
            if (Belong[i] != Belong[j] && con[i][j])
                // j的入度+1
                ind[Belong[j]] ++;
    int A=0;
    // 则入度为0的顶点就是最少要接受新软件副本的学校
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
    // 可以知道，"存在一个顶点入度为0或者出度为0"与"该图一定
    // 不是强连通的"是等价的命题。为了使添加的边最少，则应该
    // 把入度为0顶点和出度为0的顶点每个顶点添加1条边，使图中
    // 不存在入度为0顶点和出度为0的顶点。

    // 当入度为0的顶点多于出度为0的顶点，则应添加的边数应为入
    // 度为0的顶点的个数。当出度为0的顶点多于出入度为0的顶点，则
    // 应添加的边数应为出度为0的顶点的个数。 
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
        // 取入度数和出度数最大的那一个
        ofile << max(innum, outnum) << endl;

    return 0;
}