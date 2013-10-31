/*
ID: lyyyuna
PROG: milk
LANG: C++
*/

#include <fstream>
#include <algorithm>

using namespace::std;

class Cows
{
public:
    int price;
    int amount;
};

bool operator< (const Cows &a, const Cows &b)
{
    return a.price < b.price;
}

const int MAX = 5000;

int main(void)
{
    ifstream ifile("milk.in");
    ofstream ofile("milk.out");
    int M, N;
    ifile >> M >> N;

    Cows cows[MAX];
    for (int i = 0; i != N; ++i)
        ifile >> cows[i].price >> cows[i].amount;

    sort(cows, cows+N);

    int i(0);
    int price(0);
    while (M - cows[i].amount > 0) {
        M -= cows[i].amount;
        price += cows[i].price * cows[i].amount;
        i++;
    }

    price += M * cows[i].price;

    ofile << price << endl;
}