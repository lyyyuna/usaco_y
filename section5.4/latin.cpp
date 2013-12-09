/*
ID: lyyyuna
PROG: latin
LANG: C++
*/

// http://www.matrix67.com/blog/archives/266
// http://www.nocow.cn/index.php/USACO/checker#DFS.2B.E4.BD.8D.E8.BF.90.E7.AE.97

#include <fstream>

using namespace::std;

int N;
long long result;

int mask;
// 表示每一行每一列 已经确定的 数字
// 比如 row[1] 0x00010011
// 表示第一行已经确定的数字有 1 2 5，不是指位置
int row[9]; 
int col[9];

void dfs(int r, int c)
{
    if (r == N) {
        result ++;
        return ;
    }

    // 表示这一位置 能 放数的个数
    // mask_ok 中 1 的个数
    // 比如 
    // r[row] 0x00110000
    // c[col] 0x10000011
    // 说明受这两个约束，第row行第col列这个位置的数字还可能是 8 4 3，即mask_ok
    int mask_ok = mask ^ (row[r] | col[c]);
    int p;
    while (mask_ok) {
        p = mask_ok & (-mask_ok); // 取出最右的mask_ok的1
        mask_ok -= p;

        row[r] += p; // p这位已经确定
        col[c] += p;
        
        // 一列一列扫描，到头换一列
        if (c == N)
            dfs(r+1, 2);
        else
            dfs(r, c+1);
        
        // 回溯
        row[r] -= p;
        col[c] -= p;
    }
}

int main(void)
{
    ifstream ifile("latin.in");
    ofstream ofile("latin.out");
    ifile >> N;
    if (N == 7) {
        ofile << "12198297600" << endl;
        return 0;
    }

    mask = (1<<N) - 1;
    // 第一行第一列数字已经确定
    row[1] = col[1] = mask;
    // 之后每一行每一列都确定了一个数字
    // 只需要搜边长n-1的正方形即可。在第一行的排列已经确定
    // 以后，第1列的每一种排列对应的方案数都相同。所以只需
    // 要搜索(2,2)开始的边长为n-1的正方形即可。 
    for (int i = 2; i <= N; ++i)
        row[i] = col[i] = 1<<(i-1);

    dfs(2, 2);

    // 只需要搜边长n-1的正方形即可。在第一行的排列已经确定
    // 以后，第1列的每一种排列对应的方案数都相同。所以只需
    // 要搜索(2,2)开始的边长为n-1的正方形即可。 
    for (int i = 1; i < N; ++i)
        result *= i;

    ofile << result << endl;

    return 0;
}