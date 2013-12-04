/*
ID: lyyyuna
PROG: buylow
LANG: C++
*/

#include <fstream>
#include <cstring>

using namespace::std;

ifstream ifile("buylow.in");
ofstream ofile("buylow.out");

const int MAXN = 5000+9;

struct BigNum
{
    int n[500];
    int len;
    BigNum(): len(1) {
        memset(n, 0, sizeof(n));
    }
    void operator += (const BigNum &rhs) {
        if (rhs.len > len)
            len = rhs.len;
        for (int i = 0; i < len; ++i) {
            n[i] += rhs.n[i];
            if (n[i] > 9) {
                ++n[i+1];
                n[i] -= 10;
            }
        }
        if (n[len])
            len ++;
    }
    void print() {
        for (int i = len-1; i >= 0; --i)
            ofile << n[i];
        ofile << endl;
    }
};

BigNum MaxCnt[MAXN];

int main(void)
{
    int n;
    ifile >> n;
    int s[MAXN] = {0};
    for (int i = 1; i <= n; ++i)
        ifile >> s[i];
    s[0] = 0x7fffffff;
    MaxCnt[0].len = MaxCnt[0].n[0] = 1;

    // MaxLength[i]Ϊ�Ե�i��Ϊĩβ����½����г���
    // ״̬ת�Ʒ���Ϊ MaxLength[i]=max{MaxLength[j]}+1 (j=1..i-1 and s[j]>s[i]) 
    // ��ʼ����
    // MaxLength[1]=1
    // ���ڵڶ�������½����е�����������ͨ�����һ�ʵĹ��̽����
    // ��MaxCnt[i]Ϊ��i��Ϊĩβ����½����еĸ�����
    // �������е�j(1��j��i-1)�����(s[j]>s[i] ���� MaxLength[j]+1>MaxLength[i])
    // ��MaxCnt[i]=MaxCnt[j]���������(MaxLength[j]+1==MaxLength[i])�����üӷ�ԭ��MaxCnt[i]=MaxCnt[i]+MaxCnt[j]�� 
    int MaxLength[MAXN] = {0};

    // ����1
    // ���һ��s[n]Ϊ0�����������Ʊ�������Ὣ����µ�s[n]�������ڣ���n����Ϊĩβ���������
    // ֮��������
    // ��Ϊ�˷���������ͳ�ƣ������ԭ�����������޷�ͳ����ѽ
    ++n; // ????????????????????????????????????????????????

    for (int i = 1; i <= n; ++i) {
        for (int j = i-1; j >= 0 && s[j]!=s[i]; --j) {
            // ��ǰ��ƱֵСs[i]
            if (s[j] > s[i]) {
                if (MaxLength[j]+1 > MaxLength[i]) {
                    MaxLength[i] = MaxLength[j] + 1;
                    MaxCnt[i] = MaxCnt[j];
                }
                else if (MaxLength[j]+1 == MaxLength[i])
                    MaxCnt[i] += MaxCnt[j];
            }
        }
    }

    ofile << MaxLength[n]-1 << " ";
    MaxCnt[n].print();

    return 0;
}