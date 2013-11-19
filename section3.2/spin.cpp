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
            // ÿ����϶����
            for (int j = 0; j < w[i].size; ++j) {
                // �Կ�϶��ÿ����ɢ�����
                for (int k = w[i].start[j]; k <= w[i].start[j]+w[i].len[j]; ++k) {
                    // ���k����� ��ǰһ���֣��ǿ�϶�����Ϊi
                    if (wedge[k%360] == i-1)
                        wedge[k%360] = i;
                }
                // ��ʼ�㰴���ٶ�ת
                w[i].start[j] = (w[i].start[j]+w[i].speed) % 360;
            }
        }

        for (int i = 0; i < 360; ++i)
            // ���wedge Ϊ4�� ˵��5�����ӵ�����㶼�ǿ�϶
            if (wedge[i] == 4) {
                ofile << time << endl;
                return 0;
            }
    }
    
    ofile << "none" << endl;

    return 0;
}