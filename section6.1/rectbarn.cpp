/*
ID: lyyyuna
PROG: rectbarn
LANG: C++
*/
/*
令h[i][j]表示(i,j)到竖直向上的最近障碍点（或顶端）的线段的
长度，left[i][j]、right[i][j]分别表示该线段向左、右延伸的
长度。则max{h[i][j]*(left[i][j]+right[i][j]-1)}即为答案。

使用动态规划求h[i][j]、left[i][j]、right[i][j]。
*/

#include <fstream>

using namespace::std;

const int MAXN = 3000+1;

bool map[MAXN][MAXN];
int heightt[MAXN];
int leftt[MAXN];
int rightt[MAXN];

inline int min(int a, int b)
{
    return a ? (a<b?a:b) : b;
}

int main(void)
{
    ifstream ifile("rectbarn.in");
    ofstream ofile("rectbarn.out");
    int R, C, P;
    ifile >> R >> C >> P;
    for (int i = 1; i <= P; ++i) {
        int x, y;
        ifile >> x >> y;
        map[x][y] = true;
    }

    int result = 0;
    for (int i = 1; i <= R; ++i) {
        int k = 0;
        for (int j = 1; j <= C; ++j)
            if (map[i][j] == true) {
                heightt[j] = 0;
                leftt[j] = k = 0;
            } else {
                heightt[j] ++;
                leftt[j] = min(leftt[j], ++k);
            }
    
        k = 0;
        for (int j = C; j; --j) {
            if (map[i][j] == true) {
                k = 0;
                rightt[j] = 0;
            } else {
                rightt[j] = min(rightt[j], ++k);
            }

            if ( result < (heightt[j]*(leftt[j]+rightt[j]-1)) )
                result = (heightt[j]*(leftt[j]+rightt[j]-1));
        }
    }

    ofile << result << endl;
    return 0;
}