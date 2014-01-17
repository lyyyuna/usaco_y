/*
ID: lyyyuna
PROG: agrinet
LANG: C++
*/

#include <fstream>
#include <algorithm>

using namespace::std;

const int MAXN = 10001;
int u[MAXN];    // 储存边的一边节点
int v[MAXN];    // 储存边的另一边节点
int weight[MAXN];   // 储存权值
int parent[MAXN];   // 储存根节点，用来判断两个节点是否在同一棵树上
int a[MAXN];
int total_edge;

int find_set(int x)
{
    return parent[x] == x ? x : find_set(parent[x]);
}

bool cmp(int x, int y)
{
    return weight[x] < weight[y];
}

int kruskal(void)
{
    int length(0);
    // 初始状态下，每个点都是一颗树，根节点即为自己
    for (int i = 0; i < total_edge; ++i) {
        parent[i] = i;
        a[i] = i;
    }
    // 边按权值排序
    sort(a, a+total_edge, cmp);

    int res(0);
    for (int i = 0; i < total_edge; ++i) {
        int which_edge = a[i];
        // 找到边的两边的节点，各自所在的树
        int x = find_set(u[which_edge]);
        int y = find_set(v[which_edge]);
        // 如果不是同一个树，就加入最小生成树
        if (x != y) {
            res += weight[which_edge];
            // 并且跟新其中一个节点的根节点，合并成一颗树
            parent[x] = y;
        }
    }

    return res;
}

int main(void)
{
    ifstream ifile("agrinet.in");
    ofstream ofile("agrinet.out");

    int num;
    ifile >> num;
    int edge_weight;
    for (int i = 0; i < num; ++i)
        for (int j = 0; j < num; ++j) {
            ifile >> edge_weight;
            u[total_edge] = i;
            v[total_edge] = j;
            weight[total_edge] = edge_weight;
            total_edge ++;
        }

    int res = kruskal();
    ofile << res << endl;
}