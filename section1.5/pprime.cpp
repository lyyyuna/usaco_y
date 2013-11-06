/*
ID: lyyyuna
PROG: pprime
LANG: C++
*/

#include <fstream>

using namespace::std;

// 主要就是这个函数，主动构造回文数，而不是遍历判断是否是回文数
// 首先偶数位数的 回文质数除了11 是不存在的，因为肯定能被11整除
// 接下来就是构造奇数位数的回文数
// 形如 abc
// 将构造成 abcba.
int Pal(int x)
{
    int t = x; 
    x /= 10;
    while(x>0) {
        t = t*10 + x%10;
        x /= 10;
    }
    return t;
}

bool isPrime(int x)
{
    if (x%2 == 0)
        return false;
    for (int i = 3; i*i <= x; ++i)
        if (x%i == 0)
            return false;
    return true;
}

int main (void)
{
    ifstream ifile("pprime.in");
    ofstream ofile("pprime.out");
    
    int begin, end;
    ifile >> begin >> end;
    if(begin<=5&&5<=end)
        ofile << 5 <<endl;
    if(begin<=7&&7<=end)
        ofile << 7 << endl;
    if(begin<=11&&11<=end)
        ofile << 11 << endl;
    
    int i;
    i = 10;
    while (Pal(i) < begin)
        i ++;
    while (Pal(i) <= end) {
        int j = Pal(i);
        if (isPrime(j))
            ofile << j << endl;
        i++;
    }
    return 0;
}