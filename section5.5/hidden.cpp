/*
ID: lyyyuna
PROG: hidden
LANG: C++
*/

#include <fstream>
#include <cstring>
#include <string>

using namespace::std;

int main(void)
{
    ifstream ifile("hidden.in");
    ofstream ofile("hidden.out");
    int N;
    ifile >> N;
    string tmp;
    string str;
    while( ifile >> tmp)
        str += tmp;

    str += str;

    int i = 0;
    int j = 1;
    int k;
    while (j < N) {
        for (k = 0; k < N; ++k)
            if (str[i+k] != str[j+k])
                break;
        if (k == N)
            break;
        if (str[i+k] > str[j+k])
            i += k+1;
        else
            j += k+1;

        if (j == i) 
            j ++;
    }

    ofile << i << endl;
}
