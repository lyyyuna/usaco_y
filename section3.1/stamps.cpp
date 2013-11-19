/*
ID: lyyyuna
PROG: stamps
LANG: C++
*/

#include <fstream>
#include <climits>

using namespace::std;

int main(void)
{
    ifstream ifile("stamps.in");
    ofstream ofile("stamps.out");
    int K1, N;
    ifile >> K1 >> N;
    int stamps[50+1];
    for (int i = 0; i < N; ++i)
        ifile >> stamps[i];
    int dp[200000+1];
    dp[0] = 0;
    int i = 1;
    for (; i < 2000000; ++i) {
        dp[i] = INT_MAX;
        for (int j = 0; j < N; ++j)
            if (stamps[j] <= i)
                dp[i] = min(dp[i], dp[i-stamps[j]]+1);
        if (dp[i] > K1)
            break;
    }

    ofile << i-1 << endl;
    
    return 0;
}