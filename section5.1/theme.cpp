/*
ID: lyyyuna
PROG: theme
LANG: C++
*/

#include <fstream>

using namespace::std;

const int MAXN = 5000+1;

int main(void)
{
    ifstream ifile("theme.in");
    ofstream ofile("theme.out");

    int a[MAXN]={0};
    int N, p, q;
    ifile >> N >> p;
    for (int i = 1; i <= N; ++i) {
        ifile >> q;
        a[i] = q-p;
        p = q;
    }
    a[N] = 0x7fffff;

    int len = 0;
    int maxlen = 0;
    for (int i = 1; i < N-maxlen; ++i)
        for (int j = i+maxlen; j <= N-maxlen; ++j)
            if (a[i] == a[j]) {
                len = 1;
                while (a[i+len] == a[j+len] && j>i+len+1)
                    len++;
                if (len > maxlen)
                    maxlen = len;
            }

    if (maxlen < 4)
        maxlen = -1;
    ofile << maxlen+1 << endl;

    return 0;
}