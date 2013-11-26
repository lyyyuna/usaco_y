/*
ID: lyyyuna
PROG: nuggets
LANG: C++
*/

#include <fstream>

using namespace::std;

int gcd(int x, int y)
{
    if (x > y)
        swap(x, y);
    if (x == 0)
        return y;
    return gcd(y%x, x);
}

int main(void)
{
    ifstream ifile("nuggets.in");
    ofstream ofile("nuggets.out");

    int n, num[10+1];
    ifile >> n;
    for (int i = 1; i <= n; ++i) {
        ifile >> num[i];
    }
    int k = num[1];
    for (int i = 2; i <= n; ++i) {
        k = gcd(k, num[i]);
    }

    if (k != 1) {
        ofile << 0 << endl;
        return 0;
    }

    bool dp[65536+1] = {false};
    dp[0] = true;
    // 动态规划，i， i-num[j],这两个数是都能表示的
    for (int i = 1; i <= 65536; ++i) {
        for (int j = 1; j <= n; ++j)
            if (i >= num[j])
                dp[i] = dp[i] || dp[i-num[j]];
    }
    int result = 0;
    for (int i = 65536; i>= 1; --i)
        if (dp[i] == false) {
            result = i;
            break;
        }

    ofile << result << endl;

    return 0;
}