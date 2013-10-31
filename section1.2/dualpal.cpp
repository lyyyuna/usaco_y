/*
ID: lyyyuna
PROG: dualpal
LANG: C++
*/

#include <fstream>
#include <string>

using namespace::std;

bool isPalindromel(int num, int base)
{
    char s[100];
    int j(0);
    while (num!=0) {
        s[j] = num%base;
        num /= base;
        ++j;
    }
    --j;
    for (int i=0; i < j; ++i, --j) {
        if (s[i] != s[j])
            return false;
    }

    return true;
}

bool isDualpal(int s)
{
    int j = 0;
    for (int i = 2; i != 11; ++i) {
        if (isPalindromel(s, i)) {
            j++;
            if (j == 2)
                return true;
        }
    }
    return false;
}
int main(void)
{
    ifstream ifile("dualpal.in");
    ofstream ofile("dualpal.out");
    int N, S;

    ifile >> N >> S;

    int n(0);
    while ( n != N) {
        ++S;
        if (isDualpal(S)) {
            ofile << S << endl;
            n++;
        }
    }

    return 0;
}