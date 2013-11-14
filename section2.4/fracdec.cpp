/*
ID: lyyyuna
PROG: fracdec
LANG: C++
*/

#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace::std;

const int MAXN = 100000 + 1;

int main(void)
{
    ifstream ifile("fracdec.in");
    ofstream ofile("fracdec.out");
    int N, D;
    ifile >> N >> D;

    char buf[MAXN]={0};
    sprintf(buf, "%d.", N/D);

    int record_rem[MAXN];
    for (int i = 0; i < MAXN; ++i)
        record_rem[i] = -1;

    int rem; // 记录余数
    rem = N % D;
    int i = 0;
    char Decimal[MAXN]={'\0'};
    while(true) {
        // 如果余数为0，说明除尽了
        if (rem == 0) {
            // 第一个就是0
            if (i == 0)
                sprintf(buf+strlen(buf), "0");
            else
                // 除尽，直接全部输出
                sprintf(buf+strlen(buf), "%s", Decimal);
            break;
        }
        // 说明当前余数已经出现过了，只要出现过，继续算下去肯定会重复，所以不用继续循环了
        if (record_rem[rem] != -1) {
            // 这个已出现的 曾经的位置
            int record_place = record_rem[rem];
            sprintf(buf+strlen(buf), "%.*s(%s)", record_place, Decimal, Decimal+record_place);
            break;
        }
        // 记录当前算出来的余数，是在哪一位得到的
        record_rem[rem] = i;
        // 模拟除法运算
        N = rem * 10;
        // 记录下商的当前那位的 数字
        Decimal[i] = N/D + '0';
        // 算出下一个余数，和除法运算一样，笔算
        rem = N % D;
        i++;
    }

    int len = strlen(buf);
    for (int i = 0; i < len ; ++i) {
        ofile << buf[i];
        if ((i+1)%76 == 0)
            ofile << endl;
    }
    ofile << endl;

    return 0;
}