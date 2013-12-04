/*
ID: lyyyuna
PROG: fence3
LANG: C++
*/

#include <fstream>
#include <cstdlib> // srand
#include <ctime> // time
#include <iomanip>
#include <cmath>

using namespace::std;

const int kmax = 100000;

struct Fence
{
    int x1, x2;
    int y1, y2;
} edge[150+1];

int N;

double dis(double x, double y)
{
    double xx, yy;
    double len = 0;
    for (int i = 0; i < N; ++i) {
        double x1 = edge[i].x1;
        double x2 = edge[i].x2;
        double y1 = edge[i].y1;
        double y2 = edge[i].y2;
        if (x>=x1 && x <= x2)
            xx = 0;
        else if (fabs(x1-x)>fabs(x2-x))
            xx = fabs(x2-x);
        else
            xx = fabs(x1-x);

        if (y>=y1 && y<=y2)
            yy = 0;
        else if (fabs(y1-y)>fabs(y2-y))
            yy = fabs(y2-y);
        else
            yy = fabs(y1-y);

        len += sqrt(xx*xx + yy*yy);
    }

    return len;
}

int main(void)
{
    ifstream ifile("fence3.in");
    ofstream ofile("fence3.out");
    ifile >> N;
    for (int i = 0; i < N; ++i) {
        ifile >> edge[i].x1 >> edge[i].y1
            >> edge[i].x2 >> edge[i].y2;
    }

    // 随便选一个点，随机
    srand(time(NULL));
    double test_x = (double)(rand()%1000)/10;
    double test_y = (double)(rand()%1000)/10;
    double test_len = dis(test_x, test_y);
    int k = 0;
    while (k++ < kmax) {
        double step = (double)(rand()%10)/10;
        step = 0.1;
        int dir = rand()%4;
        double tmp_x = test_x;
        double tmp_y = test_y;
        switch (dir) {
        case 0: tmp_x += step; break;
        case 1: tmp_x -= step; break;
        case 2: tmp_y += step; break;
        case 3: tmp_y -= step; break;
        }
        if (tmp_x<0 || tmp_x>100 || tmp_y<0 | tmp_y>100) continue;
        double tmp_len = dis(tmp_x, tmp_y);
        if (tmp_len < test_len) {
            test_len = tmp_len;
            test_x = tmp_x;
            test_y = tmp_y;
        }
    }

    ofile << fixed << setprecision(1) << test_x << " " 
        << test_y << " "
        << test_len << endl;
}