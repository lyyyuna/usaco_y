/*
ID: lyyyuna
PROG: crypt1
LANG: C++
*/

#include <fstream>

using namespace::std;

const int N = 10;
bool number[N] = {false};

bool isDigit(int a, int b)
{
    while(b--) {
        if (!number[a%10] || a == 0)
            return false;
        a /= 10;
    }

    if (a != 0)
        return false;

    return true;
}

bool isCryp(int i, int j)
{
    if (!isDigit(i, 3))
        return false;
    else if (!isDigit(j, 2))
        return false;
    else if (!isDigit(i*j, 4))
        return false;
    else if (!isDigit(i*(j%10), 3))
        return false;
    else if (!isDigit(i*(j/10), 3))
        return false;

    return true;
}

int main(void)
{
    ifstream ifile("crypt1.in");
    ofstream ofile("crypt1.out");
    
    int n, num;
    ifile >> n;
    for (int i = 0; i != n; ++i) {
        ifile >> num;
        number[num] = true;
    }

    int sum(0);
    for (int i = 100; i != 1000; ++i)
        for (int j = 10; j != 100; ++j) {
            if (isCryp(i, j))
                sum++;
        }
    ofile << sum << endl;

}