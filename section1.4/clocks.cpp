/*
ID: lyyyuna
PROG: clocks
LANG: C++
*/

#include <fstream>
#include <string>
#include <iostream>
using namespace::std;

//int movedist[9][9];
int clocks[9];
int bestmove[9];
int nbestmove;

// char *movestr[] = { "abde", "abc", "bcef", "adg", "bdefh", "cfi", "degh",
//                    "ghi", "efhi" };
/*
void mkmove(void)
{
    for (int i = 0; i != 9; ++i) {
        for (char *p = movestr[i]; *p; p++)
            movedist[i][*p - 'a'] = 3;
    }
}*/
int movedist[9][9]=
{3, 3, 0, 3, 3, 0, 0, 0, 0,
 3, 3, 3, 0, 0, 0, 0, 0, 0,
 0, 3, 3, 0, 3, 3, 0, 0, 0,
 3, 0, 0, 3, 0, 0, 3, 0, 0,
 0, 3, 0, 3, 3, 3, 0, 3, 0,
 0, 0, 3, 0, 0, 3, 0, 0, 3,
 0, 0, 0, 3, 3, 0, 3, 3, 0,
 0, 0, 0, 0, 0, 0, 3, 3, 3,
 0, 0, 0, 0, 3, 3, 0, 3, 3};

void solve_dfs(int move[], int k)
{
    /* 这是递归的出口 k==9 */
    if (k == 9) {
        // 判断经过所有的动作之后，是否指向了12点
        for (int i = 0; i != 9; ++i)
            if (clocks[i] % 12 != 0)
                // 不符合要求的递归出口
                return;

        // 到这里，说明全指向了12点
        // 统计
        int n(0);
        for (int i = 0; i != 9; ++i)
            n += move[i];
        cout << n << endl;
        // 找到最小
        if (nbestmove == 0 || n < nbestmove) {
            nbestmove = n;
            for (int i = 0; i != 9; ++i)
                bestmove[i] = move[i];
        }
        // 全指向12点的递归出口
        return ;
    }

    // dfs的主要搜索路径
    for (int rep = 3; rep >= 0; --rep) {
        // 每一个分支顺时针转rep次
        for (int i = 0; i != rep; ++i)
            for (int j = 0; j != 9; ++j)
                // 整个递归树有9层，这是第k层
                clocks[j] += movedist[k][j];
        move[k] = rep;

        solve_dfs(move, k+1);

        // 回溯
        // 恢复同一层所做的顺时针动作
        // 和solve_dfs之前的代码是对称的
        for (int i = 0; i < rep; ++i)
            for (int j = 0; j != 9; ++j)
                clocks[j] -= movedist[k][j];
    }
}

int main(void)
{
    ifstream ifile("clocks.in");
    ofstream ofile("clocks.out");

    // mkmove();

    for (int i = 0; i != 9; ++i)
        ifile >> clocks[i];

    int move[9]={0};
    solve_dfs(move, 0);

    string s="";
    for (int i = 0; i != 9; ++i)
        for (int j = 0; j != bestmove[i]; ++j) {
            ofile << s << i+1;
            s = " ";
        }
    ofile << endl;
    
    return 0;
}