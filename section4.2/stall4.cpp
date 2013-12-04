/*
ID: lyyyuna
PROG: stall4
LANG: C++
*/

/*
bool 寻找从k出发的对应项出的可增广路
{
    while (从邻接表中列举k能关联到顶点j)
    {
        if (j不在增广路上)
        {
            把j加入增广路;
            if (j是未盖点 或者 从j的对应项出发有可增广路)
            {
                修改j的对应项为k;
                则从k的对应项出有可增广路,返回true;
            }
        }
    }
    则从k的对应项出没有可增广路,返回false;
}

void 匈牙利hungary()
{
    for i->1 to n
    {
        if (则从i的对应项出有可增广路)
            匹配数++;
    }
    输出 匹配数;
}
*/

#include <fstream>
#include <cstring>

using namespace::std;

const int MAXN = 201;
int con[MAXN][MAXN];
bool isFind[MAXN];
int match[MAXN];
int N, M;
int result;

bool dfs_crosspath(int cow)
{
    for (int i = 1; i <= con[cow][0]; ++i) {
        int stall = con[cow][i];
        // 判断j是否被搜过（即是否在增广路上或是否永远不可能在增广路上） 
        if (!isFind[stall]) {
             // 标记被搜过 （即在增广路上或永远不可能在增广路上）
            isFind[stall] = true;
            if (!match[stall] || dfs_crosspath(match[stall])) {
                // match[j]表示他所配对的奶牛
                match[stall] = cow;
                return true;
            }
        }
    }
    return false;
}

void hungary(void)
{
    memset(isFind, 0, sizeof(isFind));
    for (int i = 1; i <= N; ++i) {
         // dfs(i)表示以i为一个端点的增广路是否存在 
        if (dfs_crosspath(i))
            result ++;
        memset(isFind, 0, sizeof(isFind));
    }
}

int main(void)
{
    ifstream ifile("stall4.in");
    ofstream ofile("stall4.out");

    ifile >> N >> M;
    for (int i = 1; i <= N; ++i) {
        ifile >> con[i][0];
        for (int j = 1; j <= con[i][0]; ++j)
            ifile >> con[i][j];
    }

    hungary();

    ofile << result << endl;
}