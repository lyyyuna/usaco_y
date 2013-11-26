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
    bool flag;  // ��ʾ��û�б����ʹ�

};
std::vector<std::vector<Edge> > graph;

void dfs(int i)
{
    vector<int> output_s;   //�����洢����ַ�

    stack<pair<int, vector<Edge>::iterator> > dfs_stack;    // �������ѵ�ջ
    dfs_stack.push(make_pair(i, graph[i].begin()));
    while (!dfs_stack.empty()) {
        pair<int, vector<Edge>::iterator> &top = dfs_stack.top();
        // ��ĳһ����ĵ�һ���߿�ʼ��
        for (; top.second != graph[top.first].end(); ++top.second) {
            // ���������û�б��ѹ���������һ��
            if (top.second->flag) {
                // ��ʾ���ѹ�
                top.second->flag = false;
                // �����ߵ���һ�����㣬Ҳ����Ӧ�ı��
                graph[top.second->to][top.second->cnt].flag = false;
                // ��ջ
                dfs_stack.push(make_pair(top.second->to, graph[top.second->to].begin()));
                // �������ѹ�������һ��
                ++top.second;
                // ֱ������
                goto label;
            }
        }
        // �����˵���Ѿ����ѵ���ײ�
        // Ȼ��������������
        output_s.push_back(top.first);
        // ���������
        dfs_stack.pop();
        // Ȼ����һ��ѭ����ȡ��ջ�еĶ��㣬
        // ��ջ�м�Ϊ�ո�ѹ��ջ�еĵ㣬������ģ�������ѵ���Ϊ��
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
    // ��������
    sort(edgeset.begin(), edgeset.end());
    for (int i = 0; i <= maxn; ++i) {
        graph.push_back(vector<Edge>());
        // graph.back().reserve(100);
    }
    // ��ÿ������д洢�ߣ������㶼Ҫ�洢��
    // �洢ָ��ĵ㣬�������ߵı�š�
    for (vector<pair<int, int> >::iterator iter = edgeset.begin(); iter != edgeset.end(); ++iter) {
        graph[iter->first].push_back(Edge(iter->second, graph[iter->second].size()+(iter->first==iter->second)));
        graph[iter->second].push_back(Edge(iter->first, graph[iter->first].size()-1));
    }
    // ��ĳ����ı���������������������������յ�
    for (vector<vector<Edge> >::iterator iter=graph.begin()+1; iter != graph.end(); ++iter)
        if (iter->size() % 2 == 1) {
            dfs(iter - graph.begin());
            return 0;
        }
    // ���û�������յ㣬�����ѡһ��
    for (vector<vector<Edge> >::iterator iter=graph.begin()+1; iter != graph.end(); ++iter)
        if (iter->size()) {
            dfs(iter - graph.begin());
            return 0;
        }

    return 0;
}