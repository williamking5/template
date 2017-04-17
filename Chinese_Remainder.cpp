#include <iostream>
#include <math.h>
#include <stdio.h>
using namespace std;
long long Extended_Euclid(long long a,long long b,long long &x,long long &y)    //扩展欧几里得算法
{
    long long d;
    if(b==0)
    {
        x=1;y=0;
        return a;
    }
    d=Extended_Euclid(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
//快速乘法，防止long long 乘long long
long long cheng(long long a,long long b,long long mod){
    long long ans=0;
    while (b){
        ans+=(b&1)*a;
        ans%=mod;
        b/=2;
        a=(a*2)%mod;
    }
    return ans;
}
long long Chinese_Remainder(long long a[],long long w[],long long len)    //中国剩余定理  a[]存放余数  w[]存放两两互质的数
{
    long long i,d,x,y,m,n,ret;
    ret=0;
    n=1;
    for (i=0;i<len;i++)
        n*=w[i];
    for (i=0;i<len;i++)
    {
        m=n/w[i];
        d=Extended_Euclid(w[i],m,x,y);
        ret=(ret+cheng(cheng(y,m,n),a[i],n))%n;
    }
    return (n+ret%n)%n;
}
long long w[25],b[25];
int main()
{
    int n;
    cin>>n;
    for (int i=0;i<n;i++)
        cin>>w[i]>>b[i];

    cout<<Chinese_Remainder(b,w,n)<<endl;
    return 0;
}
