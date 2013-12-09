/*
ID: lyyyuna
PROG: telecow
LANG: C++
*/

#include <fstream>
#include <cstring>
#include <queue>

using namespace::std;

const int MAXN = 205;
const int INFTY = 999999999;

int N, M, st, ed;

int cow[MAXN][MAXN];
int FLOW[MAXN][MAXN];
int _cow[MAXN][MAXN];

int prenode[MAXN];
int _flow[MAXN];

int bfs()
{
    memset(prenode, -1, sizeof(prenode));
    memset(_flow, 0, sizeof(_flow));
    
    queue<int> Q;
    Q.push(st);
    prenode[st] = st;
    _flow[st] = INFTY;
    
    while(!Q.empty()) {
        int cur = Q.front();
        Q.pop();
        for (int next = 1; next <= N*2; ++next) {
            if (prenode[next] == -1 && _cow[cur][next] > 0) {
                prenode[next] = cur;
                _flow[next] = min(_flow[cur], _cow[cur][next]);

                if (next == N+ed)
                    return _flow[next];

                Q.push(next);
            }
        }
    }

    return 0;
}

int Edmonds_Karp()
{
    memset(FLOW , 0, sizeof(FLOW));
    memcpy(_cow, cow, sizeof(cow));

    int f=0, Cf;
    while(Cf = bfs()) {
        int i = prenode[N+ed];
        int j = N+ed;
        while(i!=j) {
            // f += Cf;
            FLOW[i][j] += Cf;
            FLOW[j][i] = -FLOW[i][j];
            _cow[i][j] = cow[i][j] - FLOW[i][j];
            _cow[j][i] = cow[j][i] - FLOW[j][i];
            j = i;
            i = prenode[j];
        }

        f += Cf;
    }

    return f;
}

int main(void)
{
    ifstream ifile("telecow.in");
    ofstream ofile("telecow.out");
    ifile >> N >> M >> st >> ed;

    for (int i = 1; i <= N; ++i)
        cow[N+i][i] = 1;
    for (int i = 1; i <= M; ++i) {
        int cow1, cow2;
        ifile >> cow1 >> cow2;
        cow[cow1][cow2+N] = cow[cow2][cow1+N] = INFTY;
    }

    int ans[MAXN];
    int num = 0;
    int oldF = Edmonds_Karp();
    for (int i = 1; i <= N; ++i) {
        cow[N+i][i] = 0;
        int newF = Edmonds_Karp();

        if (newF+1 == oldF) {
            ans[num++] = i;
            oldF --;
        }
        else
            cow[N+i][i] = 1;

        if (oldF == 0)
            break;
    }

    ofile << num << endl;
    ofile << ans[0];
    for (int i = 1; i < num; ++i)
        ofile << " " << ans[i];
    ofile << endl;

    return 0;
}
