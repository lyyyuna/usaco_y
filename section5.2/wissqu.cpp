/*
ID: lyyyuna
PROG: wissqu
LANG: C++
*/

#include <fstream>
#include <string>

using namespace::std;

ifstream ifile("wissqu.in");
ofstream ofile("wissqu.out");

char pasture[5][5];
bool hasht[5][5];
int cow[]= {0, 3, 3, 3, 4, 3};
string line[16+1];


inline bool isValid(char ch, int i, int j)
{
    return (
        pasture[i][j] != ch && 
        pasture[i-1][j] != ch &&
        pasture[i][j-1] != ch &&
        pasture[i+1][j] != ch &&
        pasture[i][j+1] != ch &&
        pasture[i+1][j+1] != ch &&
        pasture[i-1][j-1] != ch &&
        pasture[i+1][j-1] != ch &&
        pasture[i-1][j+1] != ch
        );
}

bool flag;
int num;
void dfs(int deep)
{
    if (deep >= 16) {
        num ++;
        if (flag == false) {
            for (int i = 1; i <= 16; ++i)
                ofile << line[i] << endl;
            flag = true;
        }
        return ;
    }

    for (char ch = 'A'; ch <= 'E'; ++ch) {
        for (int i = 1; i <= 4; ++i)
            for (int j = 1; j <= 4; ++j) {
                if (cow[ch-'A'+1]>0 && !hasht[i][j] && isValid(ch, i, j)) {
                    cow[ch-'A'+1] --;
                    line[deep+1] = "";
                    line[deep+1] += ch;
                    line[deep+1] += ' ';
                    line[deep+1] += char(i+'0');
                    line[deep+1] += ' ';
                    line[deep+1] += char(j+'0');
                    char tmp = pasture[i][j];
                    pasture[i][j] = ch;
                    hasht[i][j] = true;

                    dfs(deep+1);

                    cow[ch-'A'+1] ++;
                    line[deep+1] = "";
                    hasht[i][j] = false;
                    pasture[i][j] = tmp;
                } // if
            } // for j
    } // for ch
}

int main(void)
{
    for (int i = 1; i <= 4; ++i)
        for (int j = 1; j <= 4; ++j)
            ifile >> pasture[i][j];

    for (int i = 1; i <= 4; ++i)
        for (int j = 1; j <= 4; ++j) {
            if (isValid('D', i, j) == true) {
                cow[4] --;
                line[1] = "";
                line[1] += "D ";
                line[1] += char(i+'0');
                line[1] += ' ';
                line[1] += char(j+'0');
                char tmp = pasture[i][j];
                pasture[i][j] = 'D';
                hasht[i][j] = true;
                
                dfs(1);

                cow[4] ++;
                line[1] = "";
                hasht[i][j] = false;
                pasture[i][j] = tmp;
            }
        }

    ofile << num << endl;
    return 0;
}