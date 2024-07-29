#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MOD 1000000007
 
long long int prime[1000010];//prime[0]=2,prime[1]=3,prime[2]=5,prime[3]=7,........
bool is_prime[1000010];//自己写的素数打表需要的一个数组,实际上最后跟prime数组和no_prime数组作用重叠了
int factor[1000010];//记录分解质因数之后的结果
int no_prime[1000010];//记录质数的下标,比如no_prime[5]=2,就是说5这个质数的下标是2,对应实际就是是第2+1=3个质数
 
int maxx(int a,int b)
{
    if(a>b)
        return a;
    else
        return b;
}
 
long long int quick_mod(long long int a,long long int p)//计算(a^p)%mod即快速幂 用于计算指数p特别大的情况
{
    //计算(a^p)%mod
    long long int res=1;
    while(p)
    {
        if(p&1)
            res=res*a%MOD;//int有可能会冒，视情况换成long long
        p>>=1;//就是 p=p/2
        a=(a*a)%MOD;
    }
    return res;
}
 
/*int work_prime()
{
    int i,j;
    for(i=0; i<1000010; i++)
    {
        is_prime[i]=true;
    }
    memset(prime,0,sizeof(prime));
    is_prime[0]=is_prime[1]=false;
    for(i=2; i<1000010; i++)
    {
        while(is_prime[i]!=true)
            i++;
        for(j=2; i*j<1000010; j++)
        {
            is_prime[i*j]=false;
        }
    }
    j=0;
    for(i=2; i<1000010; i++)
    {
        if(is_prime[i]==true)
        {
            prime[j]=i;
            no_prime[i]=j;
            j++;
        }
    }
    return j;
}*///自己写的可能超时的版本,先筛再记录会浪费时间
 
int work_prime()
{//来自网上某博文,忘记网址了你打我啊
//感觉很精妙,实话
//不用先筛再遍历记录,时间快了不少
    int res;
    res=0;
    memset(prime,0,sizeof(prime));
    for (int i = 2; i <= 1000010; i++)
    {
        if (!prime[i])
        {
            prime[(++res)-1] = i;
            no_prime[i]=res-1;
        }
        for (int j = 1; j <= res && prime[j-1] <= 1000010 / i; j++)
        {
            prime[prime[j-1] * i] = 1;
            if (i % prime[j-1] == 0)
            {
                break;
            }
        }
    }
    return res;
}
 
 
int work_factor(int fac[1000010],int n,int n_prime)
{
    int i,max_no;
    for(i=0; i<n_prime&&prime[i]*prime[i]<=n; i++)//中间的平方是减少时间的附加条件
    {
        while(n%prime[i]==0)
        {
            n=n/prime[i];
            fac[i]++;
            max_no=i;
        }
    }
    if(n!=1)//这一段判断条件是用来防止n最后自己就是一个质数的,比如当n为2的时候跳出的时候,实际上fac数组并没有记录完实际的分解质因数的情况
    {
        fac[no_prime[n]]++;
    }
    max_no=maxx(max_no,no_prime[n]);//更新max_no
    return max_no;
}
 
int main()
{
    int i,n_prime,max_no,n;
    long long int res,ni;
    n_prime=work_prime();//打表
    ni=quick_mod(2,MOD-2);//实际上这个还不如提前算好了放进去.......
    while(scanf("%d",&n)!=EOF)
    {
        memset(factor,0,sizeof(factor));
        res=1;
        for(i=2; i<=n; i++)
        {
            max_no=maxx(max_no,work_factor(factor,i,n_prime));//更新max_no
        }
        for(i=0; i<n; i++)
        {
            res=(res*(factor[i]*2+1))%MOD;
        }
        res=((res+1)*ni)%MOD;
        printf("%lld\n",res);
    }
    return 0;
}