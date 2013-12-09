/*
ID: lyyyuna
PROG: charrec
LANG: C++
*/

#include <fstream>
#include <climits>

using namespace::std;

const char letter[30] = "  abcdefghijklmnopqrstuvwxyz";
char font[27+1][20+1][20+1];
    char data[1201][21];
    int diff[27+1][21][1201];
    int cost[1201][4];
    int from[1201][4]; //  记录 
    int dp[1201] = {0};
    int g[1201] = {0};
    int letter_i[1201]={0};

int main(void)
{
    ifstream ifont("font.in");
    int N;

    ifont >> N;
    // getchar();
    for (int i = 1; i <= 27; ++i)
        for (int j = 1; j <= 20; ++j)
            for (int k = 1; k <= 20; ++k)
                ifont >> font[i][j][k];

    ifstream ifile("charrec.in");
    ofstream ofile("charrec.out");

    ifile >> N;
    // getchar();
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= 20; ++j)
            ifile >> data[i][j];

    // 求出diff

    for (int i = 1; i <= 27; ++i)
        for (int j = 1; j <= 20; ++j)
            for (int k = 1; k <= N; ++k) {
                diff[i][j][k] = 0;
                for (int p = 1; p <= 20; ++p)
                    diff[i][j][k] += (int)(data[k][p] != font[i][j][p]);
            }

    // 求出cost

    for (int i = 1; i <= N; ++i) {
        cost[i][1] = cost[i][2] = cost[i][3] = INT_MAX;

        // 正好20行
        if (i+19 <= N) {
            for (int j = 1; j <= 27; ++j) {
                int total = 0;
                for (int k = 1; k <= 20; ++k)
                    total += diff[j][k][i+k-1];
                if (total < cost[i][2]) {
                    cost[i][2] = total;
                    from[i][2] = j;
                }
            }
        }

        // 19
        if (i+18 <= N) {
            for (int j = 1; j <= 27; ++j) {
                int total = 0;
                for (int k = 2; k <= 20; ++k)
                    total += diff[j][k][i+k-2];
                if (total < cost[i][1]) {
                    cost[i][1] = total;
                    from[i][1] = j;
                }
                for (int k = 2; k <=20; ++k) {
                    total += diff[j][k-1][i+k-2];
                    total -= diff[j][k][i+k-2];
                    if (total < cost[i][1]) {
                        cost[i][1] = total;
                        from[i][1] = j;
                    }
                }
            }
        }

        // 21
        if (i+20 <= N) {
            for (int j = 1; j <= 27; ++j) {
                int total = diff[j][1][i];
                for (int k =2; k <= 20; ++k)
                    total += diff[j][k][i+k];
                if (total < cost[i][3]) {
                    cost[i][3] = total;
                    from[i][3] = j;
                }
                for (int k = 2; k <= 20; ++k) {
                    total += diff[j][k][i+k-1];
                    total -= diff[j][k][i+k];
                    if (total < cost[i][3]) {
                        cost[i][3] = total;
                        from[i][3] = j;
                    }
                }
            }
        }
    }


    for (int i = 1; i <= N; ++i)
        dp[i] = INT_MAX;
    for (int i = 19; i <= N; ++i) {
        if (i>=19 && dp[i-19]<INT_MAX && dp[i-19]+cost[i-18][1]<dp[i]) {
            dp[i] = dp[i-19] + cost[i-18][1];
            g[i] = 19;
        }

        if (i>=20 && dp[i-20]<INT_MAX && dp[i-20]+cost[i-19][2]<dp[i]) {
            dp[i] = dp[i-20] + cost[i-19][2];
            g[i] = 20;
        }

        if (i>=21 && dp[i-21]<INT_MAX && dp[i-21]+cost[i-20][3]<dp[i]) {
            dp[i] = dp[i-21] + cost[i-20][3];
            g[i] = 21;
        }
    }



    int index = 0;
    for (int i = N; i; i-= g[i]) 
        letter_i[++index] = from[ i-g[i]+1 ][ g[i]-18 ];

    for (int i=index; i>0; --i)
        ofile << letter[ letter_i[i] ];
    ofile << endl;

    return 0;

}
