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

/// ����ͼ��API
bool isSame(Point a, Point b)
{
    if (fabs(a.x - b.x) >= EPS)
        return false;
    if (fabs(a.y - b.y) >= EPS)
        return false;
    return true;
}

typedef Point Vect;
// ������ת��Ϊ��ԭ��Ϊ��������
Vect vec(Point a, Point b)
{
    b.x = b.x - a.x;
    b.y = b.y - a.y;
    return b;
}
// �����ά���
double crossProduct(Vect a, Vect b)
{
    return (a.x*b.y - b.x*a.y);
}

bool isDiff_side(Edge a, Edge b)
{
    Vect va = vec(a.start, a.end);
    double pro1 = crossProduct(va, vec(a.start, b.start));
    double pro2 = crossProduct(va, vec(a.start, b.end));
    // ���߲���෴��˵��b�������˵� �� a����������
    if (pro1 * pro2 <= 0)
        return true;
    return false;
}

bool isCross(Edge a, Edge b)
{
    return ( isDiff_side(a, b) && isDiff_side(b,a) );
}
/// ����ͼ��API

bool isSeen(Edge test_edge, int which_edge)
{
    if (isSame(test_edge.start, test_edge.end))
        return false;

    // �����˺Ͳ��Ա����˵�
    Edge left, right;
    left.start = right.start = person;
    left.end = test_edge.start;
    right.end = test_edge.end;

    bool flag = false;
    for (int i = 1; i <= e_nums; ++i)
        if (i != which_edge) {
            bool b1 = isCross(left, edges[i]);
            bool b2 = isCross(right, edges[i]);
            // ��ȫ����ס
            if (b1 && b2)
                return false;
            flag |= b1 || b2; //�ж���û�б���ס������ס��Ҫ������ֲ��Աߣ����ܲ��Գ�������û�б���ȫ��ס
        }
    // û�б���ס
    if (flag == false)
        return true;

    // ���ַ�
    // ��test_edge�����߷ֳ�������
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
    // �����������ݣ��������Ϣ

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