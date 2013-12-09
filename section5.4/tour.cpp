/*
ID: lyyyuna
PROG: tour
LANG: C++
*/

/*
把返回的路线反向，那么整条路线就变成了两条不相交的从起点到
终点的路线。这样我们可以用DP解决。

状态设定
f[i,j] 为假定的甲乙两人，甲走到第i个城市，乙走到第j个城市
时，两人走过的城市数目的和。

初始状态
f[1,1]=1

状态转移方程
f[j,i]=f[i,j]=max{f[i,k]+1}(k到j存在飞机航线，以及f[i,k]>0，
就是说存在f[i,k]的走法，1<=k<j

交换甲乙，则肯定有f[j,i]=f[i,j]。

目标结果
由于题中告知必须走到终点才能返回，输出结果一定是max{f[i,N]}(i
到N存在飞机航线)。 如果没有经过城市数目大于1的可行目标状态，则
无法完成这次环游，输出1。 
*/
#include <fstream>
#include <cstring>
#include <map>
#include <string>

using namespace::std;

int main(void)
{
    ifstream ifile("tour.in");
    ofstream ofile("tour.out");
    int N, V;
    ifile >> N >> V;
    string s1, s2;
    map<string, int> city;
    for (int i = 1; i <= N; ++i) {
        ifile >> s1;
        city[s1] = i;
    }
    bool links[101][101]={0};
    for (int i = 1; i <= V; ++i) {
        ifile >> s1 >> s2;
        int c1 = city[s1];
        int c2 = city[s2];
        links[c1][c2] = true;
        links[c2][c1] = true;
    }

    int dp[101][101]={0};
    dp[1][1] = 1;
    for (int i = 1; i <= N; ++i)
        for (int j = i+1; j <= N; ++j) {
            dp[i][j] = -1111;
            for (int k = 1; k < j; ++k)
                // k到j有直接通路，且dp[i][k]是有解的
                // 不能把dp[i][j]放括号里哦
                if (links[k][j] && dp[i][k] && dp[i][k]>dp[i][j])
                    dp[i][j] = dp[i][k];
            dp[i][j] ++;
            dp[j][i] = dp[i][j];
        }

    int ans = 1;
    for (int i = 1; i <= N; ++i)
        if (links[i][N] && ans < dp[i][N])
            ans = dp[i][N];

    ofile << ans << endl;

    return 0;
}