/*
ID: lyyyuna
PROG: bigbrn
LANG: C++
*/

#include <fstream>
#include <cstring>

using namespace::std;

const int MAXN = 1000;

int farmdp[MAXN+2][MAXN+2];
bool tree[MAXN+1][MAXN+1] = {0};

inline int min3(int a, int b, int c)
{
    return min(min(a, b), c);
}

int main(void)
{
    ifstream ifile("bigbrn.in");
    ofstream ofile("bigbrn.out");
    int N, T;
    ifile >> N >> T;

    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            farmdp[i][j] = 1;

    for (int i = 1; i <= T; ++i) {
        int x, y;
        ifile >> x >> y;
        tree[x][y] = true;
        farmdp[x][y] = 0;
    }

    for (int i = N; i >= 1; --i)
        for (int j = N; j >= 1; --j)
            if (tree[i][j] == false)
                farmdp[i][j] = min3(farmdp[i+1][j], farmdp[i][j+1], farmdp[i+1][j+1]) + 1;

    int maxlen = 0;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            if (maxlen < farmdp[i][j])
                maxlen = farmdp[i][j];

    ofile << maxlen << endl;

    return 0;
}