/*
ID: lyyyuna
PROG: palsquare
LANG: C++
*/

#include <fstream>
#include <string>

using namespace::std;

void trans_N(int i, int base, char *arr)
{
    char sym[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int j(0);
    while ( i!= 0) {
        arr[j++] = sym[i%base];
        i /= base;
    }
    arr[j] = '\0';

    char *arr1;
    for (arr1 = arr+j-1; arr < arr1; ++arr, --arr1) {
        char temp = *arr;
        *arr = *arr1;
        *arr1 = temp;
    }
}

bool isPalsquare(char *arr)
{
    char *temp;
    int j(0);

    temp = arr;
    while (*temp++ != '\0') {
        ++j;
    }

    char *arr1;
    for (arr1=arr+j-1; arr < arr1; --arr1, ++arr) {
        if (*arr1 != *arr)
            return false;
    }
    return true;
}

int main(void)
{
    ifstream ifile("palsquare.in");
    ofstream ofile("palsquare.out");
    int base;

    ifile >> base;

    for (int i = 1; i != 300; ++i) {
        char a[100];
        char a_square[100];
        trans_N(i*i, base, a_square);
        if (isPalsquare(a_square)) {
            trans_N(i, base, a);
            ofile << a << " " << a_square << endl;
        }
    }

    return 0;
}
