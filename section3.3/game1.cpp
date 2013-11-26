/*
ID: lyyyuna
PROG: game1
LANG: C++
*/

#include <fstream>

using namespace::std;

int main(void)
{
    ifstream ifile("game1.in");
    ofstream ofile("game1.out");
    int num;
    ifile >> num;
    int number[100+1] = {0};
    for (int i = 1; i <= num; ++i)
        ifile >> number[i];

    int sum[101][101] = {0};  // ͳ�ƴ�i��j֮�䣬�������֮��
    for (int i = 1; i <= num; ++i) {
        sum[i][i] = number[i];
        for (int j = i; j <= num; ++j)
            sum[i][j] = sum[i][j-1] + number[j];
    }

    int first[101][101] = {0};  // �� i��j ����ȡ���Ǹ��˻�÷���
                                // [i][j]��ʾ��i��j�ⲿ�ֵ���ȡ���ܻ�õ�������ֺ� 
    for (int i = 1; i <= num; ++i)
        first[i][i] = number[i];
    for (int i = 1; i < num; ++i)
        for (int j = 1; j <= num-i; ++j) {
            // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            // ��Ҫע����ǣ����first������ָ��һ��ң�����ָÿ�����õ��Ǹ��ˣ���ÿ����������
            // ��Ϊ��ĿҪ�󣬶�ÿ����Ҷ�ִ�����Ų���
            // ������dp[1][n]����ָ��һ��ң���һ���Ϊ������Ϸ��һ����������
            // ����
            // f[1][2] = sum[1][2] - min(f[1][1], f[2][2])
            // f[1][3] = sum[1][3] - min(f[1][2], f[2][3])
            // [1][2]�ܵõ���������ֺͣ�[2][3]�ܵõ���������ֺ�
            // �Ƚ�ѡ��ȥ��[3]����[1]���ţ�����[1][3]
            first[j][j+i] = sum[j][j+i] - min(first[j][j+i-1], first[j+1][j+i]);
        }
    
    ofile << first[1][num] << " " 
        << sum[1][num] - first[1][num] << endl;

    return 0;
}