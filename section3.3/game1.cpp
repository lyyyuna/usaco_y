/*
ID: lyyyuna
PROG: game1
LANG: C++
*/

#include <fstream>

using namespace::std;

int main(void)
{
    ifstream ifile("game1.in");
    ofstream ofile("game1.out");
    int num;
    ifile >> num;
    int number[100+1] = {0};
    for (int i = 1; i <= num; ++i)
        ifile >> number[i];

    int sum[101][101] = {0};  // 统计从i到j之间，数字相加之和
    for (int i = 1; i <= num; ++i) {
        sum[i][i] = number[i];
        for (int j = i; j <= num; ++j)
            sum[i][j] = sum[i][j-1] + number[j];
    }

    int first[101][101] = {0};  // 从 i到j ，先取得那个人获得分数
                                // [i][j]表示从i到j这部分的先取者能获得的最大数字和 
    for (int i = 1; i <= num; ++i)
        first[i][i] = number[i];
    for (int i = 1; i < num; ++i)
        for (int j = 1; j <= num-i; ++j) {
            // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            // 需要注意的是，这里，first并不是指第一玩家，而是指每次先拿的那个人，即每次拿数的人
            // 因为题目要求，对每个玩家都执行最优操作
            // 这样，dp[1][n]就是指第一玩家，第一玩家为整个游戏第一次拿数的人
            // 举例
            // f[1][2] = sum[1][2] - min(f[1][1], f[2][2])
            // f[1][3] = sum[1][3] - min(f[1][2], f[2][3])
            // [1][2]能得到的最大数字和，[2][3]能得到的最大数字和
            // 比较选出去掉[3]还是[1]最优，就是[1][3]
            first[j][j+i] = sum[j][j+i] - min(first[j][j+i-1], first[j+1][j+i]);
        }
    
    ofile << first[1][num] << " " 
        << sum[1][num] - first[1][num] << endl;

    return 0;
}