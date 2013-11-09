/*
Id��lyyyuna
PROG: subset
LANG: C++
*/

#include <fstream>

using namespace::std;

int main(void)
{
    ifstream ifile("subset.in");
    ofstream ofile("subset.out");

    int num;
    ifile >> num;

    long long f[10001]={0};
    int sum;
    sum = (num*(num+1))/2;
    // �������ÿ���
    if (sum % 2 == 1) {
        ofile << 0 << endl;
        return 0;
    }

    f[0] = 1;
    // ֮������һά���飬����Ϊ ��i�����ʽ��ֻ������i-1�����ʽ�����i���޹أ�
    // Ҳ��û�б�Ҫ������ά������
    for (int i = 1; i <= num; ++i)
        // j < i�Ͳ�����ѭ���ˣ���Ϊ��������
        for (int j = sum/2; j >= i; --j)
            f[j] += f[j-i];
    // ע�����2��a==b b==a ��һ�����
    ofile << f[sum/2] / 2 << endl;

    return 0;
}