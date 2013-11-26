/*
ID: lyyyuna
PROG: shopping
LANG: C++
*/

#include <fstream>
#include <cstring>  // for memset()

using namespace::std;

struct  arr
{
    int price;
    int product[1002];  // ��¼ÿ����Ʒ����ٸ�
}offer[102];            // ��¼�ж�����֧����ʽ
                        // �����в����и����Żݷ�ʽ�ļ�¼
                        // ����ÿ����Ʒ����һ������Ϊ����������֧����ʽ��
                        // Ҳ���ǻ�����b_lines��֧����ʽ����Ϊdp����Ĺ��ɲ���

struct  brr
{
    int productcode;    // ��Ʒ���
    int items;          // һ������ƷҪ�򼸼�
    int ori_price;        
}purchase[7];           // ��

int main(void)
{
    ifstream ifile("shopping.in");
    ofstream ofile("shopping.out");

    int s;
    // �����Żݷ���
    ifile >> s;
    for (int i = 1; i <= s; ++i) {
        int n;
        int c, k;
        ifile >> n;
        for (int j = 1; j <= n; ++j) {
            ifile >> k;
            ifile >> offer[i].product[k];
        }
        ifile >> offer[i].price;
    }
    // ���빺���嵥
    // �����嵥Ҳ��Ϊһ��֧����ʽ
    // ���磺
    // .....����
    // ��Ʒ1 1��    20
    // ��Ʒ2 1��    10
    // .....�������Żݷ�ʽ
    // ��Ʒ1 2�� ��Ʒ2 1��  30
    // .......
    // ���ߺ�Ϊ offer
    int b_lines;
    ifile >> b_lines;
    for (int i = 1; i<= b_lines; ++i) {
        ifile >> purchase[i].productcode >> purchase[i].items
            >> offer[++s].price;
        offer[s].product[purchase[i].productcode] = 1;
    }

    // DP
    int dp[6][6][6][6][6] = {0};
    memset(dp, 333, sizeof(dp));
    dp[0][0][0][0][0] = 0;
    for (int i = 1; i <= s; ++i) {
        int m1 = offer[i].product[purchase[1].productcode];
        int m2 = offer[i].product[purchase[2].productcode];
        int m3 = offer[i].product[purchase[3].productcode];
        int m4 = offer[i].product[purchase[4].productcode];
        int m5 = offer[i].product[purchase[5].productcode];
        for (int b1 = m1; b1 <= purchase[1].items; ++b1)
            for (int b2 = m2; b2 <= purchase[2].items; ++b2)
                for (int b3 = m3; b3 <= purchase[3].items; ++b3)
                    for (int b4 = m4; b4 <= purchase[4].items; ++b4)
                        for (int b5 = m5; b5 <= purchase[5].items; ++b5) {
                            // ��̬�滮
                            // Ҫô����֧����ʽ���ã�Ҫô�����ã�ѡ��֧�����ٵķ�ʽ
                            dp[b1][b2][b3][b4][b5] = min(
                                dp[b1][b2][b3][b4][b5],
                                dp[b1-m1][b2-m2][b3-m3][b4-m4][b5-m5] + offer[i].price
                                );
                        }

    }

    // output
    ofile << dp[purchase[1].items][purchase[2].items][purchase[3].items][purchase[4].items][purchase[5].items] << endl;

    return 0;
}