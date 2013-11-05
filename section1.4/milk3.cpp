/*
ID: lyyyuna
PROG: milk3
LANG: C++
*/

#include <fstream>

using namespace::std;

const int N = 21;

bool bucket[N][N][N] = {false};
bool c_bucket[N];
int a, b, c;

void dfs(int a1, int b1, int c1)
{
    // 这是递归的出口
    // 意思是，这种情况已经出现过即
    // 三个桶为a1, b1, c1的情况在之前的情况已经出现，这时就没必要
    // 再继续递归下去了，是重复的
    if (bucket[a1][b1][c1])
        return ;
    bucket[a1][b1][c1] = true;

    // 当a桶为空，就置位
    // 还有一个需要考虑的，就是在此情况下不需要退出递归。
    // 因为虽然a1为空，b和c桶还可以互倒，就不止一种情况，所以
    // 不能return，否则出来的结果会很少
    if (!a1) {
        c_bucket[c1] = true;
        // return;
    }

    // 以下为六种倒的情况，例如第一种
    // 从c桶倒入a桶
    // 假如可以全部倒入，则。。。。
    // 如果不可以全部倒入，还剩一点，则。。。。
    if (a >= a1+c1)
        dfs(a1+c1, b1, 0);
    else
        dfs(a, b1, c1-(a-a1));

    if (a >= a1+b1)
        dfs(a1+b1, 0, c1);
    else
        dfs(a, b1-(a-a1), c1);

    if(b >= b1+c1)
        dfs(a1, b1+c1 , 0);
    else
        dfs(a1, b, c1-(b-b1));

    if(b >= a1+b1)
        dfs(0, a1+b1, c1);
    else
        dfs(a1-(b-b1), b, c1);
 
    if(c >= b1+c1)
        dfs(a1, 0, b1+c1);
    else
        dfs(a1, b-(c-c1), c);

    if(c >= a1+c1)
        dfs(0, b1, a1+c1);
    else
        dfs(a1-(c-c1), b1, c);

    return;
}

int main(void)
{
    ifstream ifile("milk3.in");
    ofstream ofile("milk3.out");
    
    ifile >> a >> b >> c;

    // 开始深搜，一开始a，b是空的，c是满的
    dfs(0, 0, c);

    bool space_flag = false;
    for (int i = 0; i != N; ++i) {
        if (c_bucket[i] && space_flag)
            ofile << " ";
        if (c_bucket[i]) {
            ofile << i;
            space_flag = true;
        }
    }
    ofile << endl;

    return 0;
}