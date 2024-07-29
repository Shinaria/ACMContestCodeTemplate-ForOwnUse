#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
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
 
char A[200005],B[200005];
complex a[200005],b[200005],c[200005];
long long int res[200005];
int len_a,len_b,len_c,len;
//怕函数体里面塞不下所以.....
 
int main()
{
    int i;
    while(scanf("%s%s",A,B)!=EOF)
    {
        len=1;
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        memset(c,0,sizeof(c));//置零
        memset(res,0,sizeof(res));
        len_a=(int)strlen(A);
        len_b=(int)strlen(B);
        for(i=0;i<len_a;i++)
            a[len_a-1-i].a=A[i]-'0';//倒置,fft优化的多项式存储时,下标为k则代表多项式中对应的项次数为k,所以倒置
        for(i=0;i<len_b;i++)
            b[len_b-1-i].a=B[i]-'0';//倒置
        while(len<(len_a+len_b))
            len=len<<1;//len为大于结果多项式次数的2次幂,比如最后结果最高次项为10,那么取len为2^4=16
        fft(a,len,1);//注意后面on的参数,和多项式长度参数传的是什么
        fft(b,len,1);//on=1,表示从原始的多项式转化成便于处理的"fft"形式
        for(i=0;i<len;i++)//接下来开始线性处理
            c[i]=a[i]*b[i];//这里是虚数的乘法哦,在结构体声明里面重载过
        fft(c,len,-1);//on==-1,就是把"fft"形式转化成普遍的多项式形式
        for(i=0;i<len;i++)
            res[i]=(int)(c[i].a+0.5);//转化过来的普遍的多项式形式是小数,用四舍五入的方法约成整数
        for(i=0;i<=len;i++)
        {
            res[i+1]+=res[i]*0.1;
            res[i]=res[i]%10;//向高位进位
        }
        len_c=0;
        for(i=len-1;i>=0;i--)
        {
            if(res[i]!=0)
            {
                len_c=i;
                break;
            }
        }
        for(i=len_c;i>=0;i--)
        {
            putchar((int)res[i]+'0');
        }
        puts("");
    }
    return 0;
}