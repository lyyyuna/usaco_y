/*
ID: lyyyuna
PROG: ditch
LANG: C++
*/

#include <fstream>
#include <cstring>
#include <queue>

using namespace::std;

int startP;
int endP;
int con[200+1][200+1];  // 记录两个点之间边的容量
int prePoint[200+1];    // 记录该点的前驱节点是哪个
int flow[200+1];        // 单个节点最大流

int bfs(void)
{
    queue <int> Q;
    while (!Q.empty())
        Q.pop();
    Q.push(startP);
    memset(prePoint, -1, sizeof(prePoint));
    // 起点的前驱计为0
    prePoint[startP] = 0;
    // 
    flow[startP] = 3290409;
    while (!Q.empty()) {
        int curP = Q.front();
        Q.pop();
        // 搜索到终点
        if (curP == endP)
            break;
        for (int i = 1; i <= endP; ++i) {
            // 如果这个点没找到过，而且有边连着
            if (prePoint[i] == -1 && con[curP][i]!=0) {
                // 连起来
                prePoint[i] = curP;
                flow[i] = min(flow[curP], con[curP][i]);
                Q.push(i);
            }
        }
    }
    // 表明终点没有线连着
    if (prePoint[endP] == -1)
        return -1;
    return flow[endP];
}

int Edmonds_Karp(void)
{
    int max_flow = 0;
    int Cf;
    while ((Cf = bfs()) != -1) {
        // 从终点开始
        int curP = endP;
        // 到起点为止
        while (curP != startP) {
            // 从后往前找
            int preP = prePoint[curP];
            // 正向减
            con[preP][curP] -= Cf;
            // 反向加
            con[curP][preP] += Cf;
            curP = preP;
        }
        max_flow += Cf;
    }
    return max_flow;
}

int main(void)
{
    ifstream ifile("ditch.in");
    ofstream ofile("ditch.out");
    int N, M;
    ifile >> N >> M;
    endP = M;
    for (int i = 0; i < N; ++i) {
        int Si, Ei, Ci;
        ifile >> Si >> Ei >> Ci;
        con[Si][Ei] += Ci;
    }

    startP = 1;
    int result = Edmonds_Karp();
    ofile << result << endl;

    return 0;
}