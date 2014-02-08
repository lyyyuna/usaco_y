/*
ID: lyyyuna
PROG: twofive
LANG: C++
*/

// http://www.cnblogs.com/txhwind/archive/2012/08/18/2645339.html
// http://hi.baidu.com/winterlegend/item/76fbc2d6bb3e1c10d90e44d3

#include <fstream>
#include <cstring>
#include <string>

using namespace::std;

const int N = 25;
string test(N, '\0');
int matrix[6][6][6][6][6];

inline bool isValid(int a, int deep)
{
    return (!test[a] || test[a]==deep+'A');
}

int dfs(int a, int b, int c, int d, int e, int deep)
{
    if (deep == N)
        return 1;
    
    // 优化，加速
    int &now = matrix[a][b][c][d][e];
    if (now)
        return now;

    if ( a<5 && isValid(a, deep) )
        now += dfs(a+1, b, c, d, e, deep+1);

    if ( b<a && isValid(b+5, deep) )
        now += dfs(a, b+1, c, d, e, deep+1);

    if ( c<b && isValid(c+10, deep) )
        now += dfs(a, b, c+1, d, e, deep+1);

    if ( d<c && isValid(d+15, deep) )
        now += dfs(a, b, c, d+1, e, deep+1);

    if ( e<d && isValid(e+20, deep) )
        now += dfs(a, b, c, d, e+1, deep+1);

    return now;
}

int main(void)
{
    ifstream ifile("twofive.in");
    ofstream ofile("twofive.out");
    char method;
    ifile >> method;
    
    if (method == 'W') {
        int result = 0;

        string str;
        ifile >> str;
        for (int i = 0; i < N; ++i) {
            test[i] = 'A';
            for (; test[i] < str[i]; ++test[i]) {
                memset(matrix, 0, sizeof(matrix));
                result += dfs(0, 0, 0, 0, 0, 0);
            }
        }
        ofile << result + 1 << endl;
    }

    if (method == 'N') {
        int num;
        int tmp;
        ifile >> num;
        for (int i = 0; i < N; ++i) {
            test[i] = 'A';
            memset(matrix, 0, sizeof(matrix));
            while ( (tmp=dfs(0, 0, 0, 0, 0, 0)) < num ) {
                num -= tmp;
                memset(matrix, 0, sizeof(matrix));
                ++test[i];
            }
        }

        ofile << test << endl;
    }
}