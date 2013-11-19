/*
ID: lyyyuna
PROG: contact
LANG: C++
*/

#include <fstream>
#include <map>
#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>

using namespace::std;

bool cmp(const pair<string, int> &a, const pair<string, int> &b)
{
    if (a.second > b.second)
        return true;
    if (a.second < b.second)
        return false;
    int an = a.first.size();
    int bn = b.first.size();
    if (an < bn)
        return true;
    if (an > bn)
        return false;
    return a.first < b.first;
}

int main(void)
{
    ifstream ifile("contact.in");
    ofstream ofile("contact.out");
    int A, B, N;
    ifile >> A >> B >> N;
    string str="";
    string line;
    while(getline(ifile, line))
        str += line;
    
    map <string, int> mp;
    for (int i = A; i <= B; ++i) {
        for (int j = 0; j+i<=str.size(); ++j) {
            mp[str.substr(j, i)] ++;
        }
    }

    map <string, int>::iterator mapit = mp.begin();
    vector <pair<string, int> > vt;
    while (mapit != mp.end()) {
        vt.push_back(make_pair(mapit->first, mapit->second));
        mapit ++;
    }
    sort(vt.begin(), vt.end(), cmp);

    int num(0);
    int old(-1);
    int total(0);
    int counter(0);
    while (num < vt.size()) {
        if (vt[num].second != old) {
            if (total == N)
                break;
            if (total != 0)
                ofile << endl;
            ++total;
            counter = 0;
            ofile << vt[num].second << endl
                << vt[num].first;
            old = vt[num++].second;
        }
        else {
            counter++;
            if (counter%6 == 0) {
                ofile << endl;
                ofile << vt[num].first;
            }
            else ofile << " " << vt[num].first;
            num ++;
        }
    }

    ofile << endl;

    return 0;
}