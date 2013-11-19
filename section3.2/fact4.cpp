/*
ID: lyyyuna
PROG: fact4
LANG: C++
*/

#include <fstream>

using namespace::std;

int main(void)
{
    ifstream ifile("fact4.in");
    ofstream ofile("fact4.out");
    int num;
    ifile >> num;

    long last[4220+1] = {0};
    long val[4220+1] = {0};

    long count=0;
    for (int i = 1; i <= num; ++i) {
        val[i] = i;
        while (val[i] % 2 == 0) {
            val[i] /= 2;
            count ++;
        }
        while (val[i] % 5 == 0) {
            val[i] /= 5;
            count --;
        }
    }

    last[0] = 1;
    for (int i = 1; i <= num; ++i)
        last[i] = (last[i-1]*val[i]) % 10;

    for (int i = 1; i <= count; ++i)
        last[num] = (last[num]*2) % 10;

    ofile << last[num] << endl;

    return 0;
}