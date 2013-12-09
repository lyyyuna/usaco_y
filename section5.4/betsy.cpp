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
当前点左右都是已经点(包括边缘)，而上下都是未经点
当前点上下都是已经点(包括边缘)，而左右都是未经点 
这样就会形成孤立的区域，只要将出现这种情况的状态都剪掉即可。 
*/
    if ( (map[i][j-1] && map[i][j+1] && !map[i-1][j] && !map[i+1][j]) ||
        (!map[i][j-1] && !map[i][j+1] && map[i-1][j] && map[i+1][j]) )
        return ;

    int cntnum = 0;
    int cnti, cntj;
    for (int k = 0; k < 4; ++k) {
        int ni = i + di[k];
        int nj = j + dj[k];
        // (ni==N && nj==1)??? 这一步可能是因为虽然下一步是终点，但不能保证走到这一步后，所有格子都走遍
        if (map[ni][nj] || (ni==N && nj==1))
            continue;

        int num = 0;
        for (int k = 0; k < 4; ++k) {
            if ( !map[ ni+di[k] ][ nj+dj[k] ] )
                num ++;
        }
        // 当前点周围的点cnti,cntj,如果只有一个与cnti,cntj相邻的未经点,则点cnti,cntj为必经点。 
        if (num < 2) {
            cntnum ++;
            cnti = ni;
            cntj = nj;
        }
    }

    // 显然，如果当前点周围有两个或两个以上的符合上述条件的必经点，则无论走哪个必经点都会造成一个死胡同，需要剪枝。 
    if (cntnum > 1)
        return ;
    else {
        // 如果当前点周围只有一个必经点，则一定要走到这个点。 
        if (cntnum == 1) {
            map[cnti][cntj] = true;
            dfs(cnti, cntj, step+1);
            map[cnti][cntj] = false;
        }
        else {
            // 如果该点周围没有必经点，则需要枚举周围每一个点。
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