/*
Id��lyyyuna
PROG: race3
LANG: C++
*/

#include <fstream>
#include <cstring>

using namespace::std;

bool path1[50+1][50+1]; // ��¼ԭʼ����֮����ͨ���
bool path2[50+1][50+1]; // ��¼ʵ�������Ƿ����ͨ�����������

int isVisit[50+1];
int nump = -1;

// ·��������ͨ��splitpoint��Ȼ���¼�¸������״̬
void dfs(int deep, int splitpoint)
{
    isVisit[deep] = true;
    for (int i = 0; i <= nump; ++i)
        if (i != splitpoint && path1[deep][i] && !isVisit[i])
            dfs(i, splitpoint);
}

int main(void)
{
    ifstream ifile("race3.in");
    ofstream ofile("race3.out");

    int point = 0;

    while (point != -1) {
        nump++;
        while (true) {
            ifile >> point;
            if (point < 0)
                break;
            path1[nump][point] = true;
        }
    }
    nump--;

    memcpy(path2, path1, sizeof(path2));

    for (int k = 0; k <= nump; ++k)
        for (int i = 0; i <= nump; ++i)
            for (int j = 0; j <= nump; ++j)
                if (path2[i][k] && path2[k][j])
                    path2[i][j] = true;

    
    int unavoid[50+1];
    int split[50+1];
    int a(0), b(0);
    // ��iΪ�ָ�㣬��·��������ͨ��i
    // ��ȥ0���յ�
    for (int i = 1; i < nump; ++i) {
        memset(isVisit, 0, sizeof(isVisit));
        dfs(0, i);
        
        // ����ָ���յ㲻�ɴ˵���ָ����һ��unavoidable
        if (!isVisit[nump]) {
            unavoid[a++] = i;
            bool flag = true;

            // ��ͼ������path2�� unavoidable �ĵ� 
            // �ܹ������ܻ�[i][j]����˵����������ͨ·��������
            // �����Ϊһ���м�·��
            for (int j = 0; j < nump; ++j)
                if (isVisit[j] && path2[i][j]) {
                    flag = false;
                    break;
                }
            if (flag == true)
                split[b++] = i;
        }
    }

    ofile << a;
    for (int i = 0; i < a; ++i)
        ofile << " " << unavoid[i];
    ofile << endl;
    ofile << b;
    for (int i = 0; i < b; ++i)
        ofile << " " << split[i];
    ofile << endl;

    return 0;
}