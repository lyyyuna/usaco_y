/*
ID: lyyyuna
PROG: numtri
LANG: C++
*/

#include <fstream>

using namespace::std;

const int N = 1000+1;
int tri[N][N] = {0};
//int tri_1[N][N] = {0}

inline long max(long a, long b)
{
    return a>b?a:b;
}

int main (void)
{
    ifstream ifile("numtri.in");
    ofstream ofile("numtri.out");
    
    int n;
    ifile >> n;
    for (int i = 0; i != n; ++i)
        for (int j = 0; j <= i; ++j)
            ifile >> tri[i][j];

    // 动态规划解
    // 从最倒数第二排开始，逐步往上，最后第一层即为最优解
    for (int i = n-2; i >= 0; --i)
        for (int j = 0; j <= i; ++j)
            //tri_1[i][j] += 
            tri[i][j] += max(tri[i+1][j], tri[i+1][j+1]);

    ofile << tri[0][0] << endl;

    return 0;
}