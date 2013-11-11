/*
ID: lyyyuna
PROG: concom
LANG: C++
*/

#include <fstream>

using namespace::std;

int contr1[101][101];   // i公司控制j公司的股份
int contr2[101][101];   // 备份，在备份上做运算，不破坏原数组
int max_num;            // 最大公司数

void dfs(int i, int j)
{
    for (int k = 1; k <= max_num; ++k)
        // 不和自身比，判断i公司对其他公司的股份
        if (i != k && contr2[i][k] <= 50) {
            // 将j公司控制的股份加到i公司的控制力上
            contr2[i][k] = contr2[i][k] + contr1[j][k];
            // 加完后，发现i公司控制k公司
            // 那么继续往下搜索，判断i公司控制的k公司中是否有被i控制的公司
            if (contr2[i][k] > 50)
                dfs(i, k);
        }
}

int main(void)
{
    ifstream ifile("concom.in");
    ofstream ofile("concom.out");

    int num;
    ifile >> num;
    int company1, company2;
    for (int i = 1; i <= num; ++i) {
        ifile >> company1 >> company2;
        ifile >> contr1[company1][company2];
        contr2[company1][company2] = contr1[company1][company2];
        // max_num 记下一共有几个公司
        if (max_num < company1)
            max_num = company1;
        if (max_num < company2)
            max_num = company2;
    }

    for (int i = 1; i <= max_num; ++i)
        for (int j = 1; j <= max_num; ++j)
            // 判断i公司是否控制j
            if (contr2[i][j] > 50)
                // 搜索，继续判断i所控制的j公司的那些公司，是否被i公司控制
                // 
                dfs(i, j);

    for (int i = 1; i <= max_num; ++i)
        for (int j = 1; j <= max_num; ++j)
            if (i != j && contr2[i][j]>50)
                ofile << i << " " << j << endl;

    return 0;
}