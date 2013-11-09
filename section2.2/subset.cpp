/*
Id：lyyyuna
PROG: subset
LANG: C++
*/

#include <fstream>

using namespace::std;

int main(void)
{
    ifstream ifile("subset.in");
    ofstream ofile("subset.out");

    int num;
    ifile >> num;

    long long f[10001]={0};
    int sum;
    sum = (num*(num+1))/2;
    // 奇数不用考虑
    if (sum % 2 == 1) {
        ofile << 0 << endl;
        return 0;
    }

    f[0] = 1;
    // 之所以用一维数组，是因为 第i个表达式，只依赖与i-1个表达式，与第i个无关，
    // 也就没有必要开个二维数组了
    for (int i = 1; i <= num; ++i)
        // j < i就不用再循环了，因为反正不变
        for (int j = sum/2; j >= i; --j)
            f[j] += f[j-i];
    // 注意除以2，a==b b==a 是一种情况
    ofile << f[sum/2] / 2 << endl;

    return 0;
}