/*
ID: lyyyuna
PROG: lamps
LANG: C++
*/

/*
���ȣ�1 2 3 4 5 6 �������ƾ��ܴ������е�״̬������ĵ���ǰ����ظ�
��������ⷨ��û������
��������ͨ�����ѣ���� �ĸ����� ���е�״̬��Ȼ���ж�
*/

#include <fstream>
#include <algorithm>
#include <string>

using namespace::std;

int N, C;
bool on[101];
bool off[101];
bool lamps[101];
bool which_key[5];

string types[101];
int total_types;

char n_2_s(bool led)
{
    if (led == true)
        return '1';
    else 
        return '0';
}

void check()
{
    // ���Ƶ������ �� �� �Ƿ����
    for (int i = 1; i <= N; ++i) {
        if (on[i] && !lamps[i])
            return;
        if (off[i] && lamps[i])
            return;
    }
    // ͳ�Ʊ����µĸ���
    int number_key(0);
    for (int i = 1; i <= 4; ++i) {
        if (which_key[i] == true)
            number_key ++;
    }
    // �����ܵİ�����C�ж�
    if (C < number_key)
        return;
    if ((C-number_key)%2 != 0)
        return;
    
    // ������е����˵���Ƿ���������һ�����
    // Ȼ���¼�°������µ�״̬��ͨ���ַ�����¼
    for (int i = 1; i <= N; ++i) {
        types[total_types] = types[total_types] + n_2_s(lamps[i]);
    }
    total_types++;
}

void dfs(int key)
{
    // �ݹ����
    if (key>4) {
        check();
        return;
    }

    // ��ǰ�ݹ���ȵİ��� û�б����£����� key ������û��
    // û���£�ֱ�ӽ�����һ�㣬��ȥ�ж���һ�����������
    dfs(key+1);
    // ��ǰ�ݹ���ȵİ��� �����£����� key �������Ǳ����µ�
    // ���ĸ�������ȥִ���ĸ������Ķ���
    if (key == 1)
        for (int i = 1; i <= N; ++i)
            lamps[i] = !lamps[i];
    if (key == 2)
        for (int i = 1; i <= N; i += 2)
            lamps[i] = !lamps[i];
    if (key == 3)
        for (int i = 0; i <= N; i += 2)
            lamps[i] = !lamps[i];
    if (key == 4)
        for (int i = 0; i<=N/3; ++i)
            lamps[i*3+1] = !lamps[i*3+1];
    // ��¼���ĸ�����������
    which_key[key] = true;
    // ������һ��
    dfs(key+1);
    // ���ݣ��ָ�����
    which_key[key] = false;
    // ���ݣ��ָ�����������֮ǰ��״̬
    if (key == 1)
        for (int i = 1; i <= N; ++i)
            lamps[i] = !lamps[i];
    if (key == 2)
        for (int i = 1; i <= N; i += 2)
            lamps[i] = !lamps[i];
    if (key == 3)
        for (int i = 0; i <= N; i += 2)
            lamps[i] = !lamps[i];
    if (key == 4)
        for (int i = 0; i<=N/3; ++i)
            lamps[i*3+1] = !lamps[i*3+1];
}

bool cmp(string s1, string s2)
{
    return s1 < s2;
}

int main(void)
{
    ifstream ifile("lamps.in");
    ofstream ofile("lamps.out");

    ifile >> N >> C;
    // ���Ϊ0�Ĳ���
    // ��1��ʼ
    for (int i = 0; i <= N; ++i)
        lamps[i] = true;

    int num;
    ifile >> num;
    // �������ĵ�
    while (num>0) {
        on[num] = true;
        ifile >> num;
    }
    ifile >> num;
    // ������ĵ�
    while (num>0) {
        off[num] = true;
        ifile >> num;
    }
    // ����
    dfs(1);
    // ������cmp
    sort(types, types+total_types, cmp);

    for (int i = 0; i < total_types; ++i) {
        ofile << types[i] << endl;
    }
    if (total_types == 0)
        ofile << "IMPOSSIBLE" << endl;
}