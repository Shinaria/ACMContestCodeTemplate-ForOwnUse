#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
 
struct polynomial
{
    long long int a[100];
    int n;
};
typedef polynomial pol;
 
pol data[26];
 
void initial_data(int no,int n)//第no个字母,有n个
{
    int i,value;
    value=no+1;
    for(i=0;i<=n&&i*value<=50;i++)
    {
        data[no].a[i*value]=1;
        data[no].n=i*value;
    }
}
 
pol pol_multi(pol a, pol b)
{
	int i, j;
	pol res;
	memset(res.a, 0, sizeof(res.a));
	res.n = 0;
	for (i = 0; i <= a.n; i++)
	{
		for (j = 0; j <= b.n&&j + i <= 50; j++)
		{
			if(a.a[i] * b.a[j]!=0)
                            res.n = max(res.n, i + j);
			res.a[i + j] += a.a[i] * b.a[j];
		}
	}
	return res;
}
 
int main()
{
    int T,i,n,j,ans;
    pol res;
    scanf("%d",&T);
    while(T--)
    {
        ans=0;
        memset(data,0,sizeof(data));
        res.a[0]=1;//最开始的res永远都只有一个取0元硬币的方案,这是为什么自己去想
        res.n=0;
        for(i=1;i<=50;i++)
        {
            res.a[i]=0;
        }
        for(i=0;i<26;i++)
        {
            scanf("%d",&n);
            initial_data(i,n);
        }
        for(i=0;i<26;i++)
        {
            res=pol_multi(res,data[i]);
        }
        for(i=0;i<=res.n;i++)
        {//res.n是小于等于50中价值最高的方案的价值大小(好别扭
            //printf("%d ",res.a[i]);
            ans+=res.a[i];
        }
        printf("%d\n",ans-1);
    }
    return 0;
}