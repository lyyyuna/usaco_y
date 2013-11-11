/*
ID: lyyyuna
PROG: money
LANG: C++
*/

#include <fstream>

using namespace::std;

int main(void)
{
    ifstream ifile("money.in");
    ofstream ofile("money.out");

    int V, N;
    ifile >> V >> N;

    int kind_money[25];
    for (int i = 0; i < V; ++i)
        ifile >> kind_money[i];
    
    // dp[j] 为 j单位面值的 数量
    long long dp[10001]={0};
    // 为什么dp[0]是1？还没搞懂
    dp[0] = 1;
    for (int i = 0; i < V; ++i)
        // dp[i,j] = dp[i-1,j];    不用第i种货币
        // dp[i,j] = dp[i-1,j]+dp[i,j-kind_money[i]]    用第i种货币，j>=kind_money[i]
        // 这里用一维数组节省空间
        // 因为不相干扰
        for (int j = kind_money[i]; j <= N; ++j)
            dp[j] = dp[j] + dp[j-kind_money[i]];

    ofile << dp[N] << endl;

    return 0;
}