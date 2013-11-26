/*
ID: lyyyuna
PROG: fence6
LANG: C++
*/

#include <fstream>
#include <cstring>

using namespace::std;

int con[101][2][9];
// x y z      x����һ���ߵı�ţ�y���ĸ��˵㣬z�Ƕ˵����ŵı�
// ����[5][1][2] 5�űߵ�1�˵����ŵĵ�2��3������
// ����ֵ��ʾ���ŵıߵı��
// con[][][0] ��˳�������洢�˵������ߵĸ���
int len[101];
bool link[101][101]; // �洢x��y   �������Ƿ�����������˳���ǣ�x��1�˵�����y��0�˵�
                    // 0x10y1
bool sideflag[101];
int start_side;
int min_len = 939349;

// ���� �ߵı��  �ߵ���ʼ�˵��  �Ѿ��ۼӵĳ���
void dfs(int deep, int endpoint, int length)
{
    // ��֦
    if (length > min_len) return;

    // deep�����ߣ�������һ�˵���������
    for (int i = 1; i <= con[deep][1-endpoint][0]; ++i) {
        int now_side = con[deep][1-endpoint][i];
        // �ҵ�now_side�����ߣ���deep�������� �˵��
        int con_point = link[now_side][deep];
        // ����ʼ����ͬ��˵������һȦ��������һ�������
        if (start_side == now_side) {
            if (length < min_len)
                min_len = length;

            return ;
        }

        if (!sideflag[now_side]) {
            sideflag[now_side] = true;
            dfs(now_side, con_point, length+len[now_side]);
            // ����
            sideflag[now_side] = false;
        }
    }
}

int main(void)
{
    ifstream ifile("fence6.in");
    ofstream ofile("fence6.out");

    int total;
    ifile >> total;
    for (int i = 1; i <= total; ++i) {
        int x;
        ifile >> x;
        ifile >> len[x] >> con[x][0][0] >> con[x][1][0];
        for (int j = 1; j <= con[x][0][0]; ++j)
            ifile >> con[x][0][j];
        for (int j = 1; j <= con[x][1][0]; ++j) {
            ifile >> con[x][1][j];
            link[x][ con[x][1][j] ] = true;
        }
    }

    for (int i = 1; i <= total; ++i) {
        memset(sideflag, 0, sizeof(sideflag));
        // ��¼��ʼ��
        start_side = i;
        dfs(i, 0, len[i]);
    }

    ofile << min_len << endl;
    
    return 0;
}