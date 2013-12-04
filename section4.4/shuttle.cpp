/*
ID: lyyyuna
PROG: shuttle
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;
 
int main()
{
	ifstream fin("shuttle.in");
	int m;
	fin >> m;
	int flag = -1;	
	int n = m+1;
	int t = 0;	
	int i,j;
 
	ofstream fout("shuttle.out");
	for ( i=1; i<=m; i++)
	{
		n += flag;
	        (++t % 20 == 0 )? fout << n << endl : fout << n << ' ';
		flag *= -1;
		for ( int j=0; j<i ; j++)
		{
			n += flag*2;
			(++t % 20 == 0 )? fout << n << endl : fout << n << ' ';
		}
	}
	for ( i=m; i>1; i--)
	{
		flag *= -1;
		n += flag;
		(++t % 20 == 0 )? fout << n << endl : fout << n << ' ';
		for ( j=1; j<i; j++)
		{
			n += flag*2;
			(++t % 20 == 0 )? fout << n << endl : fout << n << ' ';
		}
	}
	fout << n-flag << endl;
 
	return 0;
}