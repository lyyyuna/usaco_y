/*
ID: lyyyuna
PROG:  inflate
LANG: C++
*/

#include <fstream>

using namespace::std;

int main(void)
{
    ifstream ifile("inflate.in");
    ofstream ofile("inflate.out");

    int T, M;
    ifile >> T >> M;
    int score, times;
    int dp[10000+1]={0};
    for (int i = 1; i <= M; ++i) {
        ifile >> score >> times;
        for (int j = times; j <= T; ++j)
            dp[j] = max(dp[j], dp[j-times]+score);
    }

    ofile << dp[T] << endl;

    return 0;
}