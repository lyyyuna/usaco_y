/*
ID: lyyyuna
PROG: checker
LANG: C++
*/

#include <fstream>

using namespace::std;

ifstream ifile("checker.in");
ofstream ofile("checker.out");
int num;
int total_solution_number; // һ��ֻҪ���3����
int checker[20];
int a[3][50];

void dfs(int x_row)
{
    // �ݹ���ڣ�Ҳ����ɨ�赽���һ��
    if (x_row == num)
    {
        // ���������
        if (total_solution_number < 3) {
            for (int i = 0; i < num-1; ++i)
                ofile << checker[i] << " ";
            ofile << checker[num-1] << endl;
        }
        total_solution_number++;
        return;
    }

    for (int i = 0; i < num; ++i) {
        // �����и�����
        // �ж�ͬһ���Ƿ�����ͬԪ�� i
        // �ж�б���򣬴����ϵ����� i+x_row���������Ψһ�ģ�ͬһ����i+j��ȫ���
        // �ж�б���򣬴����Ͻǵ����£�i-x_row+23 �����Ҳ��Ψһ�ģ�i-x_row����
        // ��������һ�������������
        if (!a[0][i] && !a[1][x_row+i] && !a[2][x_row-i+15]) {
            checker[x_row] = i+1;

            a[0][i] = 1;
            a[1][x_row+i] = 1;
            a[2][x_row-i+15] = 1;
            // ��������һ��
            dfs(x_row+1);
            // ���ݣ��ѱ�־λ���
            a[0][i] = 0;
            a[1][x_row+i] = 0;
            a[2][x_row-i+15] = 0;
        }
    }
    return;
}

int main(void)
{
    ifile >> num;

    dfs(0);

    ofile << total_solution_number << endl;
}