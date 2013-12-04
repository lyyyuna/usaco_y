/*
ID: lyyyuna
PROG: stall4
LANG: C++
*/

/*
bool Ѱ�Ҵ�k�����Ķ�Ӧ����Ŀ�����·
{
    while (���ڽӱ����о�k�ܹ���������j)
    {
        if (j��������·��)
        {
            ��j��������·;
            if (j��δ�ǵ� ���� ��j�Ķ�Ӧ������п�����·)
            {
                �޸�j�Ķ�Ӧ��Ϊk;
                ���k�Ķ�Ӧ����п�����·,����true;
            }
        }
    }
    ���k�Ķ�Ӧ���û�п�����·,����false;
}

void ������hungary()
{
    for i->1 to n
    {
        if (���i�Ķ�Ӧ����п�����·)
            ƥ����++;
    }
    ��� ƥ����;
}
*/

#include <fstream>
#include <cstring>

using namespace::std;

const int MAXN = 201;
int con[MAXN][MAXN];
bool isFind[MAXN];
int match[MAXN];
int N, M;
int result;

bool dfs_crosspath(int cow)
{
    for (int i = 1; i <= con[cow][0]; ++i) {
        int stall = con[cow][i];
        // �ж�j�Ƿ��ѹ������Ƿ�������·�ϻ��Ƿ���Զ������������·�ϣ� 
        if (!isFind[stall]) {
             // ��Ǳ��ѹ� ����������·�ϻ���Զ������������·�ϣ�
            isFind[stall] = true;
            if (!match[stall] || dfs_crosspath(match[stall])) {
                // match[j]��ʾ������Ե���ţ
                match[stall] = cow;
                return true;
            }
        }
    }
    return false;
}

void hungary(void)
{
    memset(isFind, 0, sizeof(isFind));
    for (int i = 1; i <= N; ++i) {
         // dfs(i)��ʾ��iΪһ���˵������·�Ƿ���� 
        if (dfs_crosspath(i))
            result ++;
        memset(isFind, 0, sizeof(isFind));
    }
}

int main(void)
{
    ifstream ifile("stall4.in");
    ofstream ofile("stall4.out");

    ifile >> N >> M;
    for (int i = 1; i <= N; ++i) {
        ifile >> con[i][0];
        for (int j = 1; j <= con[i][0]; ++j)
            ifile >> con[i][j];
    }

    hungary();

    ofile << result << endl;
}