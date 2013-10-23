/*
ID: lyyyuna
LANG: C++
PROG: milk2
*/

#include <fstream>

using namespace::std;
const int N = 1000000;

int main(void)
{
    ifstream ifile("milk2.in");
    ofstream ofile("milk2.out");
    int num, actual_num(0);
    int begin, end;
    bool time[N]={false};

    ifile >> num;
    // record time interval
    for (int i = 0; i != num; ++i) {
        ifile >> begin >> end;
        for (int j = begin; j != end; ++j)
            time[j] = true;
        actual_num = actual_num < end ? end : actual_num;
    }

    int continuous_time(0), idle_time(0);
    int continuous_time_max(0), idle_time_max(0);
    /* ȥ���ʼ�Ƕ�û�й�����ʱ�� */
    int begin_index(0);
    for (; begin_index != actual_num; ++begin_index) {
        if (time[begin_index] == false)
            continue;
        else
            break;
    }
    /* ������Ѱ���ʱ��Σ���������begin_index��actual_num��ֻ������ʱ���Ĳ��� */
    for (int i = begin_index+1; i != actual_num; ++i) {
        if (time[i] == true) {
            if (time[i-1] == true) {
                continuous_time ++;
            }
            else {
                continuous_time = 0;
            }
        }
        continuous_time_max = continuous_time > continuous_time_max ? continuous_time : continuous_time_max;

        if (time[i] == false) {
            if (time[i-1] == false) {
                idle_time ++;
            }
            else {
                idle_time = 0;
            }
        }
        idle_time_max = idle_time > idle_time_max ? idle_time : idle_time_max;
    }

    /* Ҫ�ų�һ����������������㶼�����ģ�û�п���ʱ�� 
       �������Ҫcontinuous_time_max��idle_time_max��һ */
    if (actual_num-begin_index != continuous_time_max+1) {
        continuous_time_max ++;
        idle_time_max ++;
    } else
        continuous_time_max ++;

    ofile << continuous_time_max << " " << idle_time_max << endl;;

    return 0;
}