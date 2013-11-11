/*
ID: lyyyuna
PROG: prefix
LANG: C++
*/

#include <fstream>
#include <map>
#include <string>

using namespace::std;

int main(void) 
{
    ifstream ifile("prefix.in");
    ofstream ofile("prefix.out");

    string str[201];
    string str1;
    int index(0);
    ifile >> str1;
    // ����ÿ��primitive
    while (str1 != ".") {
        str[++index] = str1;
        ifile >> str1;
    }
    // ����S
    string core = "", temp;
    while(ifile>>temp)
        core += temp;

    int len = core.length();
    int max_length(0);
    // ��ʼ����
    for (int i = 0; i < len; ++i) {
        // ��ÿ��primitive���
        for (int j = 1; j <= index; ++j) {
            // �������+i������˵������
            if (i + str[j].length() > len)
                continue;
            else {
                bool flag = false;
                // ��ÿ����ĸ���
                for (int k = 0; k < str[j].length(); ++k)
                    if (core[i+k] != str[j][k]) {
                        flag = true;
                        break;
                    }
                // ��־λ
                // ˵��û�е����ƥ������
                if (!flag)
                    max_length = str[j].length()+i ? str[j].length()+i : max_length;
            }
        }

        if (i+1 > max_length)
            break;
    }

    ofile << max_length << endl;
    return 0;
}