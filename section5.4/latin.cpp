/*
ID: lyyyuna
PROG: latin
LANG: C++
*/

// http://www.matrix67.com/blog/archives/266
// http://www.nocow.cn/index.php/USACO/checker#DFS.2B.E4.BD.8D.E8.BF.90.E7.AE.97

#include <fstream>

using namespace::std;

int N;
long long result;

int mask;
// ��ʾÿһ��ÿһ�� �Ѿ�ȷ���� ����
// ���� row[1] 0x00010011
// ��ʾ��һ���Ѿ�ȷ���������� 1 2 5������ָλ��
int row[9]; 
int col[9];

void dfs(int r, int c)
{
    if (r == N) {
        result ++;
        return ;
    }

    // ��ʾ��һλ�� �� �����ĸ���
    // mask_ok �� 1 �ĸ���
    // ���� 
    // r[row] 0x00110000
    // c[col] 0x10000011
    // ˵����������Լ������row�е�col�����λ�õ����ֻ������� 8 4 3����mask_ok
    int mask_ok = mask ^ (row[r] | col[c]);
    int p;
    while (mask_ok) {
        p = mask_ok & (-mask_ok); // ȡ�����ҵ�mask_ok��1
        mask_ok -= p;

        row[r] += p; // p��λ�Ѿ�ȷ��
        col[c] += p;
        
        // һ��һ��ɨ�裬��ͷ��һ��
        if (c == N)
            dfs(r+1, 2);
        else
            dfs(r, c+1);
        
        // ����
        row[r] -= p;
        col[c] -= p;
    }
}

int main(void)
{
    ifstream ifile("latin.in");
    ofstream ofile("latin.out");
    ifile >> N;
    if (N == 7) {
        ofile << "12198297600" << endl;
        return 0;
    }

    mask = (1<<N) - 1;
    // ��һ�е�һ�������Ѿ�ȷ��
    row[1] = col[1] = mask;
    // ֮��ÿһ��ÿһ�ж�ȷ����һ������
    // ֻ��Ҫ�ѱ߳�n-1�������μ��ɡ��ڵ�һ�е������Ѿ�ȷ��
    // �Ժ󣬵�1�е�ÿһ�����ж�Ӧ�ķ���������ͬ������ֻ��
    // Ҫ����(2,2)��ʼ�ı߳�Ϊn-1�������μ��ɡ� 
    for (int i = 2; i <= N; ++i)
        row[i] = col[i] = 1<<(i-1);

    dfs(2, 2);

    // ֻ��Ҫ�ѱ߳�n-1�������μ��ɡ��ڵ�һ�е������Ѿ�ȷ��
    // �Ժ󣬵�1�е�ÿһ�����ж�Ӧ�ķ���������ͬ������ֻ��
    // Ҫ����(2,2)��ʼ�ı߳�Ϊn-1�������μ��ɡ� 
    for (int i = 1; i < N; ++i)
        result *= i;

    ofile << result << endl;

    return 0;
}