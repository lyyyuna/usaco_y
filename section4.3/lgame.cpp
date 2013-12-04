/*
ID: lyyyuna
PROG: lgame
LANG: C++
*/

#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>

using namespace::std;

map<char, int> value;
map<string, int> dict;

int calcul(string word)
{
    int res = 0;
    for (int i = 0; i < word.size(); ++i)
        res += value[ word[i] ];
    return res;
}

int main(void)
{
    ifstream ifile("lgame.dict");
    value['q'] = 7; value['w'] = 6; value['e'] = 1; value['r'] = 2;
    value['t'] = 2; value['y'] = 5; value['u'] = 4; value['i'] = 1;
    value['o'] = 3; value['p'] = 5; value['a'] = 2; value['s'] = 1;
    value['d'] = 4; value['f'] = 6; value['g'] = 5; value['h'] = 5;
    value['j'] = 7; value['k'] = 6; value['l'] = 3; value['z'] = 7;
    value['x'] = 7; value['c'] = 4; value['v'] = 6; value['b'] = 5;
    value['n'] = 2; value['m'] = 5;

    string word;
    ifile >> word;
    while (word != ".") {
        dict[word] = calcul(word);
        ifile >> word;
    }
    dict[""] = 0;

    ifstream ifile1("lgame.in");
    ofstream ofile("lgame.out");
    string word1;
    ifile1 >> word1;

    int len = word1.size();
    sort(word1.begin(), word1.end());
    int max_len = 0;
    vector<string> ans;
    do {
        for (int i = 1; i <= len; ++i) {
            for (int j = i; j <= len; ++j) {
                // ���ŷֿ������ַ���
                int a = dict[ word1.substr(0, i) ];
                int b = dict[ word1.substr(i, j-i) ];

                // i==j ˵�����ֿ�����ĿҪ��ǰ�����ҪС�ں������
                if ( i!=j && word1.substr(0, i)>word1.substr(i, j-i) )
                    continue;
                if (!a) // û�ҵ�
                    continue;
                if ( i!=j && !b) // �ֿ����Һ�����Ǹ�û�ҵ�
                    continue;

                string nword = word1.substr(0, i);
                if ( i != j ) {
                    nword += " ";
                    nword += word1.substr(i, j-i);
                }

                // ����
                if (max_len == a+b) 
                    ans.push_back(nword);
                else if (max_len < a+b) {
                    max_len = a+b;
                    ans.clear();
                    ans.push_back(nword);
                }
            }
        }
    } while(next_permutation(word1.begin(), word1.end()));  // �������

    ofile << max_len << endl;

    // unique ȥ����ͬ���ַ���
    vector<string>::iterator end_unique = unique(ans.begin(), ans.end());
    for (vector<string>::iterator iter = ans.begin(); iter != end_unique; ++iter)
        ofile << *iter << endl;

    return 0;
}

// usaco�ĵ��Բ����ҵ�����Ҫ�ܺü�����