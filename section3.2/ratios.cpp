/*
ID: lyyyuna
PROG: ratios
LANG: C++
*/

#include <fstream>

using namespace::std;

//计算三阶行列式的值
int DD(int (*x)[4])
{
    int ans=x[1][1]*x[2][2]*x[3][3]+x[2][1]*x[3][2]*x[1][3]+x[3][1]*x[1][2]*x[2][3]
            -x[1][3]*x[2][2]*x[3][1]-x[2][3]*x[3][2]*x[1][1]-x[3][3]*x[1][2]*x[2][1];
    return ans;
}

int main(void)
{
    ifstream ifile("ratios.in");
    ofstream ofile("ratios.out");

    int goals[4];
    int num[4][4];
    for (int i = 1; i < 4; ++i)
        ifile >> goals[i];
    // 要注意矩阵元素输入的顺序
    for (int i = 1; i < 4; ++i)
        for (int j = 1; j < 4; ++j)
            ifile >> num[j][i];

    int D, Dx, Dy, Dz;
    int temp[4];
    // 克莱姆法则
    D = DD(num);

    for (int i = 1; i < 4; ++i)
        temp[i] = num[i][1];
    for (int i = 1; i < 4; ++i)
        num[i][1] = goals[i];
    Dx = DD(num);
    for (int i = 1; i < 4; ++i)
        num[i][1] = temp[i];

    for (int i = 1; i < 4; ++i)
        temp[i] = num[i][2];
    for (int i = 1; i < 4; ++i)
        num[i][2] = goals[i];
    Dy = DD(num);
    for (int i = 1; i < 4; ++i)
        num[i][2] = temp[i];

    for (int i = 1; i < 4; ++i)
        temp[i] = num[i][3];
    for (int i = 1; i < 4; ++i)
        num[i][3] = goals[i];
    Dz = DD(num);
    for (int i = 1; i < 4; ++i)
        num[i][3] = temp[i];

    int x, y, z;
    for (int k = 1; k <= 100; ++k) {
        if (k*Dx%D==0 && k*Dy%D==0 && k*Dz%D==0) {
            x = k*Dx / D;
            y = k*Dy / D;
            z = k*Dz / D;
            if (x<0 || y<0 || z<0)
                continue;
            ofile << x << " " << y << " " << z << " " << k << endl;
            return 0;
        }
    }
    ofile << "NONE" << endl;

    return 0;
}
