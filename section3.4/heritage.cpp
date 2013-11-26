/*
ID: lyyyuna
PROG: heritage
LANG: C++


#include <fstream>
#include <string>

using namespace::std;

string infixorder;
string preorder;
int k;
ifstream ifile("heritage.in");
ofstream ofile("heritage.out");

void makepost(int beg, int end)
{
    if (beg > end) return ;
    for (int i = beg; i <= end; ++i) {
        if (infixorder[i] == preorder[k]) {
            k ++;
            makepost(beg, i-1);
            makepost(i+1, end);
            ofile << infixorder[i];
            return;
        }
    }
}

int main(void)
{
    ifile >> infixorder >> preorder;

    makepost(0, infixorder.size()-1);

    ofile << endl;
    return 0;
}*/

#include <iostream>
#include <cstdio>

using namespace::std;
    union A
    {
        int i;
        char x[2];
    }a;
int main(void)
{

    
    a.x[0] = 10;
    a.x[1] = 1;
    printf("%d", a.i);
    return 0;
}
