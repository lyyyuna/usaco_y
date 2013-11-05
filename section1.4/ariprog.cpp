/*
ID: lyyyuna
PROG: ariprog
LANG: C++
*/

#include <fstream>

using namespace::std;

const int N = 250*250*2+1;

int main(void)
{
    ifstream ifile("ariprog.in");
    ofstream ofile("ariprog.out");
    
    int n, m;
    ifile >> n >> m;
    int max;
    max = 2*m*m;

    // 把所有的双平方数标记出来
    // 这个数组的总数应该是 250*250*2
    bool allnumber[N]={false};
    for (int i = 0; i <= m; ++i)
        for (int j = 0; j <= i; ++j)
            allnumber[i*i+j*j] = true;

    // 这个数组用来存储所有的双平方数
    int bisquares[N]={0};
    int b_num(0);
    for (int i = 0; i <= max; ++i)
        if (allnumber[i])
            bisquares[++b_num] = i;

    // 先从b公差, 开始遍历，这样结果就不用再排序啦
    bool flag(false);
    for (int b = 1; b*(n-1) <= max; ++b)
        // 一共b_num个数，第一个数不能超过b_num-n+1
        // 还要保证第n个数不超过max
        for (int i = 1; i <= b_num-n+1 && bisquares[i]+(n-1)*b<=max; ++i) {
            int a = bisquares[i];
            int j = n-1;
            for (;j>=1; --j) {
                if (!allnumber[a+j*b])
                    break;
            }
            if (!j) {
                flag = true;
                ofile << a << " " << b << endl;
            }
        }

    if (!flag) 
        ofile << "NONE" << endl;

    return 0;
}