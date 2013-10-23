/*
ID: lyyyuna
LANG: C++
PROG: namenum
*/

#include <fstream>
#include <string>

using namespace::std;

int main(void)
{
    ifstream ifile("namenum.in");
    ofstream ofile("namenum.out");
    ifstream dict("dict.txt");

    string word;
    char letters[] = {'2', '2', '2', '3', '3', '3', '4', '4', '4', '5', '5',
        '5', '6', '6', '6', '7', '0', '7', '7', '8', '8', '8', '9', '9',
        '9', '0'};
    string digit;
    bool flag(false);

    ifile >> digit;
    while ( dict>>word ) {
        string word2ditgit(word);
        for (int i=0; i != word.length(); ++i)
            word2ditgit[i] = letters[word[i]-'A'];
        
        if (word2ditgit == digit){
            ofile << word << endl;
            flag = true;
        }
    }

    if (flag != true)
        ofile << "NONE" << endl;

    return 0;
}