/*
ID: lyyyuna
PROG: money
LANG: C++
*/

#include <fstream>

using namespace::std;

int main(void)
{
    ifstream ifile("money.in");
    ofstream ofile("money.out");

    int V, N;
    ifile >> V >> N;

    int kind_money[25];
    for (int i = 0; i < V; ++i)
        ifile >> kind_money[i];
    
    // dp[j] Ϊ j��λ��ֵ�� ����
    long long dp[10001]={0};
    // Ϊʲôdp[0]��1����û�㶮
    dp[0] = 1;
    for (int i = 0; i < V; ++i)
        // dp[i,j] = dp[i-1,j];    ���õ�i�ֻ���
        // dp[i,j] = dp[i-1,j]+dp[i,j-kind_money[i]]    �õ�i�ֻ��ң�j>=kind_money[i]
        // ������һά�����ʡ�ռ�
        // ��Ϊ�������
        for (int j = kind_money[i]; j <= N; ++j)
            dp[j] = dp[j] + dp[j-kind_money[i]];

    ofile << dp[N] << endl;

    return 0;
}