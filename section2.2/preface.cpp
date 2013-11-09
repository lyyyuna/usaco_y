/*
ID: lyyyuna
PROG: preface
LANG: C++
*/

#include <fstream>

using namespace::std;

int main(void)
{
    ifstream ifile("preface.in");
    ofstream ofile("preface.out");
    int num;
    ifile >> num;

    int I = 0;
    int V = 0;
    int X = 0;
    int L = 0;
    int C = 0;
    int D = 0;
    int M = 0;

    for (int i = 1; i <= num; ++i) {
        int k = i;
        while(k > 0) {
            if (k >= 1000) {
                k -= 1000;
                M++;
            }
            if (k>=900 && k<1000) {
                k -= 900;
                C++;
                M++;
            }
            if (k>=500 && k<900) {
                k -= 500;
                D++;
            }
            if (k>=400 && k<500) {
                k -= 400;
                C++;
                D++;
            }
            if (k>=100 && k<400) {
                k -= 100;
                C++;
            }
            if (k>=90 && k<100) {
                k -= 90;
                X++;
                C++;
            }
            if (k>=50 && k<90) {
                k -= 50;
                L++;
            }
            if (k>=40 && k<50) {
                k -= 40;
                X++;
                L++;
            }
            if (k>=10 && k<40) {
                k -= 10;
                X++;
            }
            if (k>=9 && k<10) {
                k -= 9;
                I++;
                X++;
            }
            if (k>=5 && k<9) {
                k -= 5;
                V++;
            }
            if (k>=4 && k<5) {
                k -= 4;
                I++;
                V++;
            }
            if (k>=1 && k<4) {
                k -= 1;
                I++;
            }
        }
    }

    if (I)
        ofile << "I " << I << endl;
    if (V)
        ofile << "V " << V << endl;
    if (X)
        ofile << "X " << X << endl;
    if (L)
        ofile << "L " << L << endl;
    if (C)
        ofile << "C " << C << endl;
    if (D)
        ofile << "D " << D << endl;
    if (M)
        ofile << "M " << M << endl;

    return 0;
}