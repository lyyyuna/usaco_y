/*
ID: lyyyuna
PROG: kimbits
LANG: C++
*/

#include <fstream>

using namespace::std;

const int MAXN = 32+1;
long long sizeofset[MAXN][MAXN];

ifstream ifile("kimbits.in");
ofstream ofile("kimbits.out");

void printbits(int nbits, int nones, long long index)
{
    if (nbits == 0)
        return;

    long long s = sizeofset[nbits-1][nones];
    if (s <= index) {
        ofile << "1";
        printbits(nbits-1, nones-1, index-s);
    }
    else {
        ofile << "0";
        printbits(nbits-1, nones, index);
    }
}

int main(void)
{
    int N, L;
    long long index;
    ifile >> N >> L >> index;

    for (int i = 0; i < MAXN; ++i) {
        sizeofset[0][i] = 1;
        sizeofset[i][0] = 1;
    }

    for (int i = 1; i < MAXN; ++i)
        for (int j = 1; j < MAXN; ++j) {
            sizeofset[i][j] = sizeofset[i-1][j-1] + sizeofset[i-1][j];
        }

    printbits(N, L, index-1);
    ofile << endl;
}
