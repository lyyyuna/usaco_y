/*
ID: lyyyuna
PROG: castle
LANG: C++
*/

#include <fstream>
#include <string>

using namespace::std;

const int MAX = 50+1;
int walls[MAX][MAX];    // 用来存储每个单元墙的情况
int room_color[MAX][MAX] = {0}; // 用来存储每个单元的颜色情况，如果是同一个颜色，则在同一个房间
int num_rooms[MAX*MAX] = {0};   // 存储房间数，实际数组长度为房间数

int max_number;         // 拆掉墙后，最大房间的面积
int remove_row, remove_col;     // 去掉的位置
char remove_dest;               // 去掉的方向，北或东

void floodfill(int y, int x, int which_room, int *room_area)
{
    // 有颜色，不用再搜
    // 递归出口
    if (room_color[y][x])
        return ;
    // 面积加1
    (*room_area) ++;
    // 将新搜到的单元标记为某个房间的颜色
    room_color[y][x] = which_room;
// 位运算，和单片机里面很相似
// 快速判断某一面是否有墙
#define IS_W(w)     (w & 1)
#define IS_N(w)     (w & 2)
#define IS_E(w)     (w & 4)
#define IS_S(w)     (w & 8)
    // 判断有墙
    // 例如，西面没有墙，则往西面继续搜素
    if (IS_W(walls[y][x]) == 0)
        floodfill(y, x-1, which_room, room_area);
    if (IS_N(walls[y][x]) == 0)
        floodfill(y-1, x, which_room, room_area);
    if (IS_E(walls[y][x]) == 0)
        floodfill(y, x+1, which_room, room_area);
    if (IS_S(walls[y][x]) == 0)
        floodfill(y+1, x, which_room, room_area);

    // 都有墙，则退出递归
    return ;
}

void test_remove(int y, int x, char dest)
{
    //int which_room = room_color[y][x];
    switch (dest) {
    case 'N':
        // 把两个房间合并比较面积大小
        if (num_rooms[room_color[y][x]] + 
            num_rooms[room_color[y-1][x]]
            > max_number) {
                remove_row = y;
                remove_col = x;
                remove_dest = dest;
                max_number = num_rooms[room_color[y][x]] + 
            num_rooms[room_color[y-1][x]];
            } break;
    case 'E':
        if (num_rooms[room_color[y][x]] + 
            num_rooms[room_color[y][x+1]]
            > max_number) {
                remove_row = y;
                remove_col = x;
                remove_dest = dest;
                max_number = num_rooms[room_color[y][x]] + 
            num_rooms[room_color[y][x+1]];
            } break;

    }
}

int main(void)
{
    ifstream ifile("castle.in");
    ofstream ofile("castle.out");

    int M, N;
    ifile >> M >> N;
    for (int i = 0; i < N; ++i) 
        for (int j = 0; j < M; ++j)
            ifile >> walls[i][j];

    int max_area(0);    // 拆之前最大的房间的面积
    int which_room(0);  // 房间数，以下的遍历有一间就会加1，从1开始
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            // 没有搜过的房间是0
            // 搜过的则是相应的房间的编号
            if (room_color[i][j] == 0) {
                int area(0);    // 统计面积
                // 搜索，先搜第一间房
                floodfill(i, j, ++which_room, &area);
                // 记录下当前房间的面积
                num_rooms[which_room] = area;
                // 记录最大面积
                max_area = max(area, max_area);
            }

    // 根据题目要求，要从最西最南开始拆
    // 并且先选最西的，两个最西的情况下选最南的
    // 所以以下的循环是从 0..M      N-1..0 展开的
    for (int i = 0; i < M; ++i)
        for (int j = N-1; j >= 0; --j) {
            // 颜色不一样就说明是不同的房间
            if (j > 0 && room_color[j][i] != room_color[j-1][i])
                test_remove(j, i, 'N');
            if (i < M-1 && room_color[j][i] != room_color[j][i+1])
                test_remove(j, i, 'E');
        }

    ofile << which_room << endl;
    ofile << max_area << endl;
    ofile << max_number << endl;
    ofile << remove_row+1 << " " << remove_col+1 << " ";
    ofile << remove_dest << endl;

    return 0;
}