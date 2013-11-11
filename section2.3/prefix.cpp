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
    // 记下每个primitive
    while (str1 != ".") {
        str[++index] = str1;
        ifile >> str1;
    }
    // 输入S
    string core = "", temp;
    while(ifile>>temp)
        core += temp;

    int len = core.length();
    int max_length(0);
    // 开始遍历
    for (int i = 0; i < len; ++i) {
        // 对每个primitive检查
        for (int j = 1; j <= index; ++j) {
            // 如果长度+i超过，说明不对
            if (i + str[j].length() > len)
                continue;
            else {
                bool flag = false;
                // 对每个字母检查
                for (int k = 0; k < str[j].length(); ++k)
                    if (core[i+k] != str[j][k]) {
                        flag = true;
                        break;
                    }
                // 标志位
                // 说明没有到最后不匹配的情况
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