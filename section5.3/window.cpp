/*
ID: lyyyuna
PROG: window
LANG: C++
*/

#include <fstream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <string>

using namespace::std;

ifstream ifile("window.in");
ofstream ofile("window.out");

struct Win
{
    int x1, y1;
    int x2, y2;
    long area;
    char ID;
};

int height;         // ͼ����ܸ߶�
int windows[200];   // ��¼ÿ�����ڵ�λ��
Win desktop[200]; // ��¼һ�����棬�㼶��ÿ�����ڵľ�������

void init(string s)
{
    windows[(int)s[2]] = height; // ������߲�
    desktop[height].ID = s[2];   // ��¼����ID

    s.erase(0, 4);
    string sub = s.substr(0, s.find(','));
    int tmp = 0;
    for (int i = 0; i < sub.length(); ++i)
        tmp = tmp*10 + sub[i]-'0';
    desktop[height].x1 = tmp;
    s.erase(0, sub.length()+1);

    sub = s.substr(0, s.find(','));
    tmp = 0;
    for (int i = 0; i < sub.length(); i++)
        tmp = tmp*10 + sub[i]-'0';
    desktop[height].y1 = tmp;
    s.erase(0, sub.length()+1);

    sub = s.substr(0,s.find(','));
    tmp = 0;
    for(int i = 0; i < sub.length(); i++)
        tmp = tmp*10 + sub[i]-'0';
    desktop[height].x2 = tmp;
    s.erase(0, sub.length()+1);

    sub = s.substr(0, s.find(')'));
    tmp = 0;
    for(int i=0; i < sub.length(); i++)
        tmp = tmp*10 + sub[i]-'0';
    desktop[height].y2 = tmp;
    s.erase(0, sub.length()+1);

    if(desktop[height].y1 > desktop[height].y2)
        swap(desktop[height].y1, desktop[height].y2);

    if(desktop[height].x1 > desktop[height].x2)
        swap(desktop[height].x1, desktop[height].x2);

    desktop[height].area = (desktop[height].x1 - desktop[height].x2)
                            * (desktop[height].y1 - desktop[height].y2);
}

long cover(int x1, int x2, int y1, int y2, int k)
{
    while ( k<=height && 
            (x1>=desktop[k].x2 || x2<=desktop[k].x1 ||
             y1>=desktop[k].y2 || y2<=desktop[k].y1) )
        k++;
    if (k > height)
        return (x1-x2)*(y1-y2);

    long area1 = 0;
    if (x1 <= desktop[k].x1) {
        area1 += cover(x1, desktop[k].x1, y1, y2, k+1);
        x1 = desktop[k].x1;
    }
    if (x2 >= desktop[k].x2) {
        area1 += cover(desktop[k].x2, x2, y1, y2, k+1);
        x2 = desktop[k].x2;
    }
    if (y1 <= desktop[k].y1) {
        area1 += cover(x1, x2, y1, desktop[k].y1, k+1);
        y1 = desktop[k].y1;
    }
    if (y2 >= desktop[k].y2) {
        area1 += cover(x1, x2, desktop[k].y2, y2, k+1);
        y2 = desktop[k].y2;
    }

    return area1;
}

double calc(char ch)
{
    int tmpk = windows[ (int)ch ];
    long area = cover(desktop[tmpk].x1,
                      desktop[tmpk].x2,
                      desktop[tmpk].y1,
                      desktop[tmpk].y2, tmpk+1);
    return 100 * (double)area / (double)desktop[tmpk].area;
}

int main(void)
{
    ofile << fixed << setprecision(3);

    string s;
    while (getline(ifile, s)) {
        char ch = s[0];
        switch (ch) {
        case 'w':
            {
                height ++;
                init(s);
            }
                  break;
        case 't': 
            {
                int tmpk = windows[ (int)s[2] ];
                windows[ (int)s[2] ] = height;
                Win tmpwin = desktop[tmpk];
                for (int i = tmpk; i < height; ++i) {
                    desktop[i] = desktop[i+1];
                    windows[ (int)desktop[i].ID ] --;
                }
                desktop[height] = tmpwin;
            }
                  break;
        case 'b':
            {
                int tmpk = windows[ (int)s[2] ];
                windows[ (int)s[2] ] = 1;
                Win tmpwin = desktop[tmpk];
                for (int i = tmpk; i > 1; --i) {
                    desktop[i] = desktop[i-1];
                    windows[ (int)desktop[i].ID ] ++;
                }
                desktop[1] = tmpwin;
            }
                break;
        case 'd':
            {
                int tmpk = windows[ (int)s[2] ];
                windows[ (int)s[2] ] = 0;
                for (int i = tmpk; i < height; ++i) {
                    desktop[i] = desktop[i+1];
                    windows[ (int)desktop[i].ID ] --;
                }
                height --;
            }
                break;
        case 's':
            {
                ofile << calc(s[2]) << endl;
            }
                break;
        }
    }
}
