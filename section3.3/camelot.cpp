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
int N;  // һ���ж��ٸ���ʿ
int dis[26+1][30+1][26+1][30+1];    // ��¼���룬ǰ����Ϊ��һ���㣬������Ϊ�ڶ�����
const int INFTY = 23232;

bool flag[26+1][30+1];  // ��¼ĳһ�����Ƿ񱻷��ʹ�
int dir[9][2] = {{0,0},{-2,-1},{-2,1},{2,-1},{2,1},{1,2},{1,-2},{-1,2},{-1,-2}};
// ����ÿһ���㵽��xx��yy�����룬
// ������bfs��������Ŀ϶�����̾���
void BFS(int xx, int yy)
{
    memset(queue, 0, sizeof(queue));
    memset(flag, 0, sizeof(flag));
    dis[xx][yy][xx][yy] = 0;    // �Լ����Լ�Ϊ0
    flag[xx][yy] = true;
    // ģ�����
    int front = 0;  // ����ͷ
    int rear = 1;   // ����β
    queue[rear].x = xx;
    queue[rear].y = yy;
    int x, y;
    while(front < rear) {
        front ++;
        // 8������
        for (int i = 1; i <= 8; ++i) {
            // �����һ�����ܵ�
            x = queue[front].x + dir[i][0];
            y = queue[front].y + dir[i][1];
            // �����߽�
            if (x<1 || x>Col || y<1 || y>Row)
                continue;
            // �ѱ����ʹ�
            if (flag[x][y] == true)
                continue;
            // ģ��������
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
    // ����������aaaa�����˸� = ���˰���
    for (int i = 1; i <= N; ++i)
        knight_num += dis[ knight[i].x ][ knight[i].y ][x][y];
    if (knight_num >= MIN_steps) return;

    int steps_num(0);
    int temp(0);
    for (int i = kingx1; i <= kingx2; ++i)
        for (int j = kingy1; j <= kingy2; ++j)
            // ��ÿ����ʿ���в���
            // ��ԭ����·����֣����������������������յ�
            for (int kni = 1; kni <= N; ++kni) {
                // ��ȥ��ԭ����ʿ�Ĳ���
                steps_num = knight_num - dis[ knight[kni].x ][ knight[kni].y ][x][y];
                // temp Ϊ������Ҫ�ߵĲ���
                temp = max(abs(king.x-i), abs(king.y-j));
                // ���ϲ�ֺ�·������
                temp += dis[ knight[kni].x ][ knight[kni].y ][i][j] 
                        + dis[i][j][x][y];
                if (steps_num + temp < MIN_steps)
                    MIN_steps = steps_num + temp;
            }
}

void search()
{
    // û����ʿ
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
    // ���king��+-2������
    // ��˼��˵����ʿֻҪ�ߵ�����ĸ�������
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
    // ����
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

