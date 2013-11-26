/*
ID: lyyyuna
PROG: fence
LANG: C++
*/

#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace::std;

struct Edge
{
    Edge(const int &tt, const int &revv):to(tt), cnt(revv), flag(true){};
    int to, cnt;
    bool flag;  // 表示有没有被访问过

};
std::vector<std::vector<Edge> > graph;

void dfs(int i)
{
    vector<int> output_s;   //用来存储输出字符

    stack<pair<int, vector<Edge>::iterator> > dfs_stack;    // 用来深搜的栈
    dfs_stack.push(make_pair(i, graph[i].begin()));
    while (!dfs_stack.empty()) {
        pair<int, vector<Edge>::iterator> &top = dfs_stack.top();
        // 从某一个点的第一条边开始搜
        for (; top.second != graph[top.first].end(); ++top.second) {
            // 如果这条边没有被搜过，则深入一层
            if (top.second->flag) {
                // 表示被搜过
                top.second->flag = false;
                // 这条边的另一个顶点，也做相应的标记
                graph[top.second->to][top.second->cnt].flag = false;
                // 入栈
                dfs_stack.push(make_pair(top.second->to, graph[top.second->to].begin()));
                // 这条边搜过，换下一个
                ++top.second;
                // 直接跳过
                goto label;
            }
        }
        // 到这里，说明已经深搜到最底层
        // 然后把这个点放入输出
        output_s.push_back(top.first);
        // 弹出这个点
        dfs_stack.pop();
        // 然后下一个循环，取出栈中的顶点，
        // 而栈中即为刚刚压入栈中的点，这样就模拟了深搜的行为。
        label:;
    }

    ofstream ofile("fence.out");
    for (vector<int>::reverse_iterator riter=output_s.rbegin(); riter != output_s.rend(); ++riter)
        ofile << *riter << endl;
}

int main(void)
{
    ifstream ifile("fence.in");
    int F;
    int maxn(0);
    ifile >> F;
    vector<pair<int, int> > edgeset;
    // edgeset.reserve(F);
    for (int i = 0; i < F; ++i) {
        int a, b;
        ifile >> a >> b;
        if (b < a)
            swap(a, b);
        edgeset.push_back(make_pair(a, b));
        if (maxn < b)
            maxn = b;
    }
    // 给边排序
    sort(edgeset.begin(), edgeset.end());
    for (int i = 0; i <= maxn; ++i) {
        graph.push_back(vector<Edge>());
        // graph.back().reserve(100);
    }
    // 对每个点进行存储边，两个点都要存储，
    // 存储指向的点，和这条边的编号。
    for (vector<pair<int, int> >::iterator iter = edgeset.begin(); iter != edgeset.end(); ++iter) {
        graph[iter->first].push_back(Edge(iter->second, graph[iter->second].size()+(iter->first==iter->second)));
        graph[iter->second].push_back(Edge(iter->first, graph[iter->first].size()-1));
    }
    // 当某个点的边是奇数个，所以这个点是起点或终点
    for (vector<vector<Edge> >::iterator iter=graph.begin()+1; iter != graph.end(); ++iter)
        if (iter->size() % 2 == 1) {
            dfs(iter - graph.begin());
            return 0;
        }
    // 如果没有起点或终点，则随便选一个
    for (vector<vector<Edge> >::iterator iter=graph.begin()+1; iter != graph.end(); ++iter)
        if (iter->size()) {
            dfs(iter - graph.begin());
            return 0;
        }

    return 0;
}