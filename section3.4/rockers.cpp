/*
ID: lyyyuna
PROG: rockers
LANG: C++
*/

#include <fstream>

using namespace::std;

int songs[21];
int maxsongs;
int N, T, M;

void dfs(int num_of_disk,   // 当前磁盘
        int vol,    // 当前磁盘已用容量
        int num_of_songs,   // 已放歌数量
        int n_song  // 第n_song的情况
        )
{
    if (num_of_disk > M) return;
    if (n_song > N) return;
    
    // 这首歌不放
    dfs(num_of_disk, vol, num_of_songs, n_song+1);

    // 可以放进当前磁盘里
    if (T - vol - songs[n_song] >= 0) {
        if (num_of_songs + 1 > maxsongs)
            maxsongs = num_of_songs+1;
        dfs(num_of_disk, vol+songs[n_song], num_of_songs+1, n_song+1);
    }
    // 不能放进当前磁盘，而且能放进下一张磁盘
    // 而且磁盘还没用光
    else if (T - songs[n_song] >= 0 && num_of_disk!=M) {
          if(num_of_songs+1>maxsongs)
              maxsongs = num_of_songs+1;
          dfs(num_of_disk+1, songs[n_song], num_of_songs+1, n_song+1);
    }

    return ;
}

int main(void)
{
    ifstream ifile("rockers.in");
    ofstream ofile("rockers.out");
    ifile >> N >> T >> M;
    for (int i = 1; i <= N; ++i)
        ifile >> songs[i];

    dfs(1, 0, 0, 1);

    ofile << maxsongs << endl;

    return 0;
}