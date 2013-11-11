/*
ID: lyyyuna
PROG: zerosum
LANG: C++
*/

#include <fstream>
#include <string>

using namespace::std;

string line(20, '0');
ifstream ifile("zerosum.in");
ofstream ofile("zerosum.out");
int num;

// deep �ݹ���ȣ�������
// sum ��ȥ���һ�����ϳɵ����֡�֮ǰ����������֮�ͣ�
// last ���һ�����ϳɵ����֡�
void dfs(int deep, int sum, int last)
{
    // �ݹ����
    if (deep == num) {
        if (sum + last == 0) {
            // 0��������������ֶ�����һ��string
            string line1(line, 0, num*2-1);
            ofile << line1 << endl;
        }
        return;
    }
    // ��ʼ����
    // ����������
    line[deep*2-1] = ' ';
    // ���ڲ����������������һ���sum���ü�last
    // lastҪ����֮ǰ�����������
    dfs(deep+1, sum, last>0? last*10+deep+1 : last*10-deep-1);

    // �ǼӺ�
    // �ⲽҲ�൱�ڻ���
    line[deep*2-1] = '+';
    // ����һ�����ϳɵ����֡����
    // ��Ϊ��ǰ�ķ�����+������deep+1Ϊ��
    dfs(deep+1, sum+last, deep+1);

    line[deep*2-1] = '-';
    // ��Ϊ��ǰ�ķ�����-������-deep-1Ϊ��
    dfs(deep+1, sum+last, -deep-1);
}

int main(void)
{

    ifile >> num;
    // ������ԭ�����ֵ���������
    // ż��λ �� ����
    // ����λ �� �ո���������
    for (int i = 0; i < num; ++i)
        line[i*2] = i + '1';

    dfs(1, 0, 1);

    return 0;
}