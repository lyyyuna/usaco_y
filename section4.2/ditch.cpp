/*
ID: lyyyuna
PROG: ditch
LANG: C++
*/

#include <fstream>
#include <cstring>
#include <queue>

using namespace::std;

int startP;
int endP;
int con[200+1][200+1];  // ��¼������֮��ߵ�����
int prePoint[200+1];    // ��¼�õ��ǰ���ڵ����ĸ�
int flow[200+1];        // �����ڵ������

int bfs(void)
{
    queue <int> Q;
    while (!Q.empty())
        Q.pop();
    Q.push(startP);
    memset(prePoint, -1, sizeof(prePoint));
    // ����ǰ����Ϊ0
    prePoint[startP] = 0;
    // 
    flow[startP] = 3290409;
    while (!Q.empty()) {
        int curP = Q.front();
        Q.pop();
        // �������յ�
        if (curP == endP)
            break;
        for (int i = 1; i <= endP; ++i) {
            // ��������û�ҵ����������б�����
            if (prePoint[i] == -1 && con[curP][i]!=0) {
                // ������
                prePoint[i] = curP;
                flow[i] = min(flow[curP], con[curP][i]);
                Q.push(i);
            }
        }
    }
    // �����յ�û��������
    if (prePoint[endP] == -1)
        return -1;
    return flow[endP];
}

int Edmonds_Karp(void)
{
    int max_flow = 0;
    int Cf;
    while ((Cf = bfs()) != -1) {
        // ���յ㿪ʼ
        int curP = endP;
        // �����Ϊֹ
        while (curP != startP) {
            // �Ӻ���ǰ��
            int preP = prePoint[curP];
            // �����
            con[preP][curP] -= Cf;
            // �����
            con[curP][preP] += Cf;
            curP = preP;
        }
        max_flow += Cf;
    }
    return max_flow;
}

int main(void)
{
    ifstream ifile("ditch.in");
    ofstream ofile("ditch.out");
    int N, M;
    ifile >> N >> M;
    endP = M;
    for (int i = 0; i < N; ++i) {
        int Si, Ei, Ci;
        ifile >> Si >> Ei >> Ci;
        con[Si][Ei] += Ci;
    }

    startP = 1;
    int result = Edmonds_Karp();
    ofile << result << endl;

    return 0;
}