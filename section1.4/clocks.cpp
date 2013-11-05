/*
ID: lyyyuna
PROG: clocks
LANG: C++
*/

#include <fstream>
#include <string>
#include <iostream>
using namespace::std;

//int movedist[9][9];
int clocks[9];
int bestmove[9];
int nbestmove;

// char *movestr[] = { "abde", "abc", "bcef", "adg", "bdefh", "cfi", "degh",
//                    "ghi", "efhi" };
/*
void mkmove(void)
{
    for (int i = 0; i != 9; ++i) {
        for (char *p = movestr[i]; *p; p++)
            movedist[i][*p - 'a'] = 3;
    }
}*/
int movedist[9][9]=
{3, 3, 0, 3, 3, 0, 0, 0, 0,
 3, 3, 3, 0, 0, 0, 0, 0, 0,
 0, 3, 3, 0, 3, 3, 0, 0, 0,
 3, 0, 0, 3, 0, 0, 3, 0, 0,
 0, 3, 0, 3, 3, 3, 0, 3, 0,
 0, 0, 3, 0, 0, 3, 0, 0, 3,
 0, 0, 0, 3, 3, 0, 3, 3, 0,
 0, 0, 0, 0, 0, 0, 3, 3, 3,
 0, 0, 0, 0, 3, 3, 0, 3, 3};

void solve_dfs(int move[], int k)
{
    /* ���ǵݹ�ĳ��� k==9 */
    if (k == 9) {
        // �жϾ������еĶ���֮���Ƿ�ָ����12��
        for (int i = 0; i != 9; ++i)
            if (clocks[i] % 12 != 0)
                // ������Ҫ��ĵݹ����
                return;

        // �����˵��ȫָ����12��
        // ͳ��
        int n(0);
        for (int i = 0; i != 9; ++i)
            n += move[i];
        cout << n << endl;
        // �ҵ���С
        if (nbestmove == 0 || n < nbestmove) {
            nbestmove = n;
            for (int i = 0; i != 9; ++i)
                bestmove[i] = move[i];
        }
        // ȫָ��12��ĵݹ����
        return ;
    }

    // dfs����Ҫ����·��
    for (int rep = 3; rep >= 0; --rep) {
        // ÿһ����֧˳ʱ��תrep��
        for (int i = 0; i != rep; ++i)
            for (int j = 0; j != 9; ++j)
                // �����ݹ�����9�㣬���ǵ�k��
                clocks[j] += movedist[k][j];
        move[k] = rep;

        solve_dfs(move, k+1);

        // ����
        // �ָ�ͬһ��������˳ʱ�붯��
        // ��solve_dfs֮ǰ�Ĵ����ǶԳƵ�
        for (int i = 0; i < rep; ++i)
            for (int j = 0; j != 9; ++j)
                clocks[j] -= movedist[k][j];
    }
}

int main(void)
{
    ifstream ifile("clocks.in");
    ofstream ofile("clocks.out");

    // mkmove();

    for (int i = 0; i != 9; ++i)
        ifile >> clocks[i];

    int move[9]={0};
    solve_dfs(move, 0);

    string s="";
    for (int i = 0; i != 9; ++i)
        for (int j = 0; j != bestmove[i]; ++j) {
            ofile << s << i+1;
            s = " ";
        }
    ofile << endl;
    
    return 0;
}