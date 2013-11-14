/*
ID: lyyyuna
PROG: fracdec
LANG: C++
*/

#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace::std;

const int MAXN = 100000 + 1;

int main(void)
{
    ifstream ifile("fracdec.in");
    ofstream ofile("fracdec.out");
    int N, D;
    ifile >> N >> D;

    char buf[MAXN]={0};
    sprintf(buf, "%d.", N/D);

    int record_rem[MAXN];
    for (int i = 0; i < MAXN; ++i)
        record_rem[i] = -1;

    int rem; // ��¼����
    rem = N % D;
    int i = 0;
    char Decimal[MAXN]={'\0'};
    while(true) {
        // �������Ϊ0��˵��������
        if (rem == 0) {
            // ��һ������0
            if (i == 0)
                sprintf(buf+strlen(buf), "0");
            else
                // ������ֱ��ȫ�����
                sprintf(buf+strlen(buf), "%s", Decimal);
            break;
        }
        // ˵����ǰ�����Ѿ����ֹ��ˣ�ֻҪ���ֹ�����������ȥ�϶����ظ������Բ��ü���ѭ����
        if (record_rem[rem] != -1) {
            // ����ѳ��ֵ� ������λ��
            int record_place = record_rem[rem];
            sprintf(buf+strlen(buf), "%.*s(%s)", record_place, Decimal, Decimal+record_place);
            break;
        }
        // ��¼��ǰ�������������������һλ�õ���
        record_rem[rem] = i;
        // ģ���������
        N = rem * 10;
        // ��¼���̵ĵ�ǰ��λ�� ����
        Decimal[i] = N/D + '0';
        // �����һ���������ͳ�������һ��������
        rem = N % D;
        i++;
    }

    int len = strlen(buf);
    for (int i = 0; i < len ; ++i) {
        ofile << buf[i];
        if ((i+1)%76 == 0)
            ofile << endl;
    }
    ofile << endl;

    return 0;
}