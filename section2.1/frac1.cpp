/*
ID: lyyyuna
PROG: frac1
LANG: C++
*/

#include <fstream>
#include <map>
#include <string>

using namespace::std;

// ��һ����ת���ַ���
string n_2_s(int n)
{
    string num;
    while(n) {
        num.insert(num.begin(), n%10 + '0');
        n /= 10;
    }
    return num;
}

int main(void)
{
    ifstream ifile("frac1.in");
    ofstream ofile("frac1.out");

    int num;
    ifile >> num;

    // ��map,�߼��Ƚ����
    map<float, string> fractions;
    // �������������
    fractions[0/1] = "0/1";
    fractions[1/1] = "1/1";

    // ���Կ�������û���ж��Ƿ��ĸ���ӻ��ʵ����
    // ��Ϊ��ѭ���Ǵӷ�ĸ���������ʼ�ģ���������С������ʱ�򣬾ͻ��ԭ�������ʵ�������ǵ������˼·�Ƚ����
    // ���� 5
    // 2/4 == 0.5 ��Ȼ���ǻ���
    // ��ѭ��������ȥ���ͻ���� 1/2 == 0.5�������ͰѸղŵ� 2/4 ���ǵ���
    // ����denominator Ҫ�� num ��ʼѭ��
    for (float denominator = num; denominator>1.0; denominator -= 1) {
        for (float numerator = 1.0; numerator < denominator; numerator += 1) {
            float frac = numerator / denominator;
            string s;
            s += n_2_s(numerator);
            s.push_back('/');
            s += n_2_s(denominator);
            fractions[frac] = s;
        }
    }

    for (map<float, string>::const_iterator iter = fractions.begin();
        iter != fractions.end(); ++iter) 
        ofile << iter->second << endl;

    return 0;
}