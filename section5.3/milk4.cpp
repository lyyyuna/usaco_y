/*
ID: lyyyuna
PROG: milk4
LANG: C++
*/

#include <fstream>
#include <algorithm>
#include <cstdlib>

using namespace::std;

ifstream ifile("milk4.in");
ofstream ofile("milk4.out");

int Q, P;
int pales[101]; //  ��¼ÿ��Ͱ����
int pales_buy[101]; // ��¼����������¼һ�������е�I��Ͱ�ı�ţ�
                    // ָȥ���� Ҫ����ЩͰ

int ans;

void print()
{
    ofile << ans;
    for (int i = 1; i <= ans; ++i)
        ofile << " " << pales[ pales_buy[i] ];
    ofile << endl;

    exit(0);
}

const int MAXQ = 20000+1;
void DP_check()
{
    bool dp[MAXQ] = {0};
    // ����װ�̵�pales_buy[1]����¼���ĸ�Ͱ
    // pales[pales_buy[1]] ���Ͱ�Ĵ�С
    // Ȼ�� 1*pales[pales_buy[1]]�� 2*pales[pales_buy[1]].��������Щ�̵������ǿ��������Ͱ�Ƴ�����
    for (int i = 1; i <= Q/pales[pales_buy[1]]; i++)
        dp[i*pales[pales_buy[1]]] = true;
    // ��̬�滮����������ͬ��ԭ��
    for (int i = 2; i <= ans; ++i)
        for (int j = pales[ pales_buy[i] ]; j <= Q; ++j)
            dp[j] |= dp[ j-pales[pales_buy[i]] ];

    // ˵���ܳƳ�Q���ѵ���
    if (dp[Q] == true)
        print();
}

void dfs(int deep)
{
    // i = pales_buy[deep-1]+1
    // ��һ���Ͱ����
    for (int i = pales_buy[deep-1]+1; i <= P-ans+deep; ++i) {
        // ��deep��ͰҪ�õ�iͰ
        // �����˵㣩����ָi�Ƕ�Ӧ����ԭͰ
        // pales_buy��ָȥ���� Ҫ����ЩͰ
        pales_buy[deep] = i;
        // ������ͷ��������֤
        if (deep == ans)
            DP_check();
        else
            dfs(deep+1);
    }
}

int main(void)
{
    ifile >> Q >> P;
    for (int i = 1; i <= P; ++i)
        ifile >> pales[i];

    sort(pales, pales+P);

    // ����ţ��Ͱ����Ϊ1��ʱ�����е���ϣ����û�н�����ţ��Ͱ����Ϊ2...ֱ��ţ��Ͱ����ΪP
    for (ans = 1; ans <= P; ++ans) 
        // ÿ�δ�һͰ�ѣ�ֱ��Ͱ��==ans
        dfs(1);

    return 0;
}