/*
ID: lyyyuna
PROG: runround
LANG: C++
*/

#include <fstream>

using namespace::std;

bool runround(long long n)
{
    long long temp = n;
    int count[10] = {0};
    int number[10] = {0};
    int index(0);
    // 首先取出每一位的数
    while (temp > 0) {
        number[index] = temp%10;
        if (number[index] == 0)
            return false;
        count[number[index]]++;
        // 如果有连续的数，直接返回
        if (count[number[index]] > 1)
            return false;
        temp /= 10;
        index ++;
    }

    // 把数反一反，
    // 因为题目要求从最左边的数开始
    int temp_n;
    for (int i = 0, j = index-1; i<=j; ++i, --j) {
        temp_n = number[i];
        number[i] = number[j];
        number[j] = temp_n;
    }

    // 按照题目要求跳来跳去。
    // 用j控制跳的次数，次数不能超过所有位数
    int length = index;
    for (int i = 0,j = 0; j < length; ++j) {
        i += number[i];
        // 环
        while (i >= length)
            i -= length;
        count[number[i]] ++;
    }

    // 如果该数不是没有出现，或者被数了两次，就说明这个数不是runround
    for (int i = 0; i < 10; ++i)
        if (count[i] != 0 && count[i] != 2)
            return false;

    return true;

}

int main(void)
{
    ifstream ifile("runround.in");
    ofstream ofile("runround.out");

    long long num;
    ifile >> num;
    long long i = num+1;

    // 从输入的数+1开始遍历
    for (; runround(i) == 0; ++i)
        ;
    ofile << i << endl;

    return 0;
}