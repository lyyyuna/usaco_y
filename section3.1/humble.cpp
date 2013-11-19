/*
ID: lyyyuna
PROG: humble
LANG: C++
*/

#include <fstream>
#include <climits>

using namespace::std;

const int MAXPRIME = 101;
const int MAXN = 100001;

int main(void)
{
    ifstream ifile("humble.in");
    ofstream ofile("humble.out");

    int K, N;
    ifile >> K >> N;
    int prime[MAXPRIME];
    for (int i = 0; i < K; ++i)
        ifile >> prime[i];

    long long hum[MAXN] = {0};
    int nhum(0);
    hum[nhum++] = 1;
    int prime_index[MAXPRIME];
    for (int i = 0; i < K; ++i)
        prime_index[i] = 0;

    while (nhum < N+1) {
        int min = INT_MAX;
        // 对
        for (int i = 0; i < K; ++i) {
            // prime[i] 和 prime_index[i]一一对应
            // 表示 第i个素数，已经累计在丑数里面 乘到第prime_index[i]个
            /*
            对于每个质数p 寻找最小的丑数h 使得 h * p 比上一个丑数大
            取我们找到的 h * p 中最小的一个：它就是下一个丑数 为了使搜索更
            快，我们可以为每个质数维护一个索引“pindex”表示每个质数已经乘
            到了哪个丑数，每次都从那里开始，而不是再从头再来。
            */
            while ((long long)prime[i] * hum[prime_index[i]] <= hum[nhum-1])
                prime_index[i] ++;
            // 跟新第nhum个丑数的最小值方案
            if ((long long) prime[i] * hum[prime_index[i]] < min)
                min = prime[i] * hum[prime_index[i]];
        }
        // 算出第nhun个丑数
        hum[nhum++] = min;
    }

    ofile << hum[N] << endl;

    return 0;
}