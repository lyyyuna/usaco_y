/*
ID: lyyyuna
PROG: ttwo
LANG: C++
*/

#include <fstream>

using namespace::std;

ifstream ifile("ttwo.in");
ofstream ofile("ttwo.out");
char graph[11][11];
int Fx, Fy; // farmer当前位置
int Cx, Cy; // cow当前位置
int times;  // 总的时间数

int Fstep = 0;  // 各自走的步数
int Cstep = 0;

bool isOut(int x, int y)
{
    return (x<0 || y<0 || x>=10 || y>=10);
}

void simulation()
{

    int dx[] = {-1, 0, 1, 0};   // 控制方向
    int dy[] = {0, 1, 0, -1};   // 一开始正好朝北
    int Fx_n, Fy_n;     // 下一步可能到的位置，不管障碍
    int Cx_n, Cy_n;
    int Fdir = 0;       // 方向
    int Cdir = 0;

    while (Fstep <= 400 && Cstep <= 400) {
        // 相遇
        if (Fx == Cx && Fy == Cy)
            break;
        // farmer
        // 先算出下一个可能的位置
        Fx_n = Fx + dx[Fdir];
        Fy_n = Fy + dy[Fdir];
        // 再判断是否出界或者有障碍
        if (!isOut(Fx_n, Fy_n) && graph[Fx_n][Fy_n]!='*') {
            Fx = Fx_n;
            Fy = Fy_n;
            Fstep ++;
        }
        // 有则转向
        else
            Fdir = (Fdir+1)%4;
        
        // 同理
        Cx_n = Cx + dx[Cdir];
        Cy_n = Cy + dy[Cdir];
        if (!isOut(Cx_n, Cy_n) && graph[Cx_n][Cy_n]!='*') {
            Cx = Cx_n;
            Cy = Cy_n;
            Cstep ++;
        }
        else
            Cdir = (Cdir+1)%4;

        times ++;
    }
}

int main(void)
{
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j) {
            ifile >> graph[i][j];
            // 记下cow的位置，并还原成 .
            if (graph[i][j] == 'C') {
                Cx = i;
                Cy = j;
                graph[i][j] = '.';
            }
            // 记下farmer的位置，并还原成 .
            if (graph[i][j] == 'F') {
                Fx = i;
                Fy = j;
                graph[i][j] = '.';
            }
        }
    // 按照题目意思进行模拟
    simulation();
    // 如果有一方 超过400步，说明不相遇
    if (Fstep <= 400 && Cstep <= 400)
        ofile << times << endl;
    else
        ofile << 0 << endl;

    return 0;
}