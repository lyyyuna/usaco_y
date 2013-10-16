/*
ID: lyyyuna
LANG: C++
PROG: beads
*/

#include <fstream>
#include <string>
using namespace::std;


int main(void)
{
    ifstream ifile("beads.in");
    ofstream ofile("beads.out");
    int num1,num,max=0;
    string necklace;

    ifile >> num1; // total beads
    ifile >> necklace; // the necklace

    necklace = necklace + necklace;
    num = num1 + num1;

    for(int i = 0; i != num-1; ++i) {
        int leftIndex(i), rightIndex(i+1);
        char leftColor(necklace[leftIndex]), rightColor(necklace[rightIndex]);
        int leftNum(0), rightNum(0);

        //int j = i;
        for (; leftIndex != 0; --leftIndex) {
            if (necklace[leftIndex] == 'w')
                continue;
            else {
                if (leftColor == 'w') {
                    leftColor = necklace[leftIndex];
                    continue;
                } else if (leftColor == necklace[leftIndex])
                    continue;
                else
                    break;
            }
        }
        leftNum = i - leftIndex;

        //j = i+1;
        for (; rightIndex != num; ++rightIndex) {
            if (necklace[rightIndex] == 'w')
                continue;
            else {
                if (rightColor == 'w') {
                    rightColor = necklace[rightIndex];
                    continue;
                } else if (rightColor == necklace[rightIndex])
                    continue;
                else
                    break;
            }
        }
        rightNum = rightIndex - i-1;

        max = max > (leftNum+rightNum) ? max : (leftNum+rightNum);
    }

    if (max > num1)
        max = num1;
    ofile << max << endl;

    return 0;
}