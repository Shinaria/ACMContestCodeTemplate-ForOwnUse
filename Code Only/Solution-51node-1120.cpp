#include <stdio.h>
#include <stdlib.h>
#define MOD 10007
long long int quick_mod(long long int a,long long int p,long long int mod)
//计算(a^p)%mod即快速幂 用于计算指数p特别大的情况
{
    //计算(a^p)%mod
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
 
long long int cn(long long int m,long long int n,int p)
//从n个里面选m个
{
    long long int res,up,down;
    int i;
    if(m>n)
        return 0;
    else if(m==n)
        return 1;
    if(n-m<m) m=n-m;
    up=down=1;
    for(i=0;i<m;i++)
    {
        up=(up*(n-i))%p;
        down=(down*(m-i))%p;
    }
    //printf("%lld %lld\n",up,down);
    res=(up*quick_mod(down,p-2,p))%p;
    return res;
    
}
 
long long int LUCAS(long long int m,long long int n,int p)
{//适用于p不大的情况
    //这里的m和n的意思是从n个里面选m个
    long long int res,mm,nn;
    res=1;
    mm=m;
    nn=n;
    while(mm&&nn&&res)
    {//这个循环可以说是卢卡斯定理体现的地方
        res=(res*cn(mm%p,nn%p,p))%p; nn=nn/p; mm=mm/p;
    }
    return res;
    
}
int main()
{
    long long int res1,res2,res,n;
    while(scanf("%lld",&n)!=EOF)
    {
        n--;
        res1=LUCAS(n,2*n,MOD);
        res2=LUCAS(n-1,2*n,MOD);
        res=(2*(res1-res2)%10007+10007)%10007;//卡特兰数的组合数表示形式,具体的以后上离散数学课可能要学
        printf("%lld\n",res);
    }
    return 0;
}