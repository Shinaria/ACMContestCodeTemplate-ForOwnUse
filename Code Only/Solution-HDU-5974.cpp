#include <stdio.h>
#include <stdlib.h>
 
int gcd1(int a,int b)
{
    int res;
    if(b==0)
        return 0;
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
    int a,b,gcd,T;
    long long int res;
    while(scanf("%d",&T)!=EOF)
    {
        while(T--)
        {
            res=0;
            scanf("%d%d",&a,&b);
            gcd=gcd1(a,b);
            res=a*a-2*b*gcd;
            printf("%lld\n",res);
        }
    }
    return 0;
}