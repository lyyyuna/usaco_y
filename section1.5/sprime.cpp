/*
ID: lyyyuna
PROG: sprime
LANG: C++
*/

#include <fstream>

using namespace::std;

int DEEP;
ifstream ifile("sprime.in");
ofstream ofile("sprime.out");

bool isPrime(int num)
{
    if (num == 1)
        return false;
    if (num == 2)
        return true;
    for (int i = 2; i*i <= num; ++i)
        if (num%i == 0)
            return false;
    return true;
}

void dfs(int num, int deep)
{
    // 递归出口，即为所有位数都搜遍了
    if (deep > DEEP)
        return ;

    if (isPrime(num)) {
        if (deep == DEEP)
            ofile << num <<endl;
        else {
            // 每次的个位数只可能是 1 3 5 7 9
            // 偶数位不用搜了
            dfs(num*10+1, deep+1);
            dfs(num*10+3, deep+1);
            dfs(num*10+5, deep+1);
            dfs(num*10+7, deep+1);
            dfs(num*10+9, deep+1);
        }
    }
    else 
        return;
}

int main(void)
{
    ifile >> DEEP;

    // 深搜，看首位
    for (int i = 1; i <= 9; ++i) 
        dfs(i, 1);

    return 0;
}