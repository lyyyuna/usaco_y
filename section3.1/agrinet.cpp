/*
ID: lyyyuna
PROG: agrinet
LANG: C++
*/

#include <fstream>
#include <algorithm>

using namespace::std;

const int MAXN = 10001;
int u[MAXN];
int v[MAXN];
int weight[MAXN];
int parent[MAXN];
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
    for (int i = 0; i < total_edge; ++i) {
        parent[i] = i;
        a[i] = i;
    }
    sort(a, a+total_edge, cmp);

    int res(0);
    for (int i = 0; i < total_edge; ++i) {
        int which_edge = a[i];
        int x = find_set(u[which_edge]);
        int y = find_set(v[which_edge]);
        if (x != y) {
            res += weight[which_edge];
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
        for (int j = 0; j <num; ++j) {
            ifile >> edge_weight;
            u[total_edge] = i;
            v[total_edge] = j;
            weight[total_edge] = edge_weight;
            total_edge ++;
        }

    int res = kruskal();
    ofile << res << endl;
}