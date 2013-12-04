/*
ID: lyyyuna
PROG: milk6
LANG: C++
*/
/*
首先将题目的语言转化成图论术语就是：
(1)找到一条割，使它是最小割。
(2)在（1）的条件下，满足这条最小割的边数最少
(3)在(1)和（2）的条件下，满足这条最小割的集合的字典序最小。

由于仍然要满足最小割，而关于最小割的算法，只能（至少我只能）靠网络流
来实现。且对于要满足最小边数的最小割并没有直接的算法可以做到，所以我
们必须要进行对算法的重新挖掘。
仔细分析，发现其实这是一个双关键字的问题。第一关键字是最小割，第二
关键字是边数最少。在满足第一关键字最大的情况下，再满足第二关键字最
大。也就是说第二关键字的存在不能影响第一关键字最大。
所以进行重新设定每条边的容量。

将C---àC*(M+1)+1
这样子，1表示每条边自己是否被统计。
我们再来看一下此时的最小割，因为在一个割中1最多只有M个，所以，1的个
数不会影响到前面C的选择，而在C最小的情况下，同时1也会变成最小。
也就是说Cmin’=cmin*(m+1)+minedges
因此，cmin=cmin’ div (m+1)
Minedges=cmin’ mod (m+1)
这两个分别是第一问第二问的答案。／／其实ｐａｒｔ２将ｐａｒｔ１的工作也做了
*/

#include <fstream>
#include <cstring>

using namespace::std;

const int MAXM = 1000+1;
const int MAXN = 32+1;
struct Node
{
    int from;
    int to;
    long long cost;
}e[MAXM];
int N, M;

long long map1[MAXN][MAXN];
long long map2[MAXN][MAXN];
long long const MAXFLOW = 0x7ffffffff;

int GAP[MAXN+9];
int h[MAXN];


/*
SAP算法框架：
1、定义距离标号为各点到汇点距离的下界(即最短距离)。
2、在初始距离标号的基础上，不断沿着可行弧找增广路。可行弧的定义为{( i , j ) , h[ i ]==h[ j ]+1 };
3、遍历当前节点完以后，为了保证下次再来的时候有路可走，重新标号当前距离。
    h[ i ] = min（h[ j ] +1）；
4、检查重新标记的顶点，若其为原点，且被标记的高度等于节点个数时，图中已经不存在增广路，算法可结束。否则继续从原点开始遍历

2、GAP常数优化！（性价比极高）
由于我们不停的遍历，最大流很可能便早就已经求出来了。那么我们接下来
的遍历便成了无用功。可以发现，距离标号是连续单调变化的。如果某一种
大小标号的节点数量为零。也就是出现了不连续，断层！那么图中也不肯能
再存在增广路了。实践中，我们用一个GAP[ i ]数组用来记录标号为i的顶点
的个数，若重标号使得vh数组中的原标号数目变为了0，那么就停止算法。
*/
//////////////////////////////////////////////////
// 返回流去的流量
//////////////////////////////////////////////////
long long dfs(int x, long long flow) // flow是总流量
{
    if (x == N)
        return flow;

    long long res = flow; // res是剩余流量
    for (int i = 1; i <= N; ++i) {
        // 满足可行弧条件
        if (map2[x][i] && h[x] == h[i]+1) {
            // 计算最小可行弧流量
            // 并递归寻找增广路
            long long t = dfs(i, min(res, map2[x][i]));
            map2[x][i] -= t;
            map2[i][x] += t;
            // 剩余流量 减去 最小可行弧流量
            // 若为0，说明没流量了，直接返回吧
            if (!(res-=t))
                return flow;
        }
    }

    // 需要重新标记
    // 重标记以后，原标记的数目肯定减少了1
    // 若出现了断层，已经找到了最大流，停止算法，让h[1]=N
    if (!--GAP[h[x]])
        h[1] = N;
    ++GAP[++h[x]];

    return flow-res; // 总流量减去剩下的流量=流去的流量
}

long long SAP()
{
    long long ans = 0;
    memcpy(map2, map1, sizeof(map2));
    memset(GAP, 0, sizeof(GAP));
    memset(h, 0, sizeof(h));

    GAP[0] = N;
    while (h[1]<N)
        ans += dfs(1, MAXFLOW);

    return ans;
}

int main(void)
{
    ifstream ifile("milk6.in");
    ofstream ofile("milk6.out");

    ifile >> N >> M;
    for (int i = 1; i <= M; ++i) {
        ifile >> e[i].from >> e[i].to >> e[i].cost;
        map1[ e[i].from ][ e[i].to ] += e[i].cost*MAXM + 1;
    }
    long long ans = SAP();

/*
因为总共只有1000条边，那么将每个边
容量*1001+1作为新的容量（注意这里指每次读入的每个边），那么最
大流mod 1001就是最小割去的边数。最大流=值 div 1001。
*/
    ofile << ans/MAXM << " " << ans%MAXM << endl;


/*
先说一个定理。
最小割边退流定理：
退流：如果删去一条边后，新旧图之间的最大流差值正好是该边容量，则称发生了退流、
定理内容：如果这条边在一条最小割中，则删掉该边后必然发生退流。且所有发生退流的边都在最小割上。
有了这个定理，我们就可以确定一条边是否在一条最小割上了，删去这条边，然后判断，是否发生退流即可。
*/
    long long map3_BAK[MAXN][MAXN];
    memcpy(map3_BAK, map2, sizeof(map2));
    for (int i = 1; i <= M; ++i) {
        if (!map3_BAK[ e[i].from ][ e[i].to ]) {
            // 尝试退流
            map1[ e[i].from ][ e[i].to ] -= e[i].cost;
            long long t;
            // 退流之后仍旧相等
            if ((t=SAP()) + e[i].cost == ans) {
                ans -= e[i].cost;
                memcpy(map3_BAK, map2, sizeof(map2));
                ofile << i << endl;
            }
            else
                // 不行，恢复流
                map1[ e[i].from ][ e[i].to ] += e[i].cost;
        }
    }

    return 0;
}

// http://www.cnblogs.com/ka200812/archive/2011/07/30/2121878.html
// http://hi.baidu.com/fmlzlkalohbcgod/item/f775ae07057d5cc0ff240d81
// http://www.cnblogs.com/longdouhzt/archive/2012/05/20/2510753.html
// http://www.nocow.cn/index.php/SAP