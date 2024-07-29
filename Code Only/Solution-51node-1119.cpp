#include <stdio.h>
#include <stdlib.h>
#define MOD 1000000007
 
long long int data[2000010];//不是1000010,因为M+N<=2000000,底数的规模是看M+N
 
long long int quick_mod(long long int a,long long int p,long long int mod)//计算(a^p)%mod即快速幂 用于计算指数p特别大的情况
{//计算(a^p)%mod
    long long int res=1;
    while(p)
    {
        if(p&1)
            res=res*a%mod;//int有可能会冒，视情况换成long long(这里换了)
        p>>=1;//就是 p=p/2
        a=(a*a)%mod;
    }
    return res;
}
 
long long int cn(int n,int k)
{//cn,组合数英文combinatorial number的缩写
    long long int res;
    res=data[n];
    res=(res*quick_mod(data[k],MOD-2,MOD))%MOD;//利用费马小定理取巧求逆元 (b*b^(p-2))mod p=1,因为质数p的欧拉函数值就是p-1
    res=(res*quick_mod(data[n-k],MOD-2,MOD))%MOD;//啊对这两行代码是抄的,因为原来的长达五六行的自己写的啰嗦版本找不到了,又一次证明我的代码相当冗余
    return res;
}
 
int main()
{
    int a,b,minn,i;
    long long int res;
    data[0]=1;
    for(i=1;i<2000010;i++)
    {
        data[i]=data[i-1]*i;
        data[i]=data[i]%MOD;//打表,边打表边取模
        //printf("%lld\n",data[i]);
    }
    while(scanf("%d%d",&a,&b)!=EOF)
    {
        if(a<b)
            minn=a;
        else
            minn=b;
        res=cn(a+b-2,minn-1);//为什么这里要减二——认真读题，机器人走的是格子不是格点
        printf("%lld\n",res);
    }
    return 0;
}