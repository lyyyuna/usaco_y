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
                minAindex = j;  // 记录机器编号
            }
        for (int j = 1; j < M2; ++j)
            if (delayB[j] + machineB[j] < minB) {
                minB = delayB[j] + machineB[j];
                minBindex = j;
            }
        // 按照机器顺序记录时间
        delayA[minAindex] = minA;
        delayB[minBindex] = minB;

        // 以下是按物料顺序记录所需时间,跟上面不同
        // 记录A操作出第j个零件的用时
        //     B
        costA[i] = minA;
        costB[i] = minB;
    }

    ofile << minA << ' ';

    int timeB;
    // A的工序是与B首尾对应的，即A的第一个交给B的倒数第一个，即
    // 第n个，A的第i个交给B的倒数第i个，即第n-i+1个） 那么
    // max(cost[A][i]+cost[B][n-i+1]) i=1,2,3,4...n就是B操作的最短用时。 
    timeB = costA[0] + costB[N-1];
    for (int i = 1; i < N; ++i)
        if (timeB < costA[i] + costB[N-i-1])
            timeB = costA[i] + costB[N-i-1];
    ofile << timeB << endl;

    return 0;
}