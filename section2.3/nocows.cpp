/*
ID: lyyyuna
PROG: nocows
LANG: C++
*/

#include <fstream>

using namespace::std;

int table[101][201];    // 用来记录第i层 j个元素的 
int smalltrees[101][201];

int main(void)
{
    ifstream ifile("nocows.in");
    ofstream ofile("nocows.out");

    int N, K;
    ifile >> N >> K;
    // 根
    table[1][1] = 1;
    // 从第二层开始
    for (int i = 2; i <= K; ++i) {
        // 因为至少有一个根，而且孩子不是2就是0，所以只要+2
        for (int j = 1; j <= N; j += 2)
            // 左树有k个，右边有 j-k-1 个。
            for (int k = 1; k <= j-1-k; k += 2) {
                int factor(0);
                // 不用重复计算，左树k个，只要计算到 k <= j-k-1 就为止。
                // 再往后就是重复的。比如 左边j-k-1 右边k。，只要乘以2就免得再计算一遍
                // 若 k == j-k-1，就不用重复了，左右两边一样
                if (k != (j-1-k))
                    factor = 2;
                else 
                    factor = 1;
                /*
                table[i][j] := smalltrees[i-2][k]*table[i-1][j-1-k];
                  // 左子树深度小于i-1，右子树深度为i-1
                table[i][j] := table[i-1][k]*smalltrees[i-2][j-1-k];
                  // 左子树深度为i-1，右子树深度小于i-1
                table[i][j] := table[i-1][k]*table[i-1][j-1-k];
                  // 左右子树深度都为i-1 
                */
                table[i][j] += factor*(smalltrees[i-2][k] * table[i-1][j-k-1]
                            + table[i-1][k] * smalltrees[i-2][j-k-1]
                            + table[i-1][k] * table[i-1][j-k-1]);
                // if (k != j-1-k)
                //    table[i][j] *= 2;
                table[i][j] %= 9901;
            }
        
        // 这个是用来跟新smalltrees的，
        // 即所有深度小于 i-1 的情况
        for (int k = 0; k <= N; ++k) {
            smalltrees[i-1][k] += table[i-1][k] + smalltrees[i-2][k];
            smalltrees[i-1][k] %= 9901;
        }
    }

    ofile << table[K][N] << endl;

    return 0;
}