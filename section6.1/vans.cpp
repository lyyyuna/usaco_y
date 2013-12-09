/*
ID: lyyyuna
PROG: vans
LANG: C++
*/

#include <fstream>
#include <cstring>

using namespace::std;

// ####
// (()) ()() ()## (##) ##() #()#
// 表示从一个状态到另一个状态是否可行
const bool isLink[6][6]=
           {{1,0,1,0,1,0},
            {0,1,0,1,0,0},
            {0,1,0,1,0,0},
            {1,0,1,0,1,1},
            {0,1,0,1,0,0},
            {0,0,0,1,0,0}};

struct BigInt
{
    int n[500];
    int len;

    void set(int t)
    {
        memset(n, 0, sizeof(n));
        n[0] = t;
        len = 1;
    }

    void operator += (const BigInt rhs)
    {
        if (rhs.len > len)
            len = rhs.len;
        for (int i = 0; i < len; ++i) {
            n[i] += rhs.n[i];
            if (n[i] > 9) {
                n[i+1] ++;
                n[i] -= 10;
            }
        }
        if (n[len])
            len ++;
    }
};

BigInt f[2][6];

int main(void)
{
    ifstream ifile("vans.in");
    ofstream ofile("vans.out");

    int num;
    ifile >> num;
    BigInt result;
    result.set(0);

    if (num != 1) {
        int old = 1;
        int now = 0;
        f[0][2].set(1);
        f[0][3].set(1);
        for (int i = 1; i < num; ++i) {
            old ^= 1;
            now ^= 1;
            for (int j = 0; j < 6; ++j)
                f[now][j].set(0);
            for (int j = 0; j < 6; ++j)
                for (int k = 0; k < 6; ++k)
                    // 枚举所有状态，看是否可行
                    if (isLink[j][k])
                        f[now][k] += f[old][j];
        }
        // 只有这两种才可能为最终状态
        result += f[now][2];
        result += f[now][4];
    }

    for (int i = result.len-1; i >= 0; --i)
        ofile << result.n[i];
    ofile << endl;

    return 0;
}