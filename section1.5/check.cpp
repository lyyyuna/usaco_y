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
int total_solution_number; // 一共只要输出3个解
int checker[20];
int a[3][50];

void dfs(int x_row)
{
    // 递归出口，也就是扫描到最后一行
    if (x_row == num)
    {
        // 输出三个解
        if (total_solution_number < 3) {
            for (int i = 0; i < num-1; ++i)
                ofile << checker[i] << " ";
            ofile << checker[num-1] << endl;
        }
        total_solution_number++;
        return;
    }

    for (int i = 0; i < num; ++i) {
        // 这里有个技巧
        // 判断同一列是否有相同元素 i
        // 判断斜方向，从左上到右下 i+x_row，这个和是唯一的，同一条线i+j完全相等
        // 判断斜方向，从右上角到左下，i-x_row+23 这个数也是唯一的，i-x_row有正
        // 负，随便加一个大数变成正的
        if (!a[0][i] && !a[1][x_row+i] && !a[2][x_row-i+15]) {
            checker[x_row] = i+1;

            a[0][i] = 1;
            a[1][x_row+i] = 1;
            a[2][x_row-i+15] = 1;
            // 深搜至下一层
            dfs(x_row+1);
            // 回溯，把标志位清掉
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