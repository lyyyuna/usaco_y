/*
ID: lyyyuna
PROG: picture
LANG: C++
*/

#include <fstream>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace::std;

struct Segment
{
    int st, ed, ht;
    bool flag;
    Segment(int _st=0, int _ed=0, int _ht=0, bool _flag=false): st(_st), ed(_ed), ht(_ht), flag(_flag){}
};
Segment hor[10001], ver[10001];

struct SegTree
{
    int st, ed;
    int level;
    int len;
    bool isLeaf;

    SegTree *left;
    SegTree *right;

    SegTree(int _st, int _ed): st(_st), ed(_ed), level(0), len(0) {
        if (st+1 == ed)
            isLeaf = true;
        else {
            int mid = (st+ed)/2;
            left = new SegTree(st, mid);
            right = new SegTree(mid, ed);
            isLeaf = false;
        }
    }
};

int N;

// for quicksort
int cmp(const void *a, const void *b)
{
    Segment *pa = (Segment *)a;
    Segment *pb = (Segment *)b;
    
    if (pa->ht > pb->ht)
        return 1;
    if (pa->ht == pb->ht && pb->flag==true)
        return 1;
    return -1;
}

void insert(SegTree *r, int st, int ed, int flag)
{
    if (st <= r->st && ed >= r->ed) {
        r->level += flag;
        r->len = r->ed - r->st;
    } else {
        int mid = (r->st + r->ed) / 2;
        if (st < mid)
            insert(r->left, st, ed, flag);
        if (ed > mid)
            insert(r->right, st, ed, flag);
    }

    if (r->level == 0) {
        if (r->isLeaf)
            r->len = 0;
        else
            r->len = r->left->len + r->right->len;
    }
}

int main(void)
{
    ifstream ifile("picture.in");
    ofstream ofile("picture.out");
    ifile >> N;
    int lx, ly, rx, ry;
    for (int i = 1; i <= N; ++i) {
        ifile >> lx >> ly >> rx >> ry;
        hor[i*2-1] = Segment(lx, rx, ly, true);
        hor[i*2] = Segment(lx, rx, ry, false);
        ver[i*2-1] = Segment(ly, ry, lx, true);
        ver[i*2] = Segment(ly, ry, rx, false);
    }

    N = N*2;
    qsort(hor+1, N, sizeof(Segment), cmp);
    qsort(ver+1, N, sizeof(Segment), cmp);

    int length = 0;
    SegTree *root = new SegTree(-10000, 10000);
    int old;
    for (int i = 1; i <= N; ++i) {
        old = root->len;
        insert(root, hor[i].st, hor[i].ed, (hor[i].flag?1:-1));
        length += abs( old - root->len );
    }
    for (int i = 1; i <= N; ++i) {
        old = root->len;
        insert(root, ver[i].st, ver[i].ed, (ver[i].flag?1:-1));
        length += abs( old - root->len );
    }

    ofile << length << endl;

    return 0;
}