#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <iostream>
using namespace std;
const double PI=acos(-1);//这个是一定要有的, 因为fft有应用到三角函数,因此头文件math.h也要包含进去
const int maxx=300000;
 
struct complex
{
    double a,b;//a表示实部,b表示虚部
    complex(double aa=0.0,double bb=0.0)
    {
        a=aa;
        b=bb;
    }
    complex operator +(const complex &e)
    {//重载运算符+用以直接进行虚数相加,下同
        return complex(a+e.a,b+e.b);
    }
    complex operator -(const complex &e)
    {//重载运算符-
        return complex(a-e.a,b-e.b);
    }
    complex operator *(const complex &e)
    {//重载运算符*
        return complex(a*e.a-b*e.b,a*e.b+b*e.a);
    }
};
 
void change(complex *y,long long int len)
{//change这个词还挺常用于给自己写的功能函数重名的,要注意一下,不过有可能以后更新模板就换掉了
    long long int i,j,k;
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
void fft(complex *y,long long int len,int on)
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
    if(on==-1)//还原回原来的多项式
        for(i=0;i<len;i++)
            y[i].a/=len;
}
complex a[maxx],b[maxx],ans[maxx];
long long int A[100000],B[100000],ab[maxx];
int main()
{
    long long int T,i,n,len_a,len,num,res;
    scanf("%lld",&T);
    while(T--)
    {
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        memset(A,0,sizeof(A));
        memset(B,0,sizeof(B));
        memset(ab,0,sizeof(ab));
        memset(ans,0,sizeof(ans));
        scanf("%lld",&n);
        for(i=0;i<n;i++)
            scanf("%lld",&A[i]);
        for(i=0;i<n;i++)
            scanf("%lld",&B[n-1-i]);//注意这里是倒置哦!
        len=1;
        len_a=n;
        while(len<2*len_a)
            len=len<<1;
        for(i=0;i<n;i++)
        {
            a[i].a=A[i];
            b[i].a=B[i];
        }
        fft(a,len,1);
        fft(b,len,1);
        for(i=0;i<len;i++)
            ans[i]=a[i]*b[i];
        fft(ans,len,-1);
        for(i=0;i<len;i++)
            ab[i]=(long long int)(ans[i].a+0.5);
        res=0;
        num=0;
        for(i=0;i<n;i++)
        {
            if(res<(ab[i]+ab[i+n]))//为什么这么写参见上面的解释
            {
                res=ab[i]+ab[i+n];
                num=n-1-i;
            }
        }
        res=0;
        for(i=0;i<n;i++)
            res+=(A[i]-B[n-1-((i+num)%n)])*(A[i]-B[n-1-((i+num)%n)]);//因为是倒置输入的,取B[(i+num)%n]实际上在代码里面得写B[n-1-((i+num)%n)]
        printf("%lld\n",res);
    }
    return 0;
}