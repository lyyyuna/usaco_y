/*
ID: lyyyuna
PROG: zerosum
LANG: C++
*/

#include <fstream>
#include <string>

using namespace::std;

string line(20, '0');
ifstream ifile("zerosum.in");
ofstream ofile("zerosum.out");
int num;

// deep 递归深度，即数字
// sum 除去最后一个“合成的数字”之前的所有数字之和，
// last 最后一个“合成的数字”
void dfs(int deep, int sum, int last)
{
    // 递归出口
    if (deep == num) {
        if (sum + last == 0) {
            // 0不能输出，所以又定义了一个string
            string line1(line, 0, num*2-1);
            ofile << line1 << endl;
        }
        return;
    }
    // 开始深搜
    // 数字连起来
    line[deep*2-1] = ' ';
    // 由于不是运算符，所以下一层的sum不用加last
    // last要根据之前的正负情况，
    dfs(deep+1, sum, last>0? last*10+deep+1 : last*10-deep-1);

    // 是加号
    // 这步也相当于回溯
    line[deep*2-1] = '+';
    // 与上一个“合成的数字”相加
    // 因为当前的符号是+，所以deep+1为正
    dfs(deep+1, sum+last, deep+1);

    line[deep*2-1] = '-';
    // 因为当前的符号是-，所以-deep-1为负
    dfs(deep+1, sum+last, -deep-1);
}

int main(void)
{

    ifile >> num;
    // 数组是原来数字的两倍长度
    // 偶数位 放 数字
    // 奇数位 放 空格或者运算符
    for (int i = 0; i < num; ++i)
        line[i*2] = i + '1';

    dfs(1, 0, 1);

    return 0;
}