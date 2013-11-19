/*
Id£ºlyyyuna
PROG: rect1
LANG: C++
*/

#include <fstream>

using namespace::std;

const int MAXN = 1000+1;
int x1[MAXN], Y1[MAXN];
int x2[MAXN], y2[MAXN];
int color[MAXN] = {1};
int area[2500+1];
int N;

void
rect_cal(int lx, int ly,
        int rx, int ry,
        int color_index, int layer)
{
    if (lx == rx || ly == ry)
        return;
    if (layer > N)
        area[color_index] += (ry-ly) * (rx-lx);
    else {
        if (ly<Y1[layer]) 
            rect_cal(min(x2[layer],lx),ly,min(x2[layer],rx),min(Y1[layer],ry),color_index,layer+1);
        if (rx>x2[layer]) 
            rect_cal(max(x2[layer],lx),min(y2[layer],ly),rx,min(y2[layer],ry),color_index,layer+1);
        if (ry>y2[layer]) 
            rect_cal(max(x1[layer],lx),max(y2[layer],ly),max(x1[layer],rx),ry,color_index,layer+1);
        if (lx<x1[layer]) 
            rect_cal(lx,max(Y1[layer],ly),min(x1[layer],rx),max(Y1[layer],ry),color_index,layer+1);
    }
}

int 
main(void)
{
    ifstream ifile("rect1.in");
    ofstream ofile("rect1.out");
    x1[0] = Y1[0] = 0;

    ifile >> x2[0] >> y2[0] >> N;

    for (int i = 1; i <= N; ++i) {
        ifile >> x1[i] >> Y1[i]
            >> x2[i] >> y2[i]
            >> color[i];
    }
    area[color[N]] += (x2[N]-x1[N]) * (y2[N]-Y1[N]);

    for (int i = N-1; i >= 0; --i) {
        rect_cal(x1[i], Y1[i], x2[i], y2[i], color[i], i+1);
    }

    for (int i = 1; i <= 2500; ++i)
        if (area[i])
            ofile << i << " " << area[i] << endl;

    return 0;
}