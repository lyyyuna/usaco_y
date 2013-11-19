/*
ID: lyyyuna
PROG: spin
LANG: C++
*/

#include <fstream>

using namespace::std;

struct wheel
{
    int speed;
    int size;
    int start[5];
    int len[5];
};

int main(void)
{
    ifstream ifile("spin.in");
    ofstream ofile("spin.out");

    wheel w[5];
    int wedge[361];

    for (int i = 0; i < 5; ++i) {
        int size;
        ifile >> w[i].speed >> size;
        w[i].size = size;
        while (--size >= 0)
            ifile >> w[i].start[size] >> w[i].len[size];
    }

    for (int time = 0; time < 360; ++time) {
        for (int i = 0; i < 360; ++i)
            wedge[i] = -1;

        for (int i = 0; i < 5; ++i) {
            // 每个空隙分析
            for (int j = 0; j < w[i].size; ++j) {
                // 对空隙的每个离散点分析
                for (int k = w[i].start[j]; k <= w[i].start[j]+w[i].len[j]; ++k) {
                    // 如果k这个点 的前一个轮，是空隙，则变为i
                    if (wedge[k%360] == i-1)
                        wedge[k%360] = i;
                }
                // 起始点按照速度转
                w[i].start[j] = (w[i].start[j]+w[i].speed) % 360;
            }
        }

        for (int i = 0; i < 360; ++i)
            // 如果wedge 为4， 说明5个轮子的这个点都是空隙
            if (wedge[i] == 4) {
                ofile << time << endl;
                return 0;
            }
    }
    
    ofile << "none" << endl;

    return 0;
}