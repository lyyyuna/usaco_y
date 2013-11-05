/*
ID: lyyyuna
PROG: ariprog
LANG: C++
*/

#include <fstream>

using namespace::std;

const int N = 250*250*2+1;

int main(void)
{
    ifstream ifile("ariprog.in");
    ofstream ofile("ariprog.out");
    
    int n, m;
    ifile >> n >> m;
    int max;
    max = 2*m*m;

    // �����е�˫ƽ������ǳ���
    // ������������Ӧ���� 250*250*2
    bool allnumber[N]={false};
    for (int i = 0; i <= m; ++i)
        for (int j = 0; j <= i; ++j)
            allnumber[i*i+j*j] = true;

    // ������������洢���е�˫ƽ����
    int bisquares[N]={0};
    int b_num(0);
    for (int i = 0; i <= max; ++i)
        if (allnumber[i])
            bisquares[++b_num] = i;

    // �ȴ�b����, ��ʼ��������������Ͳ�����������
    bool flag(false);
    for (int b = 1; b*(n-1) <= max; ++b)
        // һ��b_num��������һ�������ܳ���b_num-n+1
        // ��Ҫ��֤��n����������max
        for (int i = 1; i <= b_num-n+1 && bisquares[i]+(n-1)*b<=max; ++i) {
            int a = bisquares[i];
            int j = n-1;
            for (;j>=1; --j) {
                if (!allnumber[a+j*b])
                    break;
            }
            if (!j) {
                flag = true;
                ofile << a << " " << b << endl;
            }
        }

    if (!flag) 
        ofile << "NONE" << endl;

    return 0;
}