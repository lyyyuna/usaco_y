/*
ID: lyyyuna
PROG: nocows
LANG: C++
*/

#include <fstream>

using namespace::std;

int table[101][201];    // ������¼��i�� j��Ԫ�ص� 
int smalltrees[101][201];

int main(void)
{
    ifstream ifile("nocows.in");
    ofstream ofile("nocows.out");

    int N, K;
    ifile >> N >> K;
    // ��
    table[1][1] = 1;
    // �ӵڶ��㿪ʼ
    for (int i = 2; i <= K; ++i) {
        // ��Ϊ������һ���������Һ��Ӳ���2����0������ֻҪ+2
        for (int j = 1; j <= N; j += 2)
            // ������k�����ұ��� j-k-1 ����
            for (int k = 1; k <= j-1-k; k += 2) {
                int factor(0);
                // �����ظ����㣬����k����ֻҪ���㵽 k <= j-k-1 ��Ϊֹ��
                // ����������ظ��ġ����� ���j-k-1 �ұ�k����ֻҪ����2������ټ���һ��
                // �� k == j-k-1���Ͳ����ظ��ˣ���������һ��
                if (k != (j-1-k))
                    factor = 2;
                else 
                    factor = 1;
                /*
                table[i][j] := smalltrees[i-2][k]*table[i-1][j-1-k];
                  // ���������С��i-1�����������Ϊi-1
                table[i][j] := table[i-1][k]*smalltrees[i-2][j-1-k];
                  // ���������Ϊi-1�����������С��i-1
                table[i][j] := table[i-1][k]*table[i-1][j-1-k];
                  // ����������ȶ�Ϊi-1 
                */
                table[i][j] += factor*(smalltrees[i-2][k] * table[i-1][j-k-1]
                            + table[i-1][k] * smalltrees[i-2][j-k-1]
                            + table[i-1][k] * table[i-1][j-k-1]);
                // if (k != j-1-k)
                //    table[i][j] *= 2;
                table[i][j] %= 9901;
            }
        
        // �������������smalltrees�ģ�
        // ���������С�� i-1 �����
        for (int k = 0; k <= N; ++k) {
            smalltrees[i-1][k] += table[i-1][k] + smalltrees[i-2][k];
            smalltrees[i-1][k] %= 9901;
        }
    }

    ofile << table[K][N] << endl;

    return 0;
}