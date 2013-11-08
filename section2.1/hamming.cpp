/*
ID: lyyyuna
PROG: hamming
LANG: C++
*/

#include <fstream>

using namespace::std;

int N, B, D;

int hamming(int a, int b)
{
    int count(0);
    for (int i = 0; i != B; ++i) {
        if ( ((a>>i)&1) != ((b>>i)&1))
            count++;
    }
    return count;
}

int main(void)
{
    ifstream ifile("hamming.in");
    ofstream ofile("hamming.out");

    ifile >> N >> B >> D;

    int total(1);
    int list[2<<8-1];

    list[0] = 0;
    for (int i=1; i<(1<<B); ++i) {
        if (total > N)
            break;
        bool flag=true;
        for (int j = 0; j != total; ++j) {
            if (hamming(list[j],i) < D) {
                flag = false;
                break;
            }
        }
        if (flag == true) {
            ///total++;
            list[total++] = i;
        }
    }

    for (int i = 0; i < N-1; ++i)
        ofile << list[i] << ( ((i+1)%10==0)?"\n":" ");
    ofile << list[N-1] << endl;

    return 0;
}