/*
ID: lyyyuna
PROG: cryptcow
LANG: C++
*/

#include <fstream>
#include <string>

using namespace::std;

ifstream ifile("cryptcow.in");
ofstream ofile("cryptcow.out");

string original = "Begin the Escape execution at the Break of Dawn";
bool hashtable[1500000] = {false};
long long ori_hash;

long long BKDRhash(string &str)
{
    long seed = 131313;
    long long hash = 0;
    for (string::iterator siter = str.begin(); siter != str.end(); ++siter) {
        hash = hash*seed + *siter;
    }
    return (hash & 0x7FFFFFFF) % 1000003;
}

void substring(string &str, int c, int o, int w)
{
    string STR(str, 0, str.length()-3);
    int len = -1;

    for (int i = 0; i < c; ++i)
        STR[++len] = str[i];
    for (int i = o+1; i < w; ++i)
        STR[++len] = str[i];
    for (int i = c+1; i < o; ++i)
        STR[++len] = str[i];
    for (int i = w+1; i < str.length(); ++i)
        STR[++len] = str[i];

    str = STR;
}

bool isdfscut(const string &str)
{
    int len1 = str.length();
    int index = -1;
    // 最开始C前面的字符和以前是一样的
    while(++index<len1 && str[index]!='C')
        if (original[index] != str[index])
            return true;
    int i = 47;
    int index2 = index+1;
    index = len1;
    // 最后W后面的是一样的
    while (index>0 && str[index-1]!='W')
        if (original[--i] != str[--index])
            return true;

    len1 = index;
    index = index2;
    while (index < len1) {
        string temp_str(77, 0);
        int temp_index(0);
        // 找到一段关键字符之间的字符串
        while (++index < len1 && str[index]!='C' && str[index]!='O' && str[index]!='W')
            temp_str[temp_index++] = str[index];

        temp_index --;

        bool flag1 = false;
        bool flag2 = false;
        // 这段字符串一定在原字符串中出现过
        // 因为不管怎么换，这段都不会变
        if (index <= len1) {
            for (int i = 0; i < original.length()-temp_index; ++i) {
                flag2 = true;
                for (int j = i; j <= i+temp_index; ++j)
                    if (temp_str[j-i] != original[j]) {
                        flag2 = false;
                        break;
                    }
                // 如果flag2 是true，说明temp_str在original里面出现过
                if (flag2 == true) {
                        flag1 = true;
                        break;
                }
            }
        }

        if (flag1 == false)
            return true;
    }

    return false;
}

// true 说明找到
// false 没有找到
bool dfs(string &str, int steps)
{
    long long new_hash = BKDRhash(str);
    // 重复，出现了轮回的情况，永远不会递归出去
    if (hashtable[new_hash] == true)
        return false;
    else if (new_hash == ori_hash) {
        // 找到
        ofile << "1 " << steps << endl;
        return true;
    }
    hashtable[new_hash] = true;

    // 尝试优化，剪枝
    // 满足优化条件，直接判断当前字符串是找不到的
    if (isdfscut(str) == true)
        return false;

    string temp_str;
    for (int o = 0; o < str.length(); ++o) {
        if (str[o] == 'O') {
            for (int c = 0; c < o; ++c) {
                if (str[c] == 'C') {
                    for (int w = str.length()-1; w > o; --w) {
                        if (str[w] == 'W') {
                            temp_str = str;
                            // 去掉c o w，并且交换位置
                            substring(temp_str, c, o, w);
                            // 进入下一次
                            if (dfs(temp_str, steps+1))
                                return true;
                        }
                    }
                }
            }
        }
    }
    // 一定要加
    return false;
}

int main(void)
{
    string input_s;
    getline(ifile, input_s);
    ori_hash = BKDRhash(original);

    if (!((input_s.length()-47)%3) && !dfs(input_s, 0))
        ofile << "0 0" << endl;

    return 0;
}