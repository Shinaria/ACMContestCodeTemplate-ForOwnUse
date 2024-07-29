#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const double PI=acos(-1);
struct complex
{
    double a,b;
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
            j+=k;
    }
}
void fft(complex *y,int len,int on)
{
    change(y, len);
    for(int h=2; h<=len; h<<=1)
    {
        complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(int j=0; j<len; j+=h)
        {
            complex w(1, 0);
            for(int k=j;k<j+h/2;k++)
            {
                complex u=y[k],t=w*y[k+h/2];
                y[k]=u+t;
                y[k+h/2]=u-t;
                w=w*wn;
            }
        }
    }
    if(on == -1)
        for(int i=0; i<len; i++)
            y[i].a /= len;
}
 
const int k=50000;
const int maxx=800040;
int data[maxx];
long long int times[maxx],res[maxx];
complex a[maxx],b[maxx];
int len_a,len_b;
 
int main()
{
    int n,i;
    long long int ans;
    while(scanf("%d",&n)!=EOF)
    {
        memset(data,0,sizeof(data));
        memset(res,0,sizeof(res));
        memset(times,0,sizeof(times));
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        for(i=0;i<n;i++)
        {
            scanf("%d",&data[i]);
            times[data[i]+k]++;
        }
        sort(data,data+n);
        len_a=data[n-1]+k+1;
        len_b=1;
        while(len_b<(len_a*2))
            len_b=len_b<<1;
        for(i=0;i<len_b;i++)
            a[i].a=times[i];
        fft(a,len_b,1);
        for(i=0;i<len_b;i++)
            b[i]=a[i]*a[i];
        fft(b,len_b,-1);
        for(i=0;i<len_b;i++)
            res[i]=(long long int)(b[i].a+0.5);
        for(i=0;i<n;i++)
            res[2*data[i]+2*k]--;
        ans=0;
        for(i=0;i<n;i++)
            ans+=res[data[i]+2*k];
        ans-=2*times[k]*(n-times[k])+times[k]*(times[k]-1)*2;
        printf("%lld\n",ans);
    }
    return 0;
}