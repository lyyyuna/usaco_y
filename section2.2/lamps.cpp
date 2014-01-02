/*
ID: lyyyuna
PROG: lamps
LANG: C++
*/

/*
首先，1 2 3 4 5 6 这六个灯就能代表所有的状态，后面的灯是前面的重复
但在这个解法里没有体现
这道题就是通过深搜，组合 四个按键 所有的状态，然后判断
*/

#include <fstream>
#include <algorithm>
#include <string>

using namespace::std;

int N, C;
bool on[101];
bool off[101];
bool lamps[101];
bool which_key[5];

string types[101];
int total_types;

char n_2_s(bool led)
{
    if (led == true)
        return '1';
    else 
        return '0';
}

void check()
{
    // 看灯的情况和 亮 灭 是否符合
    for (int i = 1; i <= N; ++i) {
        if (on[i] && !lamps[i])
            return;
        if (off[i] && lamps[i])
            return;
    }
    // 统计被按下的个数
    int number_key(0);
    for (int i = 1; i <= 4; ++i) {
        if (which_key[i] == true)
            number_key ++;
    }
    // 根据总的按下数C判断
    if (C < number_key)
        return;
    if ((C-number_key)%2 != 0)
        return;
    
    // 如果运行到这里，说明是符合条件的一种情况
    // 然后记录下按键按下的状态，通过字符串记录
    for (int i = 1; i <= N; ++i) {
        types[total_types] = types[total_types] + n_2_s(lamps[i]);
    }
    total_types++;
}

void dfs(int key)
{
    // 递归出口
    if (key>4) {
        check();
        return;
    }

    // 当前递归深度的按键 没有被按下，即第 key 个按键没按
    // 没按下，直接进入下一层，即去判断下一个按键的情况
    dfs(key+1);
    // 当前递归深度的按键 被按下，即第 key 个按键是被按下的
    // 是哪个按键就去执行哪个按键的动作
    if (key == 1)
        for (int i = 1; i <= N; ++i)
            lamps[i] = !lamps[i];
    if (key == 2)
        for (int i = 1; i <= N; i += 2)
            lamps[i] = !lamps[i];
    if (key == 3)
        for (int i = 0; i <= N; i += 2)
            lamps[i] = !lamps[i];
    if (key == 4)
        for (int i = 0; i<=N/3; ++i)
            lamps[i*3+1] = !lamps[i*3+1];
    // 记录下哪个按键按下了
    which_key[key] = true;
    // 进入下一层
    dfs(key+1);
    // 回溯，恢复按键
    which_key[key] = false;
    // 回溯，恢复按键被按下之前的状态
    if (key == 1)
        for (int i = 1; i <= N; ++i)
            lamps[i] = !lamps[i];
    if (key == 2)
        for (int i = 1; i <= N; i += 2)
            lamps[i] = !lamps[i];
    if (key == 3)
        for (int i = 0; i <= N; i += 2)
            lamps[i] = !lamps[i];
    if (key == 4)
        for (int i = 0; i<=N/3; ++i)
            lamps[i*3+1] = !lamps[i*3+1];
}

bool cmp(string s1, string s2)
{
    return s1 < s2;
}

int main(void)
{
    ifstream ifile("lamps.in");
    ofstream ofile("lamps.out");

    ifile >> N >> C;
    // 标号为0的不用
    // 从1开始
    for (int i = 0; i <= N; ++i)
        lamps[i] = true;

    int num;
    ifile >> num;
    // 读入亮的灯
    while (num>0) {
        on[num] = true;
        ifile >> num;
    }
    ifile >> num;
    // 读入灭的灯
    while (num>0) {
        off[num] = true;
        ifile >> num;
    }
    // 深搜
    dfs(1);
    // 排序，用cmp
    sort(types, types+total_types, cmp);

    for (int i = 0; i < total_types; ++i) {
        ofile << types[i] << endl;
    }
    if (total_types == 0)
        ofile << "IMPOSSIBLE" << endl;
}