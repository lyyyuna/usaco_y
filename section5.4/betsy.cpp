/*
ID: lyyyuna
PROG: betsy
LANG: C++
*/

#include <fstream>
 
using namespace::std;

int N;
bool map[9][9];
int cnt;
int di[4]={0,0,1,-1};
int dj[4]={1,-1,0,0};

void dfs(int i, int j, int step)
{
    if (i == N && j == 1) {
        if (step == N*N)
            cnt ++;
        return ;
    }

/*
��ǰ�����Ҷ����Ѿ���(������Ե)�������¶���δ����
��ǰ�����¶����Ѿ���(������Ե)�������Ҷ���δ���� 
�����ͻ��γɹ���������ֻҪ���������������״̬���������ɡ� 
*/
    if ( (map[i][j-1] && map[i][j+1] && !map[i-1][j] && !map[i+1][j]) ||
        (!map[i][j-1] && !map[i][j+1] && map[i-1][j] && map[i+1][j]) )
        return ;

    int cntnum = 0;
    int cnti, cntj;
    for (int k = 0; k < 4; ++k) {
        int ni = i + di[k];
        int nj = j + dj[k];
        // (ni==N && nj==1)??? ��һ����������Ϊ��Ȼ��һ�����յ㣬�����ܱ�֤�ߵ���һ�������и��Ӷ��߱�
        if (map[ni][nj] || (ni==N && nj==1))
            continue;

        int num = 0;
        for (int k = 0; k < 4; ++k) {
            if ( !map[ ni+di[k] ][ nj+dj[k] ] )
                num ++;
        }
        // ��ǰ����Χ�ĵ�cnti,cntj,���ֻ��һ����cnti,cntj���ڵ�δ����,���cnti,cntjΪ�ؾ��㡣 
        if (num < 2) {
            cntnum ++;
            cnti = ni;
            cntj = nj;
        }
    }

    // ��Ȼ�������ǰ����Χ���������������ϵķ������������ıؾ��㣬���������ĸ��ؾ��㶼�����һ������ͬ����Ҫ��֦�� 
    if (cntnum > 1)
        return ;
    else {
        // �����ǰ����Χֻ��һ���ؾ��㣬��һ��Ҫ�ߵ�����㡣 
        if (cntnum == 1) {
            map[cnti][cntj] = true;
            dfs(cnti, cntj, step+1);
            map[cnti][cntj] = false;
        }
        else {
            // ����õ���Χû�бؾ��㣬����Ҫö����Χÿһ���㡣
            for (int k = 0; k < 4; ++k) {
                int ni = i + di[k];
                int nj = j + dj[k];
                if (!map[ni][nj]) {
                    map[ni][nj] = true;
                    dfs(ni, nj, step+1);
                    map[ni][nj] = false;
                }
            }
        }
    }
}

int main(void)
{
    ifstream ifile("betsy.in");
    ofstream ofile("betsy.out");
    ifile >> N;
    for (int i = 0; i <= N+1; ++i)
        map[i][0] = map[0][i] = map[N+1][i] = map[i][N+1] = true;
    map[1][1] = true;

    dfs(1, 1, 1);

    ofile << cnt << endl;

    return 0;
}