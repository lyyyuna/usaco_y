/*
ID: lyyyuna
PROG: sort3
LANG: C++
*/
#include <fstream>

using namespace::std;

int main()
{
    ifstream ifile("sort3.in");
    ofstream ofile("sort3.out");
    int num;
    ifile >> num;

    int count[4]={0};
    int number[1001];
    for (int i = 0; i!= num; ++i) {
        ifile >> number[i];
        count[number[i]] ++;
    }

    // cxy x位置上y的个数
    int c12 = 0, c21 = 0, c31 = 0, c32 = 0;
    for (int i = 0; i != num; ++i) {
        if (i < count[1] && number[i] == 2)
            c12++;
        else if (i >= count[1] + count[2] && number[i] != 3)
            if (number[i] == 1)
                c31++;
            else
                c32++;
        else if (i >= count[1] && i < count[1]+count[2] && number[i]==1)
            c21++;
    }
    ofile << c31+c32+(c21>c12?c21:c12) << endl;
    return 0;
}