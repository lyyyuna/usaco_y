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
    if (deep > DEEP)
        return ;

    if (isPrime(num)) {
        if (deep == DEEP)
            ofile << num <<endl;
        else {
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

    for (int i = 1; i <= 9; ++i) 
        dfs(i, 1);

    return 0;
}