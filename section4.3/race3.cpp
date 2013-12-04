/*
Id：lyyyuna
PROG: race3
LANG: C++
*/

#include <fstream>
#include <cstring>

using namespace::std;

bool path1[50+1][50+1]; // 记录原始两点之间联通情况
bool path2[50+1][50+1]; // 记录实际两点是否可以通过多点连起来

int isVisit[50+1];
int nump = -1;

// 路径不允许通过splitpoint，然后记录下各点访问状态
void dfs(int deep, int splitpoint)
{
    isVisit[deep] = true;
    for (int i = 0; i <= nump; ++i)
        if (i != splitpoint && path1[deep][i] && !isVisit[i])
            dfs(i, splitpoint);
}

int main(void)
{
    ifstream ifile("race3.in");
    ofstream ofile("race3.out");

    int point = 0;

    while (point != -1) {
        nump++;
        while (true) {
            ifile >> point;
            if (point < 0)
                break;
            path1[nump][point] = true;
        }
    }
    nump--;

    memcpy(path2, path1, sizeof(path2));

    for (int k = 0; k <= nump; ++k)
        for (int i = 0; i <= nump; ++i)
            for (int j = 0; j <= nump; ++j)
                if (path2[i][k] && path2[k][j])
                    path2[i][j] = true;

    
    int unavoid[50+1];
    int split[50+1];
    int a(0), b(0);
    // 以i为分割点，即路径不允许通过i
    // 除去0和终点
    for (int i = 1; i < nump; ++i) {
        memset(isVisit, 0, sizeof(isVisit));
        dfs(0, i);
        
        // 如果分割后，终点不可达，说明分割点是一个unavoidable
        if (!isVisit[nump]) {
            unavoid[a++] = i;
            bool flag = true;

            // 试图看看在path2中 unavoidable 的点 
            // 能够反向跑回[i][j]，则说明还有其他通路能往回走
            // 否则就为一个中间路口
            for (int j = 0; j < nump; ++j)
                if (isVisit[j] && path2[i][j]) {
                    flag = false;
                    break;
                }
            if (flag == true)
                split[b++] = i;
        }
    }

    ofile << a;
    for (int i = 0; i < a; ++i)
        ofile << " " << unavoid[i];
    ofile << endl;
    ofile << b;
    for (int i = 0; i < b; ++i)
        ofile << " " << split[i];
    ofile << endl;

    return 0;
}