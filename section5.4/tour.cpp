/*
ID: lyyyuna
PROG: tour
LANG: C++
*/

/*
�ѷ��ص�·�߷�����ô����·�߾ͱ�����������ཻ�Ĵ���㵽
�յ��·�ߡ��������ǿ�����DP�����

״̬�趨
f[i,j] Ϊ�ٶ��ļ������ˣ����ߵ���i�����У����ߵ���j������
ʱ�������߹��ĳ�����Ŀ�ĺ͡�

��ʼ״̬
f[1,1]=1

״̬ת�Ʒ���
f[j,i]=f[i,j]=max{f[i,k]+1}(k��j���ڷɻ����ߣ��Լ�f[i,k]>0��
����˵����f[i,k]���߷���1<=k<j

�������ң���϶���f[j,i]=f[i,j]��

Ŀ����
�������и�֪�����ߵ��յ���ܷ��أ�������һ����max{f[i,N]}(i
��N���ڷɻ�����)�� ���û�о���������Ŀ����1�Ŀ���Ŀ��״̬����
�޷������λ��Σ����1�� 
*/
#include <fstream>
#include <cstring>
#include <map>
#include <string>

using namespace::std;

int main(void)
{
    ifstream ifile("tour.in");
    ofstream ofile("tour.out");
    int N, V;
    ifile >> N >> V;
    string s1, s2;
    map<string, int> city;
    for (int i = 1; i <= N; ++i) {
        ifile >> s1;
        city[s1] = i;
    }
    bool links[101][101]={0};
    for (int i = 1; i <= V; ++i) {
        ifile >> s1 >> s2;
        int c1 = city[s1];
        int c2 = city[s2];
        links[c1][c2] = true;
        links[c2][c1] = true;
    }

    int dp[101][101]={0};
    dp[1][1] = 1;
    for (int i = 1; i <= N; ++i)
        for (int j = i+1; j <= N; ++j) {
            dp[i][j] = -1111;
            for (int k = 1; k < j; ++k)
                // k��j��ֱ��ͨ·����dp[i][k]���н��
                // ���ܰ�dp[i][j]��������Ŷ
                if (links[k][j] && dp[i][k] && dp[i][k]>dp[i][j])
                    dp[i][j] = dp[i][k];
            dp[i][j] ++;
            dp[j][i] = dp[i][j];
        }

    int ans = 1;
    for (int i = 1; i <= N; ++i)
        if (links[i][N] && ans < dp[i][N])
            ans = dp[i][N];

    ofile << ans << endl;

    return 0;
}