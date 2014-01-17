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
    // �ҵ�ÿһƬ������ͨ�������ڲ���
    // ÿһƬ��ͨ���ڵ����ľ��룬��ֱ��
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j) {
            // ����ǰ�������
            // ֻҪ��INFTY��˵����i��j����һ����ͨ����
            if (dist[i][j] != INFTY && point[i] < dist[i][j] )
                point[i] = dist[i][j];
        }

    // ����������ͨ����ͨȥ����������
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j) {
            // INFTY˵��������
            if (dist[i][j] == INFTY) {
                // ����i��j
                double new_dis = distance(x[i], y[i], x[j], y[j]);
                // Ȼ����ϸ�����ͨ����ֱ��
                if (point[i] + new_dis + point[j] < min_dis)
                    min_dis = point[i] + new_dis + point[j];
            }
        }
    // Ҳ�п���ĳ����ͨ�������ֱ���ͺܴ���
    for (int i = 1; i <= N; ++i)
        if (min_dis < point[i])
            min_dis = point[i];


}

int main(void)
{
    ifstream ifile("cowtour.in");
    ofstream ofile("cowtour.out");
    ifile >> N;
    // �������ݣ������õ�ǰ��ĸ��ڵ�Ϊ�Լ�
    for (int i = 1; i <=N; ++i) {
        ifile >> x[i] >> y[i];
        point[i] = -1;
    }

    char c;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            ifile >> c;
            // ����Ǳ�������Ϊ0
            if (i == j) dist[i][j] = 0;
            // �����0������Ϊ�����˵��������
            else if (c == '0') dist[i][j] = INFTY;
            // �������
            else if (c == '1') {
                // ���ȸ��� ��i�͵�j�ĸ��ڵ㣬
                // updateParent(i, j);
                // ������ߵľ���
                dist[i][j] = distance(x[i], y[i], x[j], y[j]);
            }
        }
    }
    // ��Floyd���ÿ������֮����С����
    Floyd();
    find_solution();
    ofile << fixed << min_dis << endl;
    return 0;
}