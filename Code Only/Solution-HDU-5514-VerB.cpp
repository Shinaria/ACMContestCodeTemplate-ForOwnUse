#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
 
long long int step[10010];
long long int add_times[1000005];
long long int need_times[1000005];
long long int fac[1000005];
 
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
 
int main()
{
    long long int res,temp,m,fac_num,i,j,change;
    bool all;
    long long int T,case_num,n;
    scanf("%lld",&T);
    case_num=1;
    while(T--)
    {
        fac_num=0;
        res=0;
        all=false;
        memset(need_times,0,sizeof(need_times));
        memset(add_times,0,sizeof(add_times));
        scanf("%lld%lld",&n,&m);
        for(i=0;i<n;i++)//读入青蛙的步数
        {
            scanf("%lld",&temp);
            step[i]=_gcd(temp,m);
            if(step[i]==1)
                all=true;
        }
        if(all==true)
        {
            printf("Case #%lld: %lld\n",case_num++,(m-1)*m/2);
            continue;
        }
        sort(step,step+n);
        n=int(unique(step,step+n)-step);//经典的去重函数unique
        for(i=1;i*i<=m;i++)
        {
            if(i*i==m)
            {
                fac[fac_num++]=i;
            }
            else if(m%i==0)
            {
                fac[fac_num++]=i;
                fac[fac_num++]=m/i;
            }
        }
        sort(fac,fac+fac_num);
        res=0;
        for(i=0;i<fac_num-1;i++)
        {
            for(j=0;j<n;j++)
            {
                if(fac[i]%step[j]==0)
                {
                    need_times[i]=1;
                    break;
                }
            }
            if(add_times[i]!=need_times[i])
            {
                temp=m/fac[i];
                res+=temp*(temp-1)/2*fac[i]*(need_times[i]-add_times[i]);
                change=need_times[i]-add_times[i];
                for(j=i;j<fac_num-1;j++)
                {//举个例子:步长为2的青蛙会把4,6,8,10,....的给跳了,就是把它们的贡献都给算了一遍
                    if(fac[j]%fac[i]==0)
                    {
                        add_times[j]+=change;
                    }
                }
            }
        }
        printf("Case #%lld: %lld\n",case_num++,res);
    }
    return 0;
}