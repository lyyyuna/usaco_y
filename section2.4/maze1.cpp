/*
ID: lyyyuna
PROG: maze1
LANG: C++
*/

#include <fstream>
#include <queue>
#include <memory.h>


using namespace::std;

const int MAXH = 101;
const int MAXW = 39;
char graph[MAXH+MAXH][MAXW+MAXW];   // 存储所有字符，包括围墙
bool maps[MAXH][MAXW];              // 只存储每个单元，看其是否被访问过
int dist[2][MAXH][MAXW];            // 存储每个点到出口的最小距离

int startx[2], starty[2];           // 存储出口的坐标位置
int dx[] = {-1, 1, 0, 0};           // 控制方向
int dy[] = {0, 0, -1, 1};           // 控制方向

struct Node
{
    int x;
    int y;
    int dist;
};


void bfs(int startx, int starty, int which_start)
{
    queue <Node> q;
    // c为当前单元，n为下一个与其相邻的单元
    Node c, n;
    c.x = startx;
    c.y = starty;
    c.dist = 1;

    dist[which_start][startx][starty] = 1;
    maps[startx][starty] = true;

    q.push(c);
    while (!q.empty()) {
        c = q.front();
        q.pop();

        // 一个单元往外共有四个可能的方向
        for (int k = 0; k < 4; ++k) {
            // 判断墙壁有无 c.x*2 + dx[k]
            if (graph[c.x*2 + dx[k]][c.y*2 + dy[k]] == ' ') {
                // 没有
                n.x = c.x + dx[k];
                n.y = c.y + dy[k];
                // 已被访问过
                if (maps[n.x][n.y])
                    continue;
                // 没有访问过
                maps[n.x][n.y] = true;
                n.dist = dist[which_start][n.x][n.y] = c.dist+1;
                q.push(n);
            }
        }
    }
}

int main(void)
{
    ifstream ifile("maze1.in");
    ofstream ofile("maze1.out");

    int W, H;
    ifile >> W >> H;
    int k(0);   // 原来标记是哪个起始点
    for (int i = 1; i <= 2*H+1; ++i) {
        // 必须用这个，若用 ofile<< ，则会读不入空格
        ifile.get();
        for (int j = 1; j <= 2*W+1; ++j) {
            graph[i][j] = ifile.get();
            if ((i == 1 || i == 2*H+1) && graph[i][j] == ' ') {
                if (i == 1) {
                    startx[k] = 1;
                    starty[k] = j/2;
                }
                else {
                    startx[k] = H;
                    starty[k] = j/2;
                }
                k++;
                graph[i][j] = '-';  // 其实哪个字符都无所谓，只要不是空格
            }
            if ((j == 1 || j == 2*W+1) && graph[i][j] == ' ') {
                if (j == 1) {
                    startx[k] = i/2;
                    starty[k] = 1;
                }
                else {
                    startx[k] = i/2;
                    starty[k] = W;
                }
                k++;
                graph[i][j] = '|';
            }
        }
    }
    // 第一个起始点
    bfs(startx[0], starty[0], 0);
    memset(maps, false, sizeof(maps));
    // 第二个起始点
    bfs(startx[1], starty[1], 1);

    int max_min(0), min_dist(0);
    // 所求得是所有最短路径中的 最差路径长度
    for (int i = 1; i <= H; ++i)
        for (int j = 1; j <= W; ++j) {
            min_dist = dist[0][i][j] < dist[1][i][j]?
                        dist[0][i][j] : dist[1][i][j];
            max_min = min_dist > max_min ? min_dist : max_min;
        }

    ofile << max_min << endl;

    return 0;
}