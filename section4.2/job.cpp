/*
ID: lyyyuna
PROG: job
LANG: C++
*/

#include <fstream>

using namespace::std;

const int MAXM = 30+1;
const int MAXN = 1000+1;

int main(void)
{
    ifstream ifile("job.in");
    ofstream ofile("job.out");
    int N, M1, M2;
    ifile >> N >> M1 >> M2;

    int machineA[MAXM];
    int machineB[MAXM];
    for (int i = 0; i < M1; ++i)
        ifile >> machineA[i];
    for (int i = 0; i < M2; ++i)
        ifile >> machineB[i];

    int delayA[MAXN] = {0};
    int delayB[MAXN] = {0};
    int minA=0, minAindex=0;
    int minB=0, minBindex=0;
    int costA[MAXN] = {0};
    int costB[MAXN] = {0};
    for (int i = 0; i < N; ++i) {
        minA = delayA[0] + machineA[0];
        minAindex = 0;
        minB = delayB[0] + machineB[0];
        minBindex = 0;

        for (int j = 1; j < M1; ++j)
            if (delayA[j] + machineA[j] < minA) {
                minA = delayA[j] + machineA[j];
                minAindex = j;  // ��¼�������
            }
        for (int j = 1; j < M2; ++j)
            if (delayB[j] + machineB[j] < minB) {
                minB = delayB[j] + machineB[j];
                minBindex = j;
            }
        // ���ջ���˳���¼ʱ��
        delayA[minAindex] = minA;
        delayB[minBindex] = minB;

        // �����ǰ�����˳���¼����ʱ��,�����治ͬ
        // ��¼A��������j���������ʱ
        //     B
        costA[i] = minA;
        costB[i] = minB;
    }

    ofile << minA << ' ';

    int timeB;
    // A�Ĺ�������B��β��Ӧ�ģ���A�ĵ�һ������B�ĵ�����һ������
    // ��n����A�ĵ�i������B�ĵ�����i��������n-i+1���� ��ô
    // max(cost[A][i]+cost[B][n-i+1]) i=1,2,3,4...n����B�����������ʱ�� 
    timeB = costA[0] + costB[N-1];
    for (int i = 1; i < N; ++i)
        if (timeB < costA[i] + costB[N-i-1])
            timeB = costA[i] + costB[N-i-1];
    ofile << timeB << endl;

    return 0;
}