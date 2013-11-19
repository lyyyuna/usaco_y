/*
ID: lyyyuna
PROG: msquare
LANG: C++
*/

#include <fstream>
#include <set>
#include <queue>
#include <string>
#include <algorithm>

using namespace::std;

class Node
{
public:
    Node(string _st, string _steps, int _count)
    {
        st = _st;
        steps = _steps;
        count = _count;
    }
public:
    string st;
    string steps;
    int count;
};

string fin = "";
set<string> ss;
queue<Node> Q;

Node BFS()
{
    // 如果输入就是12345678，直接返回
    if (fin == "12345678") return Node("", "", 0);
    
    Q.push(Node("12345678", "", 0));
    ss.insert("12345678"); // 用来判重
    while(!Q.empty()) {
        Node cur = Q.front();
        Q.pop();
        string cur_str = cur.st;

        string A(cur_str.rbegin(), cur_str.rend());
        if (A == fin)
            return Node(A, cur.steps+"A", cur.count+1);
        if (!ss.count(A)) {
            ss.insert(A);
            Q.push(Node(A, cur.steps+"A", cur.count+1));
        }

        string B(cur_str[3] + cur_str.substr(0,3) + cur_str.substr(5) + cur_str[4]);
        if (B == fin)
            return Node(B, cur.steps+"B", cur.count+1);
        if (!ss.count(B)) {
            ss.insert(B);
            Q.push(Node(B, cur.steps+"B", cur.count+1));
        }

        string C(cur_str);
        swap(C[1], C[2]);
        swap(C[1], C[5]);
        swap(C[1], C[6]);
        if (C == fin)
            return Node(C, cur.steps+"C", cur.count+1);
        if (!ss.count(C)) {
            ss.insert(C);
            Q.push(Node(C, cur.steps+"C", cur.count+1));
        }
    }
}

int main(void)
{
    ifstream ifile("msquare.in");
    ofstream ofile("msquare.out");
    char c;
    for (int i = 0; i < 8; ++i) {
        ifile >> c;
        fin += c;
    }

    Node result = BFS();
    ofile << result.count << endl
        << result.steps << endl;

    return 0;
}