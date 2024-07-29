#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
 
long long int _gcd(long long int a,long long int b)
{
    long long int res;
    res=a%b;
    while(res)
    {
        a=b;
        b=res;
        res=a%b;
    }
    return b;
}
 
long long int phi(long long int n)
{
    long long int res=n,i;
    for(i=2;i*i<=n;i++)
    {
        if(n%i==0)
        {
            res=res-res/i;
            while(n%i==0)
                n=n/i;
        }
    }
    if(n>1)
    {
        res=res-res/n;
    }
    return res;
}
 
long long int step[10010],fac[10010];
 
int main()
{
    int T,j,n,case_num,n_fac;
    long long int m,temp,res,i;
    bool all;
    scanf("%d",&T);
    case_num=1;
    while(T--)
    {
        all=false;
        scanf("%d%lld",&n,&m);
        for(i=0;i<n;i++)
        {
            scanf("%lld",&temp);
            step[i]=_gcd(temp,m);//跳了足够多圈数之后的等效步长,并放在step里
            if(step[i]==1)
                all=true;
        }
        if(all==true)//找到了一只实际等效步长就是1的青蛙的特判
        {
            printf("Case #%d: %lld\n",case_num++,((m-1)*m)/2);
            continue;
        }
        sort(step,step+n);
        n=int(unique(step,step+n)-step);//不妨学习一下unique函数的用法
        n_fac=0;
        for(i=2;i*i<=m;i++)
        {//给m分解因数,确定要找哪些假步数的青蛙,例如30块石头就要找假2,3,5,6,10,15步青蛙,并把这些数放在fac里
            if(i*i==m)
            {
                fac[n_fac++]=i;
            }
            else if(m%i==0)
            {
                fac[n_fac++]=i;
                fac[n_fac++]=m/i;
            }
        }
        sort(fac,fac+n_fac);
        res=0;
        for(i=0;i<n_fac;i++)
        {//找"假fac[i]步"青蛙
            for(j=0;j<n;j++)
            {
                if(fac[i]%step[j]==0)//因为假fac[i]步青蛙可以由以fac[i]的因子为实际等效步数的青蛙代替
                //找到了一只"假fac[i]步"青蛙,所以计算完fac[i]步青蛙可标记的石头之后就可以跳出了,不然会重复计算
                {
                    res+=phi(m/fac[i])*m/2;
                    break;
                }
            }
        }
        printf("Case #%d: %lld\n",case_num++,res);
    }
    return 0;
}