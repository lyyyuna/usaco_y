/*
ID: lyyyuna
PROG: frac1
LANG: C++
*/

#include <fstream>
#include <map>
#include <string>

using namespace::std;

// 把一个数转成字符串
string n_2_s(int n)
{
    string num;
    while(n) {
        num.insert(num.begin(), n%10 + '0');
        n /= 10;
    }
    return num;
}

int main(void)
{
    ifstream ifile("frac1.in");
    ofstream ofile("frac1.out");

    int num;
    ifile >> num;

    // 用map,逻辑比较清楚
    map<float, string> fractions;
    // 这两个单独输出
    fractions[0/1] = "0/1";
    fractions[1/1] = "1/1";

    // 可以看到，并没有判断是否分母分子互质的情况
    // 因为，循环是从分母最大的情况开始的，当遍历到小的数的时候，就会把原来不互质的情况覆盖掉（这个思路比较巧妙）
    // 例如 5
    // 2/4 == 0.5 虽然不是互质
    // 当循环继续下去，就会出现 1/2 == 0.5，这样就把刚才的 2/4 覆盖掉了
    // 所以denominator 要从 num 开始循环
    for (float denominator = num; denominator>1.0; denominator -= 1) {
        for (float numerator = 1.0; numerator < denominator; numerator += 1) {
            float frac = numerator / denominator;
            string s;
            s += n_2_s(numerator);
            s.push_back('/');
            s += n_2_s(denominator);
            fractions[frac] = s;
        }
    }

    for (map<float, string>::const_iterator iter = fractions.begin();
        iter != fractions.end(); ++iter) 
        ofile << iter->second << endl;

    return 0;
}