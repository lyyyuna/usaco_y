/*
ID: lyyyuna
PROG: cowtour
LANG: C++
*/

#include <fstream>
#include <math.h>

using namespace::std;

const int MAXN = 151;
const int INFTY = 999999;
int N;
int x[MAXN], y[MAXN];

double point[MAXN];

double dist[MAXN][MAXN];

double min_dis(INFTY);

double distance(int x1, int y1, int x2, int y2)
{
    return ( sqrt( 1.0*(x1-x2)*(x1-x2)+1.0*(y1-y2)*(y1-y2) ) );
}


void Floyd(void)
{
    for (int k = 1; k <= N; ++k)
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j) {
                if (k==i || k==j) continue;
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
}

void find_solution()
{
    // 找到每一片各自连通的牧场内部，
    // 每一片连通区内的最大的距离，即直径
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j) {
            // 经过前面的运算
            // 只要是INFTY的说明，i和j不是一个连通区的
            if (dist[i][j] != INFTY && point[i] < dist[i][j] )
                point[i] = dist[i][j];
        }

    // 将两个不连通的连通去试着连起来
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j) {
            // INFTY说明不连着
            if (dist[i][j] == INFTY) {
                // 先连i和j
                double new_dis = distance(x[i], y[i], x[j], y[j]);
                // 然后加上各自连通区的直径
                if (point[i] + new_dis + point[j] < min_dis)
                    min_dis = point[i] + new_dis + point[j];
            }
        }
    // 也有可能某个连通区本身的直径就很大了
    for (int i = 1; i <= N; ++i)
        if (min_dis < point[i])
            min_dis = point[i];


}

int main(void)
{
    ifstream ifile("cowtour.in");
    ofstream ofile("cowtour.out");
    ifile >> N;
    // 读入数据，并设置当前点的根节点为自己
    for (int i = 1; i <=N; ++i) {
        ifile >> x[i] >> y[i];
        point[i] = -1;
    }

    char c;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            ifile >> c;
            // 如果是本身，距离为0
            if (i == j) dist[i][j] = 0;
            // 如果是0，则设为无穷大，说明不连接
            else if (c == '0') dist[i][j] = INFTY;
            // 如果连接
            else if (c == '1') {
                // 首先跟新 点i和点j的根节点，
                // updateParent(i, j);
                // 算出两者的距离
                dist[i][j] = distance(x[i], y[i], x[j], y[j]);
            }
        }
    }
    // 用Floyd算出每两个点之间最小距离
    Floyd();
    find_solution();
    ofile << fixed << min_dis << endl;
    return 0;
}