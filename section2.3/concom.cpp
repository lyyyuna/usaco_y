/*
ID: lyyyuna
PROG: concom
LANG: C++
*/

#include <fstream>

using namespace::std;

int contr1[101][101];   // i��˾����j��˾�Ĺɷ�
int contr2[101][101];   // ���ݣ��ڱ����������㣬���ƻ�ԭ����
int max_num;            // ���˾��

void dfs(int i, int j)
{
    for (int k = 1; k <= max_num; ++k)
        // ��������ȣ��ж�i��˾��������˾�Ĺɷ�
        if (i != k && contr2[i][k] <= 50) {
            // ��j��˾���ƵĹɷݼӵ�i��˾�Ŀ�������
            contr2[i][k] = contr2[i][k] + contr1[j][k];
            // ����󣬷���i��˾����k��˾
            // ��ô���������������ж�i��˾���Ƶ�k��˾���Ƿ��б�i���ƵĹ�˾
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
        // max_num ����һ���м�����˾
        if (max_num < company1)
            max_num = company1;
        if (max_num < company2)
            max_num = company2;
    }

    for (int i = 1; i <= max_num; ++i)
        for (int j = 1; j <= max_num; ++j)
            // �ж�i��˾�Ƿ����j
            if (contr2[i][j] > 50)
                // �����������ж�i�����Ƶ�j��˾����Щ��˾���Ƿ�i��˾����
                // 
                dfs(i, j);

    for (int i = 1; i <= max_num; ++i)
        for (int j = 1; j <= max_num; ++j)
            if (i != j && contr2[i][j]>50)
                ofile << i << " " << j << endl;

    return 0;
}