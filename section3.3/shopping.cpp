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
    int product[1002];  // 记录每个商品买多少个
}offer[102];            // 记录有多少种支付方式
                        // 程序中不仅有各种优惠方式的记录
                        // 还把每种商品各买一件，作为各个独立的支付方式。
                        // 也就是还多了b_lines种支付方式，作为dp运算的构成部分

struct  brr
{
    int productcode;    // 商品编号
    int items;          // 一共该商品要买几件
    int ori_price;        
}purchase[7];           // 买

int main(void)
{
    ifstream ifile("shopping.in");
    ofstream ofile("shopping.out");

    int s;
    // 读入优惠方案
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
    // 读入购物清单
    // 购物清单也做为一种支付方式
    // 例如：
    // .....购买
    // 商品1 1件    20
    // 商品2 1件    10
    // .....以下是优惠方式
    // 商品1 2件 商品2 1件  30
    // .......
    // 两者合为 offer
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
                            // 动态规划
                            // 要么这种支付方式采用，要么不采用，选择支付最少的方式
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