/*
ID: lyyyuna
PROG: ttwo
LANG: C++
*/

#include <fstream>

using namespace::std;

ifstream ifile("ttwo.in");
ofstream ofile("ttwo.out");
char graph[11][11];
int Fx, Fy; // farmer��ǰλ��
int Cx, Cy; // cow��ǰλ��
int times;  // �ܵ�ʱ����

int Fstep = 0;  // �����ߵĲ���
int Cstep = 0;

bool isOut(int x, int y)
{
    return (x<0 || y<0 || x>=10 || y>=10);
}

void simulation()
{

    int dx[] = {-1, 0, 1, 0};   // ���Ʒ���
    int dy[] = {0, 1, 0, -1};   // һ��ʼ���ó���
    int Fx_n, Fy_n;     // ��һ�����ܵ���λ�ã������ϰ�
    int Cx_n, Cy_n;
    int Fdir = 0;       // ����
    int Cdir = 0;

    while (Fstep <= 400 && Cstep <= 400) {
        // ����
        if (Fx == Cx && Fy == Cy)
            break;
        // farmer
        // �������һ�����ܵ�λ��
        Fx_n = Fx + dx[Fdir];
        Fy_n = Fy + dy[Fdir];
        // ���ж��Ƿ����������ϰ�
        if (!isOut(Fx_n, Fy_n) && graph[Fx_n][Fy_n]!='*') {
            Fx = Fx_n;
            Fy = Fy_n;
            Fstep ++;
        }
        // ����ת��
        else
            Fdir = (Fdir+1)%4;
        
        // ͬ��
        Cx_n = Cx + dx[Cdir];
        Cy_n = Cy + dy[Cdir];
        if (!isOut(Cx_n, Cy_n) && graph[Cx_n][Cy_n]!='*') {
            Cx = Cx_n;
            Cy = Cy_n;
            Cstep ++;
        }
        else
            Cdir = (Cdir+1)%4;

        times ++;
    }
}

int main(void)
{
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j) {
            ifile >> graph[i][j];
            // ����cow��λ�ã�����ԭ�� .
            if (graph[i][j] == 'C') {
                Cx = i;
                Cy = j;
                graph[i][j] = '.';
            }
            // ����farmer��λ�ã�����ԭ�� .
            if (graph[i][j] == 'F') {
                Fx = i;
                Fy = j;
                graph[i][j] = '.';
            }
        }
    // ������Ŀ��˼����ģ��
    simulation();
    // �����һ�� ����400����˵��������
    if (Fstep <= 400 && Cstep <= 400)
        ofile << times << endl;
    else
        ofile << 0 << endl;

    return 0;
}