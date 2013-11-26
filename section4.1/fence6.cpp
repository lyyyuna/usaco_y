/*
ID: lyyyuna
PROG: fence6
LANG: C++
*/

#include <fstream>
#include <cstring>

using namespace::std;

int con[101][2][9];
// x y z      x是哪一条边的编号，y是哪个端点，z是端点连着的边
// 例如[5][1][2] 5号边的1端点连着的第2（3）个边
// 整个值表示连着的边的编号
// con[][][0] 是顺便用来存储端点相连边的个数
int len[101];
bool link[101][101]; // 存储x，y   两条边是否相连，而且顺序是，x的1端点连着y的0端点
                    // 0x10y1
bool sideflag[101];
int start_side;
int min_len = 939349;

// 传入 边的编号  边的起始端点号  已经累加的长度
void dfs(int deep, int endpoint, int length)
{
    // 剪枝
    if (length > min_len) return;

    // deep这条边，考虑另一端点的连线情况
    for (int i = 1; i <= con[deep][1-endpoint][0]; ++i) {
        int now_side = con[deep][1-endpoint][i];
        // 找到now_side这条边，和deep边相连的 端点号
        int con_point = link[now_side][deep];
        // 和起始边相同，说明走了一圈，构成了一个多边形
        if (start_side == now_side) {
            if (length < min_len)
                min_len = length;

            return ;
        }

        if (!sideflag[now_side]) {
            sideflag[now_side] = true;
            dfs(now_side, con_point, length+len[now_side]);
            // 回溯
            sideflag[now_side] = false;
        }
    }
}

int main(void)
{
    ifstream ifile("fence6.in");
    ofstream ofile("fence6.out");

    int total;
    ifile >> total;
    for (int i = 1; i <= total; ++i) {
        int x;
        ifile >> x;
        ifile >> len[x] >> con[x][0][0] >> con[x][1][0];
        for (int j = 1; j <= con[x][0][0]; ++j)
            ifile >> con[x][0][j];
        for (int j = 1; j <= con[x][1][0]; ++j) {
            ifile >> con[x][1][j];
            link[x][ con[x][1][j] ] = true;
        }
    }

    for (int i = 1; i <= total; ++i) {
        memset(sideflag, 0, sizeof(sideflag));
        // 记录起始边
        start_side = i;
        dfs(i, 0, len[i]);
    }

    ofile << min_len << endl;
    
    return 0;
}