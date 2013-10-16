/*
ID: lyyyuna
PROG: friday
LANG: C++
*/
#include <fstream>
#include <string>

using namespace::std;
// 存放每月天数
int dayofyear[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
// 存放一个星期每天各自13号的个数
int week[7] = {0};

bool isLeap(int year)
{
    if ((year%4==0 && year%100!=0) || year%400==0)
        return true;
    else
        return false;
}

void numberofdays(int nyears)
{
    // 总天数
    int sum=0;

    for (int i = 0; i != nyears; ++i) {
        if (isLeap(1900+i)) 
            dayofyear[1] = 29;
        else 
            dayofyear[1] = 28;
        for (int i = 0; i != 12; ++i) {
            week[(sum+13-1)%7]++;
            sum += dayofyear[i];
        }
    }
}

int main(void)
{
    ifstream ifile("friday.in");
    ofstream ofile("friday.out");
    int n;

    ifile >> n;
    numberofdays(n);
    ofile << week[5] << " " << week[6];
    for (int i = 0; i != 5; ++i)
        ofile << " " <<week[i];
    ofile << endl;

    return 0;
}