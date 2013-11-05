/*
ID: lyyyuna
PROG: milk3
LANG: C++
*/

#include <fstream>

using namespace::std;

const int N = 21;

bool bucket[N][N][N] = {false};
bool c_bucket[N];
int a, b, c;

void dfs(int a1, int b1, int c1)
{
    // ���ǵݹ�ĳ���
    // ��˼�ǣ���������Ѿ����ֹ���
    // ����ͰΪa1, b1, c1�������֮ǰ������Ѿ����֣���ʱ��û��Ҫ
    // �ټ����ݹ���ȥ�ˣ����ظ���
    if (bucket[a1][b1][c1])
        return ;
    bucket[a1][b1][c1] = true;

    // ��aͰΪ�գ�����λ
    // ����һ����Ҫ���ǵģ������ڴ�����²���Ҫ�˳��ݹ顣
    // ��Ϊ��Ȼa1Ϊ�գ�b��cͰ�����Ի������Ͳ�ֹһ�����������
    // ����return����������Ľ�������
    if (!a1) {
        c_bucket[c1] = true;
        // return;
    }

    // ����Ϊ���ֵ�������������һ��
    // ��cͰ����aͰ
    // �������ȫ�����룬�򡣡�����
    // ���������ȫ�����룬��ʣһ�㣬�򡣡�����
    if (a >= a1+c1)
        dfs(a1+c1, b1, 0);
    else
        dfs(a, b1, c1-(a-a1));

    if (a >= a1+b1)
        dfs(a1+b1, 0, c1);
    else
        dfs(a, b1-(a-a1), c1);

    if(b >= b1+c1)
        dfs(a1, b1+c1 , 0);
    else
        dfs(a1, b, c1-(b-b1));

    if(b >= a1+b1)
        dfs(0, a1+b1, c1);
    else
        dfs(a1-(b-b1), b, c1);
 
    if(c >= b1+c1)
        dfs(a1, 0, b1+c1);
    else
        dfs(a1, b-(c-c1), c);

    if(c >= a1+c1)
        dfs(0, b1, a1+c1);
    else
        dfs(a1-(c-c1), b1, c);

    return;
}

int main(void)
{
    ifstream ifile("milk3.in");
    ofstream ofile("milk3.out");
    
    ifile >> a >> b >> c;

    // ��ʼ���ѣ�һ��ʼa��b�ǿյģ�c������
    dfs(0, 0, c);

    bool space_flag = false;
    for (int i = 0; i != N; ++i) {
        if (c_bucket[i] && space_flag)
            ofile << " ";
        if (c_bucket[i]) {
            ofile << i;
            space_flag = true;
        }
    }
    ofile << endl;

    return 0;
}