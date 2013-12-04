/*
ID: lyyyuna
PROG: snail
LANG: C++
*/

#include <fstream>
#include <cstring>

using namespace::std;

int N, M;
int map[120+1][120+1];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

bool isVisit[121][121];
int steps;

bool isValid(int x, int y)
{
    if(x < 0 || x >= N || y < 0 || y >= N) return false;
    if(map[x][y] == 1) return false;
    return true;
}

void dfs(int x, int y, int dir, int deep)
{
    int nextx = x + dx[dir];
    int nexty = y + dy[dir];
    if (isValid(nextx, nexty)) {
        if (isVisit[nextx][nexty]) {
            steps = max(steps, deep);
            return ;
        }
        isVisit[nextx][nexty] = true;
        dfs(nextx, nexty, dir, deep+1);
        isVisit[nextx][nexty] = false;
        return ;
    }

    for (int i = 0; i < 4; ++i) {
        if (i%2 == dir%2) continue;
        int nextx = x + dx[i];
        int nexty = y + dy[i];
        if(nextx < 0 || nexty < 0 || nextx >= N || nexty >= N || map[nextx][nexty]) continue;
        if (isVisit[nextx][nexty]) {
            // steps = max(steps, deep);
            continue;
        }

        isVisit[nextx][nexty] = true;
        dfs(nextx, nexty, i, deep+1);
        isVisit[nextx][nexty] = false;
    }
    steps = max(steps, deep);
}

int main(void)
{
    ifstream ifile("snail.in");
    ofstream ofile("snail.out");

    ifile >> N >> M;
    for (int i = 0; i < M; ++i) {
        char ctmp;
        int tmp;
        ifile >> ctmp >> tmp;
        map[tmp-1][ctmp-'A'] = 1;
    }

    isVisit[0][0] = true;
    dfs(0, 0, 0, 0);
    memset(isVisit, 0, sizeof(isVisit));
    isVisit[0][0] = true;
    dfs(0, 0, 1, 0);

    ofile << steps+1 << endl;
    
    return 0;
}