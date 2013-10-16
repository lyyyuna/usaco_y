/*
ID: lyyyuna
LANG: C++
PROG: gift1
*/
/*#include <fstream>
#include <string>
#include <vector>

using namespace::std;

const int NP = 15; // different from c

vector<string> names(NP);
int money[NP];;
int np;

inline int find(string s)
{
    for (int i = 0; i != np; ++i)
        if (s == names[i])
            return i;
    return -1;
}

int main(void)
{
    ifstream ifile("gift1.in");
    ofstream ofile("gift1.out");
    // read total number
    ifile >> np;
    // input all names
    for (int i = 0; i != np; ++i)
        ifile >> names[i];
    // 
    for (int i = 0; i != np; ++i) {
        string name;
        int sum, n;
        ifile >> name >> sum >> n;
        if (n == 0)
            continue;
        money[find(name)] += sum%n;
        money[find(name)] -= sum;

        for (int i = 0; i != n; ++i) {
            ifile >> name;
            money[find(name)] += sum/n;
        }
    }

    for (int i = 0; i != np; ++i)
        ofile << names[i] << " " << money[i] << endl;

    return 0;
}*/
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace::std;

int main(void)
{
    ifstream ifile("gift1.in");
    ofstream ofile("gift1.out");
    map <string, int> person;
    vector <string> names;
    string name;
    int np;
    ifile >> np;

    for (int i = 0; i != np; ++i) {
        ifile >> name;
        names.push_back(name);
        person[name] = 0;
    }
    for (int i = 0; i != np; ++i) {
        int sum, n;
        ifile >> name >> sum >> n;
        if (n == 0)
            continue;
        person[name] += sum%n;
        person[name] -= sum;

        for (int i = 0; i != n; ++i) {
            ifile >> name;
            person[name] += sum/n;
        }
    }

    for (int i = 0; i != np; ++i)
        ofile << names[i] << " " << person[names[i]] << endl;

    return 0;
}