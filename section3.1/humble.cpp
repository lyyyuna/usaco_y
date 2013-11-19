/*
ID: lyyyuna
PROG: humble
LANG: C++
*/

#include <fstream>
#include <climits>

using namespace::std;

const int MAXPRIME = 101;
const int MAXN = 100001;

int main(void)
{
    ifstream ifile("humble.in");
    ofstream ofile("humble.out");

    int K, N;
    ifile >> K >> N;
    int prime[MAXPRIME];
    for (int i = 0; i < K; ++i)
        ifile >> prime[i];

    long long hum[MAXN] = {0};
    int nhum(0);
    hum[nhum++] = 1;
    int prime_index[MAXPRIME];
    for (int i = 0; i < K; ++i)
        prime_index[i] = 0;

    while (nhum < N+1) {
        int min = INT_MAX;
        // ��
        for (int i = 0; i < K; ++i) {
            // prime[i] �� prime_index[i]һһ��Ӧ
            // ��ʾ ��i���������Ѿ��ۼ��ڳ������� �˵���prime_index[i]��
            /*
            ����ÿ������p Ѱ����С�ĳ���h ʹ�� h * p ����һ��������
            ȡ�����ҵ��� h * p ����С��һ������������һ������ Ϊ��ʹ������
            �죬���ǿ���Ϊÿ������ά��һ��������pindex����ʾÿ�������Ѿ���
            �����ĸ�������ÿ�ζ������￪ʼ���������ٴ�ͷ������
            */
            while ((long long)prime[i] * hum[prime_index[i]] <= hum[nhum-1])
                prime_index[i] ++;
            // ���µ�nhum����������Сֵ����
            if ((long long) prime[i] * hum[prime_index[i]] < min)
                min = prime[i] * hum[prime_index[i]];
        }
        // �����nhun������
        hum[nhum++] = min;
    }

    ofile << hum[N] << endl;

    return 0;
}