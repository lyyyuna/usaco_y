/*
ID: lyyyuna
PROG: butter
LANG: C++
*/

#include <fstream>
#include <queue>
#include <climits>

using namespace::std;

struct Node
{
    int to;
    int len;
};

ifstream ifile("butter.in");
ofstream ofile("butter.out");
int N, P, C;

int cow[500+1]; // ������¼ÿ��ţ���ڵ�����
Node adj[800+1][800+1]; // ������¼Ȩ��
int cnt[800+1]; // ��¼ÿһ�������� �� ��
bool flag[800+1];

int SPFA(int i)
{
    int d[800+1] = {0};
    for (int j = 1; j <= P; ++j)
        d[j] = INT_MAX;
    d[i] = 0;

    queue<int> Q;
    Q.push(i);
    flag[i] = true;
    while(!Q.empty()) {
        int x = Q.front();
        Q.pop();
        flag[x] = false;

        for (int j = 0; j < cnt[x]; ++j) {
            // �ɳ�
            if (d[x] + adj[x][j].len < d[adj[x][j].to]) {
                d[adj[x][j].to] = d[x] + adj[x][j].len;
                if (flag[adj[x][j].to] == false) {
                    Q.push(adj[x][j].to);
                    flag[adj[x][j].to] = true;
                }
            }// �ɳڽ���
        }
    }

    int result = 0;
    // ������ţ��ͳ��
    // ��Ϊ�п���ͬһ�������ж�ͷ��ţ
    for (int j =1; j <= N; ++j)
    {
        if (d[cow[j]] == INT_MAX)
            return -1; // �����ڣ���Ϊ��ͨ
        else
            result += d[cow[j]];
    }
    return result;
}


int main(void)
{
    ifile >> N >> P >> C;
    for (int i = 1; i <= N; ++i)
        ifile >> cow[i];

    int A, B, weight;
    for (int i = 1; i <= C; ++i) {
        ifile >> A >> B >> weight;
        // ˫��ÿһ���㶼����Ϣ
        adj[A][cnt[A]].to = B;
        adj[A][cnt[A]].len = weight;
        cnt[A] ++;

        adj[B][cnt[B]].to = A;
        adj[B][cnt[B]].len = weight;
        cnt[B] ++;
    }

    int tt;
    int min = INT_MAX;
    // ����ÿһ�������������С·��
    for (int i = 1; i <= P; ++i) {
        tt = SPFA(i);
        if (tt < min && tt!=-1)
            min = tt;
    }

    ofile << min << endl;

    return 0;
}