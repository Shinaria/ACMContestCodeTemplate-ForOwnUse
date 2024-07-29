#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
const double PI=acos(-1);
 
struct complex
{
    double a,b;//a表示实部,b表示虚部
    complex(double aa=0.0,double bb=0.0)
    {
        a=aa;
        b=bb;
    }
    complex operator +(const complex &e)
    {
        return complex(a+e.a,b+e.b);
    }
    complex operator -(const complex &e)
    {
        return complex(a-e.a,b-e.b);
    }
    complex operator *(const complex &e)
    {
        return complex(a*e.a-b*e.b,a*e.b+b*e.a);
    }
};
 
void change(complex *y,int len)
{
    int i,j,k;
    for(i=1,j=len/2;i<len-1; i++)
    {
        if(i<j)
            swap(y[i],y[j]);
        k=len/2;
        while(j>=k)
        {
            j-=k;
            k>>=1;
        }
        if(j<k)
        {
            j+=k;
        }
    }
}
void fft(complex *y,int len,int on)
{
    change(y, len);
    int i,j,k;
    for(i=2;i<=len;i<<=1)
    {
        complex wn(cos(-on*2*PI/i),sin(-on*2*PI/i));
        for(j=0;j<len;j+=i)
        {
            complex w(1,0);
            for(k=j;k<j+i/2;k++)
            {
                complex u=y[k],t=w*y[k+i/2];
                y[k]=u+t;
                y[k+i/2]=u-t;
                w=w*wn;
            }
        }
    }
    if(on==-1)
        for(i=0;i<len;i++)
            y[i].a/=len;
}
 
const int maxx=500000;
complex a[maxx],b[maxx];
long long int sum[maxx];
int data[maxx];
long long int times[maxx];
int len,len_a;
//怕函数体里面塞不下所以.....
 
int main()
{
    int T,n,i;
    double res;
    long long int yes,all;
    scanf("%d",&T);
    while(T--)
    {
        yes=all=res=0;
        len=1;
        len_a=0;
        memset(times,0,sizeof(times));
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
            scanf("%d",&data[i]);
            times[data[i]]++;
            len_a=max(len_a,data[i]);
        }
        len_a++;
        sort(data,data+n);
        while(len<(2*len_a))
            len=len<<1;
        for(i=0;i<len;i++)
            a[i].a=times[i];
        fft(a,len,1);
        for(i=0;i<len;i++)
            b[i]=a[i]*a[i];
        fft(b,len,-1);
        for(i=0;i<len;i++)
            times[i]=(long long int)(0.5+b[i].a);
        len=2*data[n-1];//更新len!
        for(i=0;i<n;i++)
            times[data[i]*2]--;
        for(i=0;i<=len;i++)//这里中间为什么是等于?
            times[i]=times[i]/2;
        sum[0]=times[0];
        for(i=1;i<=len;i++)//这里中间为什么也是等于?
            sum[i]=sum[i-1]+times[i];//求前缀和
        for(i=0;i<n;i++)
        {
            yes+=sum[len]-sum[data[i]];
            yes-=(long long)(n-1-i)*i;
            yes-=(n-1);
            yes-=(long long)(n-1-i)*(n-i-2)/2;//关键是这里的去重和去掉的不符合题目的部分!
        }
        all=(long long)n*(n-1)*(n-2)/6;
        res=(double)yes/all;
        printf("%.7lf\n",res);
    }
    return 0;
}