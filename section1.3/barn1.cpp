/*
ID: lyyyuna
PROG: barn1
LANG: C++
*/
#include <fstream>
#include <algorithm>

using namespace::std;

const int MAX = 200;

int main()
{
    ifstream ifile("barn1.in");
    ofstream ofile("barn1.out");
    int M, S, C;

    ifile >> M >> S >> C;

    int a[MAX];
    for (int i = 0; i != C; ++i)
        ifile >> a[i];
    sort(a, a+C);

    int b[MAX];
    for (int i = 0; i != C-1; ++i)
        b[i] = a[i+1] - a[i] - 1;
    sort(b, b+C-1);

    int total_length;
    total_length = a[C-1] - a[0] + 1;
    for (int i=C-2, j=1; i>=0&&j!=M; --i,++j) {
        total_length -= b[i];
    }

    ofile << total_length << endl;
}