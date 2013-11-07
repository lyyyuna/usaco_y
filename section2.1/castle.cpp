/*
ID: lyyyuna
PROG: castle
LANG: C++
*/

#include <fstream>
#include <string>

using namespace::std;

const int MAX = 50+1;
int walls[MAX][MAX];    // �����洢ÿ����Ԫǽ�����
int room_color[MAX][MAX] = {0}; // �����洢ÿ����Ԫ����ɫ����������ͬһ����ɫ������ͬһ������
int num_rooms[MAX*MAX] = {0};   // �洢��������ʵ�����鳤��Ϊ������

int max_number;         // ���ǽ����󷿼�����
int remove_row, remove_col;     // ȥ����λ��
char remove_dest;               // ȥ���ķ��򣬱���

void floodfill(int y, int x, int which_room, int *room_area)
{
    // ����ɫ����������
    // �ݹ����
    if (room_color[y][x])
        return ;
    // �����1
    (*room_area) ++;
    // �����ѵ��ĵ�Ԫ���Ϊĳ���������ɫ
    room_color[y][x] = which_room;
// λ���㣬�͵�Ƭ�����������
// �����ж�ĳһ���Ƿ���ǽ
#define IS_W(w)     (w & 1)
#define IS_N(w)     (w & 2)
#define IS_E(w)     (w & 4)
#define IS_S(w)     (w & 8)
    // �ж���ǽ
    // ���磬����û��ǽ�����������������
    if (IS_W(walls[y][x]) == 0)
        floodfill(y, x-1, which_room, room_area);
    if (IS_N(walls[y][x]) == 0)
        floodfill(y-1, x, which_room, room_area);
    if (IS_E(walls[y][x]) == 0)
        floodfill(y, x+1, which_room, room_area);
    if (IS_S(walls[y][x]) == 0)
        floodfill(y+1, x, which_room, room_area);

    // ����ǽ�����˳��ݹ�
    return ;
}

void test_remove(int y, int x, char dest)
{
    //int which_room = room_color[y][x];
    switch (dest) {
    case 'N':
        // ����������ϲ��Ƚ������С
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

    int max_area(0);    // ��֮ǰ���ķ�������
    int which_room(0);  // �����������µı�����һ��ͻ��1����1��ʼ
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            // û���ѹ��ķ�����0
            // �ѹ���������Ӧ�ķ���ı��
            if (room_color[i][j] == 0) {
                int area(0);    // ͳ�����
                // ���������ѵ�һ�䷿
                floodfill(i, j, ++which_room, &area);
                // ��¼�µ�ǰ��������
                num_rooms[which_room] = area;
                // ��¼������
                max_area = max(area, max_area);
            }

    // ������ĿҪ��Ҫ���������Ͽ�ʼ��
    // ������ѡ�����ģ����������������ѡ���ϵ�
    // �������µ�ѭ���Ǵ� 0..M      N-1..0 չ����
    for (int i = 0; i < M; ++i)
        for (int j = N-1; j >= 0; --j) {
            // ��ɫ��һ����˵���ǲ�ͬ�ķ���
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