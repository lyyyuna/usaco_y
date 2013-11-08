/*
ID: lyyyuna
PROG: holstein
LANG: C++
*/

#include <fstream>
#include <bitset>

using namespace::std;

int main(void)
{
    ifstream ifile("holstein.in");
    ofstream ofile("holstein.out");
    
    int number_V;
    ifile >> number_V;
    int vitamine[26];
    for (int i = 0; i< number_V; ++i)
        ifile >> vitamine[i];
    int types;
    ifile >> types;
    int feeds[16][25];
    for (int i = 0; i < types; ++i)
        for (int j = 0; j < number_V; ++j)
            ifile >> feeds[i][j];

    bitset<16> minbit(0);
    // int vit[26]={0};
    int number_of_vc(16);
    for (int i = 0; i < (1<<types); ++i) {

        bitset<16> bit(i);
        int vit[26]={0};
        for (int m = 0; m < types; ++m)
            if (bit[m] == 1) {
                for (int j = 0; j < number_V; ++j)
                    vit[j] += feeds[m][j];
            }
        
        bool flag=true;
        for (int m = 0; m < number_V; ++m)
            if (vit[m] < vitamine[m])
                flag = false;

        if (flag && bit.count()<number_of_vc && bit.to_ulong() > minbit.to_ulong()) {
            number_of_vc = bit.count();
            minbit = bit;
        }
    }

    ofile << number_of_vc;
    for (int i = 0; i < types; ++i)
        if (minbit[i] == 1)
            ofile << " " << i+1;
    ofile << endl;

    return 0;
}