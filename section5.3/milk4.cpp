/*
ID: lyyyuna
PROG: milk4
LANG: C++
*/

#include <fstream>
#include <algorithm>
#include <cstdlib>

using namespace::std;

ifstream ifile("milk4.in");
ofstream ofile("milk4.out");

int Q, P;
int pales[101]; //  记录每个桶容量
int pales_buy[101]; // 记录方案数，记录一个方案中第I个桶的编号，
                    // 指去称奶 要用哪些桶

int ans;

void print()
{
    ofile << ans;
    for (int i = 1; i <= ans; ++i)
        ofile << " " << pales[ pales_buy[i] ];
    ofile << endl;

    exit(0);
}

const int MAXQ = 20000+1;
void DP_check()
{
    bool dp[MAXQ] = {0};
    // 用来装奶的pales_buy[1]，记录是哪个桶
    // pales[pales_buy[1]] 这个桶的大小
    // 然后 1*pales[pales_buy[1]]， 2*pales[pales_buy[1]].。。。这些奶的量都是可以拿这个桶称出来的
    for (int i = 1; i <= Q/pales[pales_buy[1]]; i++)
        dp[i*pales[pales_buy[1]]] = true;
    // 动态规划，和上面相同的原理
    for (int i = 2; i <= ans; ++i)
        for (int j = pales[ pales_buy[i] ]; j <= Q; ++j)
            dp[j] |= dp[ j-pales[pales_buy[i]] ];

    // 说明能称出Q夸脱的奶
    if (dp[Q] == true)
        print();
}

void dfs(int deep)
{
    // i = pales_buy[deep-1]+1
    // 下一层的桶方案
    for (int i = pales_buy[deep-1]+1; i <= P-ans+deep; ++i) {
        // 第deep个桶要用第i桶
        // （绕了点），是指i是对应给的原桶
        // pales_buy是指去称奶 要用哪些桶
        pales_buy[deep] = i;
        // 搜索到头，进行验证
        if (deep == ans)
            DP_check();
        else
            dfs(deep+1);
    }
}

int main(void)
{
    ifile >> Q >> P;
    for (int i = 1; i <= P; ++i)
        ifile >> pales[i];

    sort(pales, pales+P);

    // 先找牛奶桶数量为1的时候所有的组合，如果没有解再找牛奶桶数量为2...直到牛奶桶数量为P
    for (ans = 1; ans <= P; ++ans) 
        // 每次从一桶搜，直到桶数==ans
        dfs(1);

    return 0;
}