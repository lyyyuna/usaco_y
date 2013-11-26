/*
ID: lyyyuna
PROG: range
LANG: C++
*/

#include <fstream>

using namespace::std;

int main(void)
{
    ifstream ifile("range.in");
    ofstream ofile("range.out");

    int num;
    ifile >> num;
    int graph[300][300] = {0};
    int dp[300][300] = {0};
    for (int i = 1; i <= num; ++i) {
        for (int j = 1; j <= num; ++j) {
            char c;
            ifile >> c;
            if (c == '1') graph[i][j] = 1;
            else graph[i][j] = 0;
        }
    }

    for (int i = 1; i <= num; ++i)
        for (int j = 1; j <= num; ++j)
            if (graph[i][j] == 1)
                dp[i][j] = min(dp[i-1][j-1], min(dp[i][j-1], dp[i-1][j])) + 1;

    int count[300] = {0};
    for (int i = 1; i <= num; ++i)
        for (int j = 1; j <= num; ++j)
            // 从边长2开始
            for (int k = 2; k <= dp[i][j]; ++k)
                count[k] ++;

    // output
    for (int i = 2; i <= num; ++i)
        if (count[i] != 0)
            ofile << i << " " << count[i] << endl;

    return 0;
}