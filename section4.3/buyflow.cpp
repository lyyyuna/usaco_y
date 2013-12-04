/*
ID: lyyyuna
PROG: buylow
LANG: C++
*/

#include <fstream>
#include <cstring>

using namespace::std;

ifstream ifile("buylow.in");
ofstream ofile("buylow.out");

const int MAXN = 5000+9;

struct BigNum
{
    int n[500];
    int len;
    BigNum(): len(1) {
        memset(n, 0, sizeof(n));
    }
    void operator += (const BigNum &rhs) {
        if (rhs.len > len)
            len = rhs.len;
        for (int i = 0; i < len; ++i) {
            n[i] += rhs.n[i];
            if (n[i] > 9) {
                ++n[i+1];
                n[i] -= 10;
            }
        }
        if (n[len])
            len ++;
    }
    void print() {
        for (int i = len-1; i >= 0; --i)
            ofile << n[i];
        ofile << endl;
    }
};

BigNum MaxCnt[MAXN];

int main(void)
{
    int n;
    ifile >> n;
    int s[MAXN] = {0};
    for (int i = 1; i <= n; ++i)
        ifile >> s[i];
    s[0] = 0x7fffffff;
    MaxCnt[0].len = MaxCnt[0].n[0] = 1;

    // MaxLength[i]为以第i项为末尾中最长下降序列长度
    // 状态转移方程为 MaxLength[i]=max{MaxLength[j]}+1 (j=1..i-1 and s[j]>s[i]) 
    // 初始条件
    // MaxLength[1]=1
    // 对于第二问求最长下降序列的数量，可以通过求第一问的过程解决。
    // 设MaxCnt[i]为第i项为末尾中最长下降序列的个数。
    // 对于所有的j(1≤j≤i-1)如果有(s[j]>s[i] 并且 MaxLength[j]+1>MaxLength[i])
    // 则MaxCnt[i]=MaxCnt[j]，否则如果(MaxLength[j]+1==MaxLength[i])可利用加法原理，MaxCnt[i]=MaxCnt[i]+MaxCnt[j]。 
    int MaxLength[MAXN] = {0};

    // 最后加1
    // 最后一个s[n]为0，即所有买股票方案都会将这个新的s[n]考虑在内，将n项作为末尾的最长。。。
    // 之所以这样
    // 是为了方便做最后的统计，如果是原来那样，就无法统计了呀
    ++n; // ????????????????????????????????????????????????

    for (int i = 1; i <= n; ++i) {
        for (int j = i-1; j >= 0 && s[j]!=s[i]; --j) {
            // 当前股票值小s[i]
            if (s[j] > s[i]) {
                if (MaxLength[j]+1 > MaxLength[i]) {
                    MaxLength[i] = MaxLength[j] + 1;
                    MaxCnt[i] = MaxCnt[j];
                }
                else if (MaxLength[j]+1 == MaxLength[i])
                    MaxCnt[i] += MaxCnt[j];
            }
        }
    }

    ofile << MaxLength[n]-1 << " ";
    MaxCnt[n].print();

    return 0;
}