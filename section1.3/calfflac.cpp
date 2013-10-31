/*
ID: lyyyuna
PROG: calfflac
LANG: C++
*/

#include <fstream>
#include <string>

using namespace::std;

const int MAX = 20000;

struct TEXT
{
    char ch;
    int original;
};

int main(void)
{
    //ifstream ifile("calfflac.in");
    ofstream ofile("calfflac.out");

    char fulltext[MAX];
    TEXT text[MAX];
    char ch;
    int i(0), j(0);
    FILE *fin;
    fin = fopen("calfflac.in", "r");
    while ((ch=getc(fin)) != EOF) {
        fulltext[i] = ch;
        if (isalpha(ch)) {
            text[j].ch = tolower(ch);
            text[j].original = i;
            j++;
        }
        i++;
    }
    fulltext[i] = '\0';
    text[j].ch = '\0';

    int f[MAX]={1};
    for (i = 1; i != MAX && text[i].ch!='\0'; ++i) {
        if (text[i].ch == text[i - f[i-1] - 1].ch)
            f[i] = f[i-1] + 2;
        else if (text[i].ch == text[i-1].ch)
            f[i] = 2;
        else 
            f[i] = 1;
    }

    int max(0),max_index(0);
    for(int index=0; index != i; ++index) {
        if (max < f[index]) {
            max = f[index];
            max_index = index;
        }
    }

    ofile << max << endl;
    for(int index = text[max_index - max + 1].original;
        index <= text[max_index].original;
        ++index) {
        ofile << fulltext[index];
    }
    ofile << endl;

    return 0;
}