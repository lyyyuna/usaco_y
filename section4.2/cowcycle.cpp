/*
ID: lyyyuna
PROG: cowcycle
LANG: C++
*/

#include <fstream>
#include <algorithm>

using namespace::std;

int F, R;
int F1, F2, R1, R2;
double ratio[80+1][40+1]; /// ------||||
int gearF[5+1];
int gearR[10+1];
double minV = 1398233.3;

int x[5+1];
int y[10+1];

void calculate(void)
{
    double ratios[55] = {0};
    int k = 1;
    for (int i = 1; i <= F; ++i)
        for (int j = 1; j <= R; ++j)
            ratios[k++] = ratio[ gearF[i] ][ gearR[j] ];
    sort(ratios+1, ratios+k);

    double xx=0;
    double c[55] = {0};
    for(int i = 2; i < k; ++i)
        c[i-1] = ratios[i] - ratios[i-1];
    for(int i = 1 ; i < k-1; ++i) 
        xx += c[i];
    xx = xx / (k-2); // 平均值

    double ans = 0; 
    for(int i = 1; i < k-1; ++i)
        ans += (xx-c[i])*(xx-c[i]);  // 方差
 
    ans = ans/(k-2); 
 
    if (ans < minV) {
        minV = ans; 
        for (int i = 1; i <= F; ++i)
            x[i] = gearF[i];
        for (int i = 1; i <= R; ++i)
            y[i] = gearR[i];
    }
}

void dfsR(int x)
{
    if (x > R) {
        if (gearR[R]*gearF[F] < 3*gearF[1]*gearR[1])
            return ;
        calculate();
        return ;
    }
    for (int i = gearR[x-1]+1; i <= R2; ++i) {
        gearR[x] = i;
        dfsR(x+1);
    }
}

void dfsF(int x)
{
    if (x > F) {
        dfsR(1);
        return ;
    }
    for (int i = gearF[x-1]+1; i <= F2; ++i) {
        gearF[x] = i;
        dfsF(x+1);
    }
}

int main(void)
{
    ifstream ifile("cowcycle.in");
    ofstream ofile("cowcycle.out");
    ifile >> F >> R
        >> F1 >> F2
        >> R1 >> R2;
    for (int i = F1; i <= F2; ++i)
        for (int j = R1; j <= R2; ++j)
            ratio[i][j] = i*1.0/(j*1.0);

    gearF[0] = F1-1;
    gearR[0] = R1-1;

    dfsF(1);

    for (int i = 1; i < F; ++i)
        ofile << x[i] << " ";
    ofile << x[F] << endl;

    for (int i = 1; i < R; ++i)
        ofile << y[i] << " ";
    ofile << y[R] << endl;

    return 0;
}