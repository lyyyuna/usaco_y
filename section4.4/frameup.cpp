/*
ID: lyyyuna
PROG: frameup
LANG: C++
*/

/*
�������֪��������һ�����ε�һ���߱���ȫ���ǣ��������ǿ��Լ��������
�����ꡣ ����ʱ��¼���ε�ÿ��������Сx1����Сy1�����x2�����y2����
֪���Ͻ� (x1,y1) ���½� (x2,y2) ���Ͻ� (x2,y1) ���½� (x1,y2)��

���Ҹþ���A���ϣ��Ǹþ��ε���ĸB�������Ǿ���A������B���ǡ�����һ����
���B->A����ʾB��A�ı�Ҫ������Ȼ����������������������е�������
�У������������

ע�⣬�����е���ĸ���ܲ���������Ҫֱ��for(i='A';i<='Z';i++)�� 
*/

#include <fstream>
#include <cstring>

using namespace::std;

ifstream ifile("frameup.in");
ofstream ofile("frameup.out");

const int MAXN = 50+1;
char map[MAXN][MAXN];   // ��¼ԭͼ���
bool hasht[MAXN];       // ��¼�����ĸ�Ƿ���ֹ�
bool cover[MAXN][MAXN]; // ��¼[i][j]  j����i
int depth[MAXN];        // ��¼�����ĸ�ĸ������

// ��¼ÿ����ĸ�������Ҽ���ֵ
int up[MAXN]; int down[MAXN];
int leftt[MAXN]; int rightt[MAXN];

// ��¼�Ƿ񱻷��ʹ�
bool isVisit[MAXN];

// �ܵĳ�����ĸ��
int total;
char result[MAXN];

void dfs(int x, int deep)
{
    result[deep] = x;
    
    // �ݹ����
    if (deep >= total) {
        for (int i = 1; i <= total; ++i) {
            char c = result[i]+'A'-1;
            ofile << c;
        }
        ofile << endl;
        return ;
    }

    // ���Ϊ0��˵�������ĸ�����Ѿ��������ϲ㣬�����������ϲ�
    if (depth[x] == 0) {
        // ÿ������x �Ĳ� �����ϸ�һ��
        for (int i = 1; i <= 26; ++i)
            if (cover[x][i] == true)
                depth[i] --;

        for (int i = 1; i <= 26; ++i)
            // ����������㸡����������
            // ������
            if (depth[i] == 0 && !isVisit[i] && hasht[i]) {
                isVisit[i] = true;
                dfs(i, deep+1);
                // ����
                isVisit[i] = false;
            }
        
        // ����
        for (int i = 1; i <= 26; ++i)
            if (cover[x][i] == true)
                depth[i] ++;
    }
}

int main(void)
{
    int H, W;
    ifile >> H >> W;
    for (int i = 1; i <= H; ++i)
        for (int j = 1; j <= W; ++j)
            ifile >> map[i][j];

    // �ҳ�ÿ����ĸ���� ����
    for (int i = 1; i <= H; ++i) {
        for (int j = 1; j <= W; ++j) {
            int temp;
            if (map[i][j] == '.') continue;
            temp = map[i][j] - 'A' + 1;
            // ��¼���ֹ�����ĸ
            if (false == hasht[temp]) {
                hasht[temp] = true;
                total ++;
            }
            if (!up[temp])
                up[temp] = i;
        }
    }

    // �ҳ�ÿ����ĸ���� ����
    for (int i = H; i >= 1; --i) {
        for (int j = 1; j <= W; ++j) {
            int temp;
            if (map[i][j] == '.') continue;
            temp = map[i][j] - 'A' + 1;
            if (!down[temp])
                down[temp] = i;
        }
    }

    // �ҳ�ÿ����ĸ���� ����
    for (int j = 1; j <= W; ++j) {
        for (int i = 1; i<= H; ++i) {
            int temp;
            if (map[i][j] == '.') continue;
            temp = map[i][j] - 'A' + 1;
            if (!leftt[temp])
                leftt[temp] = j;
        }
    }

    // �ҳ�ÿ����ĸ���� ����
    for (int j = W; j >= 1; --j) {
        for (int i = 1; i <= H; ++i) {
            int temp;
            if (map[i][j] == '.') continue;
            temp = map[i][j] - 'A' + 1;
            if (!rightt[temp])
                rightt[temp] = j;
        }
    }

    // ��ʼɨ�裬ɨ��ÿ����ĸ�����Ƿ��������󸲸�
    for (int i = 1; i <= 26; ++i) {
        if (hasht[i] == false) continue;

        // ÿ����ĸ�����������������ߣ�������ɨ��
        for (int j = leftt[i]; j<= rightt[i]; ++j) {
            if (map[up[i]][j]=='.' || map[down[i]][j]=='.')
                continue;
            int temp1 = map[up[i]][j] - 'A' + 1;
            int temp2 = map[down[i]][j] - 'A' + 1;
            // ���ַǸþ������ĸ��
            // �����һ����ȣ�����¼�������
            if (temp1!=i && !cover[i][temp1]) {
                depth[temp1] ++;
                cover[i][temp1] = true;
            }
            if (temp2!=i && !cover[i][temp2]) {
                depth[temp2] ++;
                cover[i][temp2] = true;
            }
        }
        // ÿ����ĸ�����������������ߣ����ϵ���ɨ��
        for (int j = up[i]; j<= down[i]; ++j) {
            if (map[j][leftt[i]]=='.' || map[j][rightt[i]]=='.')
                continue;
            int temp1 = map[j][leftt[i]] - 'A' + 1;
            int temp2 = map[j][rightt[i]] - 'A' + 1;
            if (temp1!=i && !cover[i][temp1]) {
                depth[temp1] ++;
                cover[i][temp1] = true;
            }
            if (temp2!=i && !cover[i][temp2]) {
                depth[temp2] ++;
                cover[i][temp2] = true;
            }
        }
    }

    // ��ÿ����ĸɨ��
    for (int i = 1; i <= 26; ++i) {
        memset(isVisit, 0, sizeof(isVisit));
        if (hasht[i] == true) {
            isVisit[i] = true;
            dfs(i, 1);
        }
    }

    return 0;
}