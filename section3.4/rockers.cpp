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

void dfs(int num_of_disk,   // ��ǰ����
        int vol,    // ��ǰ������������
        int num_of_songs,   // �ѷŸ�����
        int n_song  // ��n_song�����
        )
{
    if (num_of_disk > M) return;
    if (n_song > N) return;
    
    // ���׸費��
    dfs(num_of_disk, vol, num_of_songs, n_song+1);

    // ���ԷŽ���ǰ������
    if (T - vol - songs[n_song] >= 0) {
        if (num_of_songs + 1 > maxsongs)
            maxsongs = num_of_songs+1;
        dfs(num_of_disk, vol+songs[n_song], num_of_songs+1, n_song+1);
    }
    // ���ܷŽ���ǰ���̣������ܷŽ���һ�Ŵ���
    // ���Ҵ��̻�û�ù�
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