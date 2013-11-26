/*
ID: lyyyuna
PROG: camelot
LANG: C++
*/

#include <fstream>
// #include <queue>
#include <cstring>
#include <cstdio>

using namespace::std;

struct Chess
{
    int x;
    int y;
};
Chess king;
Chess queue[1000];
Chess knight[1000];

ifstream ifile("camelot.in");
ofstream ofile("camelot.out");

int Row, Col;
int N;  // 一共有多少个骑士
int dis[26+1][30+1][26+1][30+1];    // 记录距离，前两个为第一个点，后两个为第二个点
const int INFTY = 23232;

bool flag[26+1][30+1];  // 记录某一个点是否被访问过
int dir[9][2] = {{0,0},{-2,-1},{-2,1},{2,-1},{2,1},{1,2},{1,-2},{-1,2},{-1,-2}};
// 计算每一个点到（xx，yy）距离，
// 由于是bfs，算出来的肯定是最短距离
void BFS(int xx, int yy)
{
    memset(queue, 0, sizeof(queue));
    memset(flag, 0, sizeof(flag));
    dis[xx][yy][xx][yy] = 0;    // 自己到自己为0
    flag[xx][yy] = true;
    // 模拟队列
    int front = 0;  // 队列头
    int rear = 1;   // 队列尾
    queue[rear].x = xx;
    queue[rear].y = yy;
    int x, y;
    while(front < rear) {
        front ++;
        // 8个方向
        for (int i = 1; i <= 8; ++i) {
            // 算出下一个可能点
            x = queue[front].x + dir[i][0];
            y = queue[front].y + dir[i][1];
            // 超过边界
            if (x<1 || x>Col || y<1 || y>Row)
                continue;
            // 已被访问过
            if (flag[x][y] == true)
                continue;
            // 模拟插入队列
            rear ++;
            queue[rear].x = x;
            queue[rear].y = y;
            flag[x][y] = true;
            dis[xx][yy][x][y] = dis[xx][yy][ queue[front].x ][ queue[front].y ] + 1;
        }
    }
}

int MIN_steps;
int kingx1, kingy1;
int kingx2, kingy2;
void find(int x, int y)
{
    int knight_num(0);
    // 啊啊啊啊啊aaaa，少了个 = 调了半天
    for (int i = 1; i <= N; ++i)
        knight_num += dis[ knight[i].x ][ knight[i].y ][x][y];
    if (knight_num >= MIN_steps) return;

    int steps_num(0);
    int temp(0);
    for (int i = kingx1; i <= kingx2; ++i)
        for (int j = kingy1; j <= kingy2; ++j)
            // 对每个骑士进行测试
            // 把原来的路径拆分，拆成先走向国王，再走向终点
            for (int kni = 1; kni <= N; ++kni) {
                // 先去掉原来骑士的步数
                steps_num = knight_num - dis[ knight[kni].x ][ knight[kni].y ][x][y];
                // temp 为国王需要走的步数
                temp = max(abs(king.x-i), abs(king.y-j));
                // 加上拆分后路径步数
                temp += dis[ knight[kni].x ][ knight[kni].y ][i][j] 
                        + dis[i][j][x][y];
                if (steps_num + temp < MIN_steps)
                    MIN_steps = steps_num + temp;
            }
}

void search()
{
    // 没有骑士
    if (N == 0) {
        ofile << 0 << endl;
        return ;
    }
  for (int i1 = 1; i1 <= Col; i1++)
    for (int j1 = 1; j1 <= Row; j1++)
      for (int i2 = 1; i2 <= Col; i2++)
        for (int j2 = 1; j2 <= Row; j2++)
          dis[i1][j1][i2][j2] = INFTY;

    for (int i = 1; i <= Col; ++i)
        for (int j = 1; j<= Row; ++j)
            BFS(i, j);
    MIN_steps = INFTY;
    // 算出king的+-2步界限
    // 意思是说，骑士只要走到国外的附近即可
    kingx2 = king.x + 2 > Col ? Col : king.x + 2;
    kingy2 = king.y + 2 > Row ? Row : king.y + 2;
    kingx1 = king.x - 2 < 1 ? 1 : king.x - 2;
    kingy1 = king.y - 2 < 1 ? 1 : king.y - 2;
    
    for (int i = 1; i <= Col; ++i)
        for (int j = 1; j <= Row; ++j)
            find(i, j);

    ofile << MIN_steps << endl;
    return ;
}

int main(void)
{
    // 输入
    char c;
    ifile >> Row >> Col;
    ifile >> c >> king.y;
    king.x = c - 'A' + 1;
    int num;
    while (ifile >> c >> num) {
        knight[++N].x = c - 'A' + 1;
        knight[N].y = num;
    }

    // search
    search();


    return 0;
}

