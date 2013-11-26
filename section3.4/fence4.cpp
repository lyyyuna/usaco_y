/*
ID: lyyyuna
PROG: fence4
LANG: C++
*/

#include <fstream>
#include <cmath>

using namespace::std;

struct Point
{
    double x;
    double y;
};

struct Edge
{
    Point start;
    Point end;
};

const int MAXE = 10000;
const double EPS = 1e-6;
Point person;
Edge edges[MAXE];
int e_nums;

/// 基本图形API
bool isSame(Point a, Point b)
{
    if (fabs(a.x - b.x) >= EPS)
        return false;
    if (fabs(a.y - b.y) >= EPS)
        return false;
    return true;
}

typedef Point Vect;
// 把向量转换为以原点为起点的向量
Vect vec(Point a, Point b)
{
    b.x = b.x - a.x;
    b.y = b.y - a.y;
    return b;
}
// 计算二维叉积
double crossProduct(Vect a, Vect b)
{
    return (a.x*b.y - b.x*a.y);
}

bool isDiff_side(Edge a, Edge b)
{
    Vect va = vec(a.start, a.end);
    double pro1 = crossProduct(va, vec(a.start, b.start));
    double pro2 = crossProduct(va, vec(a.start, b.end));
    // 两者叉积相反，说明b的两个端点 在 a向量的两侧
    if (pro1 * pro2 <= 0)
        return true;
    return false;
}

bool isCross(Edge a, Edge b)
{
    return ( isDiff_side(a, b) && isDiff_side(b,a) );
}
/// 基本图形API

bool isSeen(Edge test_edge, int which_edge)
{
    if (isSame(test_edge.start, test_edge.end))
        return false;

    // 连接人和测试边两端点
    Edge left, right;
    left.start = right.start = person;
    left.end = test_edge.start;
    right.end = test_edge.end;

    bool flag = false;
    for (int i = 1; i <= e_nums; ++i)
        if (i != which_edge) {
            bool b1 = isCross(left, edges[i]);
            bool b2 = isCross(right, edges[i]);
            // 完全被挡住
            if (b1 && b2)
                return false;
            flag |= b1 || b2; //判断有没有被挡住，被挡住，要继续拆分测试边，才能测试出到底有没有被完全挡住
        }
    // 没有被挡住
    if (flag == false)
        return true;

    // 二分法
    // 把test_edge这条边分成两部分
    Edge new_edge_l, new_edge_r;
    new_edge_l.start = test_edge.start;
    new_edge_l.end.x = (test_edge.start.x + test_edge.end.x) / 2;
    new_edge_l.end.y = (test_edge.start.y + test_edge.end.y) / 2;
    new_edge_r.start = new_edge_l.end;
    new_edge_r.end = test_edge.end;

    if (isSeen(new_edge_l, which_edge))
        return true;
    if (isSeen(new_edge_r, which_edge))
        return true;

    return false;
}

int main(void)
{
    ifstream ifile("fence4.in");
    ofstream ofile("fence4.out");

    int N;
    ifile >> N;
    ifile >> person.x >> person.y;
    Point tmp1, tmp2;
    ifile >> tmp1.x >> tmp1.y;
    for (int i = 2; i <= N; ++i) {
        ifile >> tmp2.x >> tmp2.y;
        edges[++e_nums].start = tmp1;
        edges[e_nums].end = tmp2;
        tmp1 = tmp2;
    }
    edges[++e_nums].start = tmp1;
    edges[e_nums].end = edges[1].start;
    // 读入所有数据，存入边信息

    int total_seen = 0;
    bool canc[MAXE] = {false};
    for (int i = 1; i <= e_nums; ++i)
        if (canc[i] = isSeen(edges[i], i))
            total_seen ++;
    ofile << total_seen << endl;

    for (int i = 1; i <= e_nums-2; ++i) {
        if (canc[i] == true) {
            ofile << (int)edges[i].start.x << " " << (int)edges[i].start.y << " "
            << (int)edges[i].end.x << " " << (int)edges[i].end.y << endl;
        }
    }

    if (canc[e_nums] == true) {
        int i = e_nums;
        ofile << (int)edges[i].end.x << " " << (int)edges[i].end.y << " "
            << (int)edges[i].start.x << " " << (int)edges[i].start.y << endl;
    }

    if (canc[e_nums-1] == true) {
        int i = e_nums-1;
        ofile << (int)edges[i].start.x << " " << (int)edges[i].start.y << " "
            << (int)edges[i].end.x << " " << (int)edges[i].end.y << endl;
    }
}