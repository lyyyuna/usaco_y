/*
ID: lyyyuna
PROG: prefix
LANG: C++
*/
#if 0
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
#endif

#include <iostream>
#include <fstream>
#include <set>
#include <string>

using namespace::std;

int main(void) 
{
    ifstream ifile("prefix.in");
    ofstream ofile("prefix.out");

    set<string> dic_str;
    string str1;
    int index(0);
    ifile >> str1;
    // ����ÿ��primitive
    while (str1 != ".") {
        dic_str.insert(str1);
        ifile >> str1;
    }
    // ����S
    string core = "", temp;
    while(ifile>>temp)
        core += temp;
    int len = core.length();

    int max_length(0);
    for (int i = 0; i < len; ++i) {

        for (set<string>::iterator iter = dic_str.begin(); iter != dic_str.end(); ++iter) {
            if (i + (*iter).length() > len)
                continue;
            else {
                bool flag = false;
                if (core.substr(i, (*iter).length()) != *iter)
                    flag = true;
                if (!flag) {
                    max_length = (*iter).length()+i > max_length? (*iter).length()+i : max_length;
                }
            }
        }

        if (i+1 > max_length)
            break;

    }

    ofile << max_length << endl;

    return 0;
}