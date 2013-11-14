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
char graph[MAXH+MAXH][MAXW+MAXW];   // �洢�����ַ�������Χǽ
bool maps[MAXH][MAXW];              // ֻ�洢ÿ����Ԫ�������Ƿ񱻷��ʹ�
int dist[2][MAXH][MAXW];            // �洢ÿ���㵽���ڵ���С����

int startx[2], starty[2];           // �洢���ڵ�����λ��
int dx[] = {-1, 1, 0, 0};           // ���Ʒ���
int dy[] = {0, 0, -1, 1};           // ���Ʒ���

struct Node
{
    int x;
    int y;
    int dist;
};


void bfs(int startx, int starty, int which_start)
{
    queue <Node> q;
    // cΪ��ǰ��Ԫ��nΪ��һ���������ڵĵ�Ԫ
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

        // һ����Ԫ���⹲���ĸ����ܵķ���
        for (int k = 0; k < 4; ++k) {
            // �ж�ǽ������ c.x*2 + dx[k]
            if (graph[c.x*2 + dx[k]][c.y*2 + dy[k]] == ' ') {
                // û��
                n.x = c.x + dx[k];
                n.y = c.y + dy[k];
                // �ѱ����ʹ�
                if (maps[n.x][n.y])
                    continue;
                // û�з��ʹ�
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
    int k(0);   // ԭ��������ĸ���ʼ��
    for (int i = 1; i <= 2*H+1; ++i) {
        // ��������������� ofile<< ����������ո�
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
                graph[i][j] = '-';  // ��ʵ�ĸ��ַ�������ν��ֻҪ���ǿո�
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
    // ��һ����ʼ��
    bfs(startx[0], starty[0], 0);
    memset(maps, false, sizeof(maps));
    // �ڶ�����ʼ��
    bfs(startx[1], starty[1], 1);

    int max_min(0), min_dist(0);
    // ��������������·���е� ���·������
    for (int i = 1; i <= H; ++i)
        for (int j = 1; j <= W; ++j) {
            min_dist = dist[0][i][j] < dist[1][i][j]?
                        dist[0][i][j] : dist[1][i][j];
            max_min = min_dist > max_min ? min_dist : max_min;
        }

    ofile << max_min << endl;

    return 0;
}