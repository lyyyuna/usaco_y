/*
ID: lorelei3
TASK: packrec
LANG: C++
*/
#if 0
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 105;

typedef struct Rect {
    int width;
    int height;
    bool operator < (const  Rect& r)const{
        return width<r.width || (width==r.width && height<r.height) ;
    }
} Rect;

Rect rotate(Rect r){
    Rect nr;
    nr.height = r.width;
    nr.width = r.height;
    return nr;
}

int max(int a, int b){
    return a>b?a:b;
}

int min(int a, int b){
    return a<b?a:b;
}

int bestarea;
int bestheight[N];
Rect r[4];

void record(Rect r){
    if(r.height*r.width<bestarea || bestarea==0){
        bestarea = r.height*r.width;
        for(int i=0; i<N; ++i)
            bestheight[i]=0;
    }

    if(r.height*r.width==bestarea){
        bestheight[min(r.height,r.width)]=1;
    }
}

void check(){

    int i = 0; 
    Rect rect;

    //case 1
    rect.width=0;
    rect.height=0;
    for(i=0; i<4; ++i){
        rect.width += r[i].width;
        rect.height = max(rect.height, r[i].height);
    }
    record(rect);

    //case 2
    rect.width=0;
    rect.height=0;
    for(i=0; i<3;++i){
        rect.width += r[i].width;
        rect.height = max(rect.height, r[i].height);
    }
    rect.height += r[3].height;
    rect.width = max(rect.width, r[3].width);
    record(rect);

    //case 3
    rect.width = r[0].width + r[1].width;
    rect.height = max(r[0].height, r[1].height);

    rect.width = max(rect.width, r[2].width);
    rect.height += r[2].height;

    rect.width += r[3].width;
    rect.height = max(rect.height, r[3].height);
    record(rect);

    //case 4 5
    rect.width = r[0].width+r[1].width;
    rect.height = max(r[0].height, r[1].height);
    rect.width += max(r[2].width, r[3].width);
    rect.height = max(rect.height , r[2].height+r[3].height);
    record(rect);

    //case 6
    rect.height = max(r[0].height+r[2].height, r[1].height+r[3].height);
    rect.width = r[0].width + r[1].width;
 
    /* do 2 and 1 touch? */
    if(r[0].height < r[1].height)
        rect.width = max(rect.width, r[2].width+r[1].width);
    /* do 2 and 3 touch? */
    if(r[0].height+r[2].height > r[1].height)
        rect.width = max(rect.width, r[2].width+r[3].width);
    /* do 0 and 3 touch? */
    if(r[1].height < r[0].height)
        rect.width = max(rect.width, r[0].width+r[3].width);
 
    /* maybe 2 or 3 sits by itself */
    rect.width = max(rect.width, r[2].width);
    rect.width = max(rect.width, r[3].width);
    record(rect);    

}


void checkrotate(int n){
    if(n==4){
        check();
        return;
    }
    checkrotate(n+1);
    r[n] = rotate(r[n]);
    checkrotate(n+1);
    r[n] = rotate(r[n]);
}

void checkpermute(){
    sort(r, r+4);
    do{
        checkrotate(0);
    }while(next_permutation(r, r+4));
}

int main(){

    int i;
    ifstream in("packrec.in");
    ofstream out("packrec.out");

    for(i=0; i<4; ++i)
        in>>r[i].width>>r[i].height;

    checkpermute();

    out<<bestarea<<endl;
    for(i=0;i<N;++i){
        if(bestheight[i]){
            out<<i<<" "<<bestarea/i<<endl;
        }
    }

    return 0;
}
#endif

#include <fstream>
#include <algorithm>

using namespace::std;

struct Rect
{
    int width;
    int height;
};

bool operator < (const Rect &l, const  Rect &r)
{
    return l.width<r.width || (l.width==r.width && l.height<r.height);
}

Rect rotate(Rect r)
{
    Rect nr;
    
    nr.height = r.width;
    nr.width = r.height;
    return nr;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

const int N = 101;
int tot;
int bestarea;
bool bestht[N]={false};

void record(Rect r)
{
    if (r.height*r.width < bestarea || bestarea == 0) {
        bestarea = r.width * r.height;
        for (int i = 0; i != N; ++i)
            bestht[i] = false;
    }
    if (r.width * r.height == bestarea)
        bestht[min(r.width, r.height)] = true;
}

void check(Rect r[])
{
    int i = 0; 
    Rect rect;

    //case 1
    rect.width=0;
    rect.height=0;
    for(i=0; i<4; ++i){
        rect.width += r[i].width;
        rect.height = max(rect.height, r[i].height);
    }
    record(rect);

    //case 2
    rect.width=0;
    rect.height=0;
    for(i=0; i<3;++i){
        rect.width += r[i].width;
        rect.height = max(rect.height, r[i].height);
    }
    rect.height += r[3].height;
    rect.width = max(rect.width, r[3].width);
    record(rect);

    //case 3
    rect.width = r[0].width + r[1].width;
    rect.height = max(r[0].height, r[1].height);

    rect.width = max(rect.width, r[2].width);
    rect.height += r[2].height;

    rect.width += r[3].width;
    rect.height = max(rect.height, r[3].height);
    record(rect);

    //case 4 5
    rect.width = r[0].width+r[1].width;
    rect.height = max(r[0].height, r[1].height);
    rect.width += max(r[2].width, r[3].width);
    rect.height = max(rect.height , r[2].height+r[3].height);
    record(rect);

    //case 6
    rect.height = max(r[0].height+r[2].height, r[1].height+r[3].height);
    rect.width = r[0].width + r[1].width;
 
    /* do 2 and 1 touch? */
    if(r[0].height < r[1].height)
        rect.width = max(rect.width, r[2].width+r[1].width);
    /* do 2 and 3 touch? */
    if(r[0].height+r[2].height > r[1].height)
        rect.width = max(rect.width, r[2].width+r[3].width);
    /* do 0 and 3 touch? */
    if(r[1].height < r[0].height)
        rect.width = max(rect.width, r[0].width+r[3].width);
 
    /* maybe 2 or 3 sits by itself */
    rect.width = max(rect.width, r[2].width);
    rect.width = max(rect.width, r[3].width);
    record(rect);  

}

void checkrotate(Rect r[], int n)
{
    if (n == 4) {
        check(r);
        return;
    }

    checkrotate(r, n+1);
    r[n] = rotate(r[n]);
    checkrotate(r, n+1);
    r[n] = rotate(r[n]);
}

void checkpermute(Rect r[])
{
    sort(r, r+4);
    do {
        checkrotate(r, 0);
    } while(next_permutation(r, r+4));
}

int main (void)
{
    ifstream ifile("packrec.in");
    ofstream ofile("packrec.out");

    Rect r[4];
    for (int i = 0; i != 4; ++i)
        ifile >> r[i].width >> r[i].height;

    checkpermute(r);

    ofile << bestarea << endl;
    for (int i = 0; i != N; ++i)
        if (bestht[i])
            ofile << i << " " << bestarea/i << endl;

    return 0;
}