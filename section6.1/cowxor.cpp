/*
ID: lyyyuna
PROG: cowxor
LANG: C++
*/

/*
���ȣ�a[i]��¼��1��i�����ֵ����� i �� j �����ֵ
λa[j] xor a[i-1];ö�ٵĻ���O(n^2)���㷨��100000�����ݾ��Բ��С� 

����Ĺؼ��ڶ���ÿ��a[j]��Ҫ���ҵ�iʹi��j�����ֵ��� 

�����󣬸�������ʶ���ǣ��в���λ��������λ����Խ��Խ�á���
��������ֵ����� �����26����ĸ�ĳ�0��1�ĺ��ӣ����������γ�һ
��21��Ķ������������λ��������к͵�ǰ���ڵ�λ�������λ����
��ѡ����·�� ���У�����Эѡ��ͬ��λ����
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

                //����ǰһ��
                for(k=1,j=20;j>=0;--j)
                {
                        if(!next[k][(a[i-1]>>j)&1])
                                next[k][(a[i-1]>>j)&1]=++num;
                        pos[ k=next[k][(a[i-1]>>j)&1] ]=i;
                }

                //��ѯ��ǰ��

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