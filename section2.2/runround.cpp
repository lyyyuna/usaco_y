/*
ID: lyyyuna
PROG: runround
LANG: C++
*/

#include <fstream>

using namespace::std;

bool runround(long long n)
{
    long long temp = n;
    int count[10] = {0};
    int number[10] = {0};
    int index(0);
    // ����ȡ��ÿһλ����
    while (temp > 0) {
        number[index] = temp%10;
        if (number[index] == 0)
            return false;
        count[number[index]]++;
        // ���������������ֱ�ӷ���
        if (count[number[index]] > 1)
            return false;
        temp /= 10;
        index ++;
    }

    // ������һ����
    // ��Ϊ��ĿҪ�������ߵ�����ʼ
    int temp_n;
    for (int i = 0, j = index-1; i<=j; ++i, --j) {
        temp_n = number[i];
        number[i] = number[j];
        number[j] = temp_n;
    }

    // ������ĿҪ��������ȥ��
    // ��j�������Ĵ������������ܳ�������λ��
    int length = index;
    for (int i = 0,j = 0; j < length; ++j) {
        i += number[i];
        // ��
        while (i >= length)
            i -= length;
        count[number[i]] ++;
    }

    // �����������û�г��֣����߱��������Σ���˵�����������runround
    for (int i = 0; i < 10; ++i)
        if (count[i] != 0 && count[i] != 2)
            return false;

    return true;

}

int main(void)
{
    ifstream ifile("runround.in");
    ofstream ofile("runround.out");

    long long num;
    ifile >> num;
    long long i = num+1;

    // ���������+1��ʼ����
    for (; runround(i) == 0; ++i)
        ;
    ofile << i << endl;

    return 0;
}