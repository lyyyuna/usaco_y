/*
ID: lyyyuna
LANG: C++
PROG: ride
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace::std;

int main(void)
{
    long long number1(1), number2(1);
    ifstream ifile("ride.in");
    ofstream ofile("ride.out");
    string line1, line2;

    getline(ifile, line1);
    for (string::size_type index = 0; index != line1.size(); ++index){
        number1 *= line1[index] - 65 + 1;
    }
	
    getline(ifile, line2);
    for (string::size_type index = 0; index != line2.size(); ++index){
        number2 *= line2[index] - 65 + 1;
    }

    if (number1%47 == number2%47)
        ofile << "GO"<<endl;
    else
        ofile << "STAY"<<endl;

    return 0;
}