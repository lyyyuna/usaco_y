/*
ID: lyyyuna
PROG: fc
LANG: C++
*/
/*
预处理要对所有点进行排序。找出一个最左边的点，如果有多个再找最下
边的。然后以这个点为准对其他所有点按照逆时针顺序排序（其实顺时针
也可以，但是大多数人的习惯是逆时针），这里要用到向量叉积。

先开一个栈，分别放入第1、2、3个点（这三个点显然都在凸包中）。然后
从第4个点开始枚举。如果栈顶元素指向当前点的有向线段与栈顶下方元素
指向栈顶的有向线段构成右手系（就是说往右转啦，这里又要用到叉积），
则栈顶元素出栈，重复以上过程直到这两个线段构成左手系，把当前点放入
栈顶。这样到第n个点枚举完后，栈中的元素就构成了一个凸包，而且还是
有序的。
*/

#include <fstream>
#include <cstring>
#include <cmath>
#include <iomanip>

using namespace::std;

struct Node
{
    double x;
    double y;
} p_left; // 最左边的点

double cross_product(Node &c, Node &a, Node &b)
{
    return (a.x-c.x)*(b.y-c.y) - (b.x-c.x)*(a.y-c.y);
}

int cmp(const void *a, const void *b)
{
    Node x = *(Node *)a;
    Node y = *(Node *)b;
    return (cross_product(p_left, x, y)<0);
}

double dis(Node &a, Node &b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

int main(void)
{
    ifstream ifile("fc.in");
    ofstream ofile("fc.out");
    int N;
    ifile >> N;

    Node p[10000];
    int p_index;
    p_left.x = 1000000000;
    p_left.y = 1000000000;
    for (int i = 0; i < N; ++i) {
        ifile >> p[i].x >> p[i].y;
        // 找出最左边的点
        if (p[i].x < p_left.x) {
            p_left = p[i];
            p_index = i;
        }
        else if (p[i].x==p_left.x && p[i].y<p_left.y) {
            p_left = p[i];
            p_index = i;
        }
    }

    int j = -1;
    Node p2[10000];
    // 除去最左边的点之后，
    // 以最左边的点为基准，按照 叉积 进行排序
    for (int i = 0; i < N; ++i)
        if (i != p_index) {
            j ++;
            p2[j] = p[i];
        }
    qsort(p2, N-1, sizeof(Node), cmp);

    Node stack[10000];
    stack[0] = p_left;
    stack[1] = p2[0];
    int frame = 2;
    // 如果栈顶元素指向当前点的有向线段与栈顶下方元素指向栈顶的
    // 有向线段构成右手系（就是说往右转啦，这里又要用到叉积），则
    // 栈顶元素出栈，重复以上过程直到这两个线段构成左手系，把当前
    // 点放入栈顶。
    for (int i = 1; i < N-1; ++i) {
        stack[frame] = p2[i];
        while (cross_product(stack[frame-2], stack[frame-1], stack[frame]) <= 0) {
            frame --;
            stack[frame] = p2[i];
        }
        frame ++;
    }

    double result = 0;
    for (int i = 1; i < frame; ++i)
        result += dis(stack[i-1], stack[i]);
    result += dis(stack[0], stack[frame-1]);

    // <iomanip>
    ofile << fixed << setprecision(2) << result << endl;

    return 0;

}