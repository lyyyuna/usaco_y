/*
ID: lyyyuna
PROG: fence8
LANG: C++
*/

#include <fstream>
#include <algorithm>

using namespace::std;

ifstream ifile("fence8.in");
ofstream ofile("fence8.out");
int nboard;
int nrail;
int board[50+1];
int rail[1023+1];
int sumlen[1023+1];
long long sum;
long long waste, maxwaste;

int original_i;

void dfs(int deep_rail, int index)
{
    if (deep_rail == 0) {
        for (int i = index; i < nboard; ++i) {
            if (board[i] >= rail[0]) {
                ofile << original_i+1 << endl;
                exit(0);
            }
        }
        return ;
    }

    for (int i = index; i < nboard; ++i) {
        if (board[i] >= rail[deep_rail]) {
            long long lastwaste = waste;
            board[i] -= rail[deep_rail];
            if (board[i] < rail[0] && waste+board[i] > maxwaste) {
                board[i] += rail[deep_rail];
                continue;
            }
            if (board[i] < rail[0])
                waste += board[i];
            if (rail[deep_rail] == rail[deep_rail-1])
                dfs(deep_rail-1, i);
            else
                dfs(deep_rail-1, 0);

            board[i] += rail[deep_rail];
            waste = lastwaste;
        }
    }
}

int main(void)
{
    ifile >> nboard;
    for (int i = 0; i < nboard; ++i) {
        ifile >> board[i];
        sum += board[i];
    }
    ifile >> nrail;
    for (int i = 0; i < nrail; ++i) {
        ifile >> rail[i];
    }

    sort(rail, rail+nrail);
    int index = 0;
    sumlen[0] = rail[0];
    // 找到原材料刚好不够用的情况，
    // 即木料大于原材料之和sum的情况
    // 即最多只能产出index个木料
    while (index<nrail && sumlen[index]<=sum) {
        index ++;
        sumlen[index] = sumlen[index-1] + rail[index];
    }
    nrail = index;

    for (int i = nrail-1; i>=1; --i) {
        waste = 0;  // 已经浪费的原料
        maxwaste = sum - sumlen[i]; // 最多可以浪费的原料
        original_i = i;
        dfs(i, 0);
    }

    ofile << 0 << endl;
    return 0;
}