/*
ID: lyyyuna
PROG: comehome
LANG: C++
*/

#include <fstream>

using namespace::std;

const int INFTY = 9999999;

int char_2_int(char c)
{
    if ((c>='a') && (c<='z'))
        return (c-'a'+27);
    if ((c>='A') && (c<='Z'))
        return (c-'A'+1);
}

int main(void)
{
    ifstream ifile("comehome.in");
    ofstream ofile("comehome.out");

    int num_roads;
    ifile >> num_roads;
    int map[26*2+1][26*2+1];
    // 先赋值成无穷
    for (int i = 1; i <= 52; ++i)
        for (int j = 1; j <= 52; ++j) {
            map[i][j] = INFTY;
        }
    // 读入，大小写分开，直接当成不同的点
    for (int i = 1; i <= num_roads; ++i) {
        char c;
        int x, y ,distance;
        ifile >> c;
        x = char_2_int(c);
        ifile >> c;
        y = char_2_int(c);
        ifile >> distance;
        if (distance < map[x][y]) {
            map[x][y] = distance;
            map[y][x] = distance;
        }
    }

    // Floyd，算出最小距离
    for (int k = 1; k <= 52; ++k)
        for (int i = 1; i <= 52; ++i)
            for (int j = 1; j <= 52; ++j)
                if (map[i][k] + map[k][j] < map[i][j])
                    map[i][j] = map[i][k] + map[k][j];

    int min_road = INFTY;
    int cow;
    for (int i = 1; i <= 25; ++i)
        if (map[i][26] < min_road) {
            min_road = map[i][26];
            cow = i;
        }

    ofile << (char)(cow + 'A' - 1) << " " << min_road << endl;
}