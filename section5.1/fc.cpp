/*
ID: lyyyuna
PROG: fc
LANG: C++
*/
/*
Ԥ����Ҫ�����е���������ҳ�һ������ߵĵ㣬����ж����������
�ߵġ�Ȼ���������Ϊ׼���������е㰴����ʱ��˳��������ʵ˳ʱ��
Ҳ���ԣ����Ǵ�����˵�ϰ������ʱ�룩������Ҫ�õ����������

�ȿ�һ��ջ���ֱ�����1��2��3���㣨����������Ȼ����͹���У���Ȼ��
�ӵ�4���㿪ʼö�١����ջ��Ԫ��ָ��ǰ��������߶���ջ���·�Ԫ��
ָ��ջ���������߶ι�������ϵ������˵����ת����������Ҫ�õ��������
��ջ��Ԫ�س�ջ���ظ����Ϲ���ֱ���������߶ι�������ϵ���ѵ�ǰ�����
ջ������������n����ö�����ջ�е�Ԫ�ؾ͹�����һ��͹�������һ���
����ġ�
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
} p_left; // ����ߵĵ�

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
        // �ҳ�����ߵĵ�
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
    // ��ȥ����ߵĵ�֮��
    // ������ߵĵ�Ϊ��׼������ ��� ��������
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
    // ���ջ��Ԫ��ָ��ǰ��������߶���ջ���·�Ԫ��ָ��ջ����
    // �����߶ι�������ϵ������˵����ת����������Ҫ�õ����������
    // ջ��Ԫ�س�ջ���ظ����Ϲ���ֱ���������߶ι�������ϵ���ѵ�ǰ
    // �����ջ����
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