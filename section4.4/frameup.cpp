/*
ID: lyyyuna
PROG: frameup
LANG: C++
*/

/*
由题意可知，不存在一个矩形的一条边被完全覆盖，所以我们可以计算出矩形
的坐标。 读入时记录矩形的每个点中最小x1，最小y1，最大x2，最大y2。可
知左上角 (x1,y1) 右下角 (x2,y2) 右上角 (x2,y1) 左下角 (x1,y2)。

查找该矩形A边上，非该矩形的字母B，即覆盖矩形A被矩形B覆盖。建立一条有
向边B->A，表示B是A的必要条件。然后进行拓扑排序，搜索求所有的拓扑序
列，并排序输出。

注意，该题中的字母可能不连续，不要直接for(i='A';i<='Z';i++)。 
*/

#include <fstream>
#include <cstring>

using namespace::std;

ifstream ifile("frameup.in");
ofstream ofile("frameup.out");

const int MAXN = 50+1;
char map[MAXN][MAXN];   // 记录原图情况
bool hasht[MAXN];       // 记录这个字母是否出现过
bool cover[MAXN][MAXN]; // 记录[i][j]  j覆盖i
int depth[MAXN];        // 记录这个字母的覆盖深度

// 记录每个字母上下左右极限值
int up[MAXN]; int down[MAXN];
int leftt[MAXN]; int rightt[MAXN];

// 记录是否被访问过
bool isVisit[MAXN];

// 总的出现字母数
int total;
char result[MAXN];

void dfs(int x, int deep)
{
    result[deep] = x;
    
    // 递归出口
    if (deep >= total) {
        for (int i = 1; i <= total; ++i) {
            char c = result[i]+'A'-1;
            ofile << c;
        }
        ofile << endl;
        return ;
    }

    // 深度为0，说明这个字母矩阵已经浮到最上层，或本来就在最上层
    if (depth[x] == 0) {
        // 每个覆盖x 的层 试着上浮一层
        for (int i = 1; i <= 26; ++i)
            if (cover[x][i] == true)
                depth[i] --;

        for (int i = 1; i <= 26; ++i)
            // 如果有其他层浮到了最上面
            // 则深入
            if (depth[i] == 0 && !isVisit[i] && hasht[i]) {
                isVisit[i] = true;
                dfs(i, deep+1);
                // 回溯
                isVisit[i] = false;
            }
        
        // 回溯
        for (int i = 1; i <= 26; ++i)
            if (cover[x][i] == true)
                depth[i] ++;
    }
}

int main(void)
{
    int H, W;
    ifile >> H >> W;
    for (int i = 1; i <= H; ++i)
        for (int j = 1; j <= W; ++j)
            ifile >> map[i][j];

    // 找出每个字母矩阵 最上
    for (int i = 1; i <= H; ++i) {
        for (int j = 1; j <= W; ++j) {
            int temp;
            if (map[i][j] == '.') continue;
            temp = map[i][j] - 'A' + 1;
            // 记录出现过的字母
            if (false == hasht[temp]) {
                hasht[temp] = true;
                total ++;
            }
            if (!up[temp])
                up[temp] = i;
        }
    }

    // 找出每个字母矩阵 最下
    for (int i = H; i >= 1; --i) {
        for (int j = 1; j <= W; ++j) {
            int temp;
            if (map[i][j] == '.') continue;
            temp = map[i][j] - 'A' + 1;
            if (!down[temp])
                down[temp] = i;
        }
    }

    // 找出每个字母矩阵 最左
    for (int j = 1; j <= W; ++j) {
        for (int i = 1; i<= H; ++i) {
            int temp;
            if (map[i][j] == '.') continue;
            temp = map[i][j] - 'A' + 1;
            if (!leftt[temp])
                leftt[temp] = j;
        }
    }

    // 找出每个字母矩阵 最右
    for (int j = W; j >= 1; --j) {
        for (int i = 1; i <= H; ++i) {
            int temp;
            if (map[i][j] == '.') continue;
            temp = map[i][j] - 'A' + 1;
            if (!rightt[temp])
                rightt[temp] = j;
        }
    }

    // 开始扫描，扫描每个字母矩阵是否被其他矩阵覆盖
    for (int i = 1; i <= 26; ++i) {
        if (hasht[i] == false) continue;

        // 每个字母矩阵，最上最下两条边，从左到右扫描
        for (int j = leftt[i]; j<= rightt[i]; ++j) {
            if (map[up[i]][j]=='.' || map[down[i]][j]=='.')
                continue;
            int temp1 = map[up[i]][j] - 'A' + 1;
            int temp2 = map[down[i]][j] - 'A' + 1;
            // 出现非该矩阵的字母，
            // 则加深一个深度，并记录覆盖情况
            if (temp1!=i && !cover[i][temp1]) {
                depth[temp1] ++;
                cover[i][temp1] = true;
            }
            if (temp2!=i && !cover[i][temp2]) {
                depth[temp2] ++;
                cover[i][temp2] = true;
            }
        }
        // 每个字母矩阵，最左最右两条边，从上到下扫描
        for (int j = up[i]; j<= down[i]; ++j) {
            if (map[j][leftt[i]]=='.' || map[j][rightt[i]]=='.')
                continue;
            int temp1 = map[j][leftt[i]] - 'A' + 1;
            int temp2 = map[j][rightt[i]] - 'A' + 1;
            if (temp1!=i && !cover[i][temp1]) {
                depth[temp1] ++;
                cover[i][temp1] = true;
            }
            if (temp2!=i && !cover[i][temp2]) {
                depth[temp2] ++;
                cover[i][temp2] = true;
            }
        }
    }

    // 从每个字母扫描
    for (int i = 1; i <= 26; ++i) {
        memset(isVisit, 0, sizeof(isVisit));
        if (hasht[i] == true) {
            isVisit[i] = true;
            dfs(i, 1);
        }
    }

    return 0;
}