/*
ID: lyyyuna
PROG: cowxor
LANG: C++
*/

/*
首先，a[i]记录从1到i的异或值，则从 i 到 j 的异或值
位a[j] xor a[i-1];枚举的话是O(n^2)的算法，100000的数据绝对不行。 

问题的关键在对于每个a[j]，要于找到i使i到j的异或值最大。 

异或最大，感性上认识就是，有差别的位数靠近高位，且越多越好。再
看看这个字典树， 如果把26个字母改成0和1的孩子，这样可以形成一
个21层的二叉树。从最高位找起，如果有和当前所在的位数相异的位数，
就选那条路。 不行，再妥协选相同的位数。
*/

// http://blog.csdn.net/biran007/article/details/3911430
// http://www.cnblogs.com/txhwind/archive/2012/08/18/2645374.html
//

#include<cstdio>
#include<cstring>
FILE *fi=fopen("cowxor.in","r"),*fo=fopen("cowxor.out","w");
const int MAXn=100000+9,MAXt=9*MAXn;
int a[MAXn];
int next[MAXt][2],pos[MAXt],num=1;
int main()
{
        int n,i,j,k,ans=0,ansx=1,ansy=1;
        fscanf(fi,"%d",&n);
        for(i=1;i<=n;++i)
        {
                fscanf(fi,"%d",a+i);
                a[i]^=a[i-1];

                //插入前一项
                for(k=1,j=20;j>=0;--j)
                {
                        if(!next[k][(a[i-1]>>j)&1])
                                next[k][(a[i-1]>>j)&1]=++num;
                        pos[ k=next[k][(a[i-1]>>j)&1] ]=i;
                }

                //查询当前项

                for(k=1,j=20;j>=0;--j)

                        if(next[k][!( (a[i]>>j)&1 )])
                                k=next[k][!( (a[i]>>j)&1 )];
                        else
                                k=next[k][(a[i]>>j)&1];
                if(pos[k] && (a[i]^a[pos[k]-1])>ans)
                        ans=a[i]^a[pos[k]-1],ansx=pos[k],ansy=i;
        }
        fprintf(fo,"%d %d %d\n",ans,ansx,ansy);
        fclose(fi);
        fclose(fo);
        return 0;
}