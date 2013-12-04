/*
ID: lyyyuna
PROG: starry
LANG: C++
*/

#include <fstream>
#include <cstring>

using namespace::std;

// ���巽��
struct Dir
{
    int x;
    int y;
} dir[8] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

// ����ÿ������ͼ
struct Star
{
    int w, h;
    char sky_map[101][101];
};
Star Constellation[26]; int Connum;
Star temp;

// �ǿ�ͼ
int W, H;
char sky[101][101];

// ÿ���������������ҷ�Χ
int x1, x2, yy1, y2;

// ��ÿһ������һ������ǣ�Ⱦ��ͬһ����ɫ
void floodfill(int y, int x, char color)
{
    sky[y][x] = color;

    x1 = min(x1, x);
    x2 = max(x2, x);
    yy1 = min(yy1, y);
    y2 = max(y2, y);

    for (int i = 0; i < 8; ++i) {
        int ty = y + dir[i].y;
        int tx = x + dir[i].x;
        if (ty>=0 && ty<H && tx < W && tx>=0 && sky[ty][tx]!=color && sky[ty][tx]!='0')
            floodfill(ty, tx, color);
    }
}

int main(void)
{
    ifstream ifile("starry.in");
    ofstream ofile("starry.out");

    ifile >> W >> H;
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
            ifile >> sky[i][j];

    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j) {
            // ��ǰλ��������
            // ���һ�û�б�����Ⱦɫ��
            if (sky[i][j] == '1') {
                x1 = W; x2 = 0;
                yy1 = H; y2 = 0;
                // ��Ⱦ�� ��2��
                floodfill(i, j, '2');

                memset(temp.sky_map, '0', sizeof(temp.sky_map));
                // ������Ϊ��2����ɫ�����Ǹ��Ƴ���
                for (int ii = yy1; ii <= y2; ++ii)
                    for (int jj = x1; jj <= x2; ++jj)
                        if (sky[ii][jj] == '2')
                            temp.sky_map[ii-yy1][jj-x1] = sky[ii][jj];
                // ���·�Χ
                temp.w = x2-x1+1;
                temp.h = y2-yy1+1;

                bool flag1 = false;
                bool flag2 = false;
                
                // Connum�ǵ�ǰ�Ѿ���ʶ��������������
                for (int k = 0; k < Connum; ++k) {
                    // ÿ��ת90��
                    for (int l = 0; l < 4; ++l) {
                        // ˳ʱ����ת90
                        Star temp1 = temp;
                        temp.h = temp1.w;
                        temp.w = temp1.h;
                        for (int ii = 0; ii < temp1.h; ++ii)
                            for (int jj = 0; jj < temp1.w; ++jj)
                                temp.sky_map[jj][temp.w-ii-1] = temp1.sky_map[ii][jj];

                        // �ж����Ѿ���ʶ�������� Constellation ���Ƿ�����ͬ��
                        flag2 = true;
                        if (temp.w!=Constellation[k].w || temp.h!=Constellation[k].h)
                            flag2 = false;
                        if (flag2 == true) {
                            for (int ii = 0; ii < temp.h; ++ii) 
                                for (int jj = 0; jj < temp.w; ++jj)
                                    if (temp.sky_map[ii][jj] != Constellation[k].sky_map[ii][jj]) {
                                        flag2 = false;
                                        break;
                                    }
                        }
                        if (flag2 == true) {
                            // ������Ѿ����ֹ��ģ�ÿ���Ǻ� Constellation[k] ����������Ƚ�
                            // ��ͬ���������·��ֵ�����Ⱦ�� Constellation[k] һ������ɫ
                            floodfill(i, j, (char)('a'+k));
                            flag1 = true;
                            break;
                        }

                        // // �ж����Ѿ���ʶ�������� Constellation ���Ƿ�����ͬ�ģ����Ǿ�����ͬ
                        flag2 = true;
                        if (temp.w!=Constellation[k].w || temp.h!=Constellation[k].h)
                            flag2 = false;
                        if (flag2 == true) {
                            for (int ii = 0; ii < temp.h; ++ii) 
                                for (int jj = 0; jj < temp.w; ++jj) 
                                    if (temp.sky_map[ii][jj] != Constellation[k].sky_map[temp.h-ii-1][jj]) {
                                        flag2 = false;
                                        break;
                                    }
                        }
                        if (flag2 == true) {
                            floodfill(i, j, (char)('a'+k));
                            flag1 = true;
                            break;
                        }
                    }
                    // ˵���ҵ���
                    if (flag1 == true)
                        break;
                }

                // û�ҵ�������һ��������Ⱦ�� Connum+'a' 
                if (flag1 == false) {
                    floodfill(i, j, (char)(Connum+'a'));
                    Constellation[Connum] = temp;
                    Connum++;
                }
            }
        }

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j)
            ofile << sky[i][j];
        ofile << endl;
    }
}