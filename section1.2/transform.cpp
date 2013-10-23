/*
ID: lyyyuna
LANG: C++
PROG: transform
*/

#include <fstream>

using namespace::std;

const int MAX = 15;

class matrix
{
public:
    char a[MAX][MAX];
    int actual_size;
};


matrix rotate_left(matrix aa) {
    matrix bb = aa;
    for (int i = 0; i != bb.actual_size; ++i)
        for (int j = 0; j != bb.actual_size; ++j)
            bb.a[j][bb.actual_size-1-i] = aa.a[i][j];
    return bb;
}
matrix reflect(matrix aa) {
    matrix bb = aa;
    for (int i = 0; i != bb.actual_size; ++i)
        for (int j = 0; j != bb.actual_size; ++j)
            bb.a[i][bb.actual_size-1-j] = aa.a[i][j];
    return bb;
}

inline bool operator== (const matrix &aa, const matrix &bb)
{
    int size = aa.actual_size;
    for (int i = 0; i != size; ++i)
        for (int j = 0; j != size; ++j)
            if (aa.a[i][j] != bb.a[i][j])
                return false;
    return true;
}

inline bool operator!= (const matrix &aa, const matrix &bb)
{
    return !(aa == bb);
}

int main(void)
{
    ifstream ifile("transform.in");
    ofstream ofile("transform.out");
    int num;
    matrix before, after;

    ifile >> num;
    before.actual_size = after.actual_size = num;

    for (int i = 0; i != num; ++i)
        for (int j = 0; j != num; ++j)
            ifile >> before.a[i][j];
    for (int i = 0; i != num; ++i)
        for (int j = 0; j != num; ++j)
            ifile >> after.a[i][j];

    int ans(0);
    if (after == rotate_left(before))
        ans = 1;
    else if (after == rotate_left(rotate_left(before)))
        ans = 2;
    else if (after == rotate_left(rotate_left(rotate_left(before))))
        ans = 3;
    else if (after == reflect(before))
        ans = 4;
    else if (after == rotate_left(reflect(before)) 
        || after == rotate_left(rotate_left(reflect(before)))
        || after == rotate_left(rotate_left(rotate_left(reflect(before)))))
        ans = 5;
    else if (after == before)
        ans = 6;
    else
        ans = 7;

    ofile << ans << endl;
}