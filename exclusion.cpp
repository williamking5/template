//hdu 5072
#include<iostream>
#include<stdio.h>
#include<math.h>
#include<string.h>
#define MAXN 100000
using namespace std;
int b[MAXN+10],a[MAXN+10],sign[64],num[MAXN+10],fac[10];
long long coprime[MAXN+10],nonprime[MAXN+10];
//统计一个数的二进制位有多少个1，用于判断排除情况应该加还是减
int BitCount(int n){
    int c =0 ;
    for (c =0; n; ++c){
        n &= (n -1) ; // 清除最低位的1
    }
    return c ;
}
long long getNum(int x){
//将一个数分解质因数
    int top=0;
    for (int i=2;i*i<=x;i++){
        if (x%i==0){
            fac[top++]=i;
            while (x%i==0) x/=i;
        }
    }
    if (x-1) fac[top++]=x;
//容斥原理，依次枚举质因数的任意乘积，从而进行容斥加或减
    top=1<<top;
    long long ans=0;
    for (int i=1;i<top;i++){
        int tmp=1;
        int ii=i,nn=0;
        while (ii){
            if (ii&1) tmp*=fac[nn];
            nn++;
            ii>>=1;
        }

        ans+=sign[i]*(num[tmp]-1);
    }

    return ans;
}
int main(){
//用于判断容斥加还是减
    for (int i=1;i<64;i++)
        sign[i]=BitCount(i)%2?1:-1;

int t;
scanf("%d",&t);
while (t--){
    int n;
    scanf("%d",&n);
    memset(num,0,sizeof num);
    for (int i=1;i<=n;i++){
        scanf("%d",a+i);
        b[a[i]]++;
    }

    num[1]=n;
    for (int i=2;i<=n;i++)
        for (int j=1;j*i<=MAXN;j++)
            num[i]+=b[j*i];

    long long ans=0;
    for (int i=1;i<=n;i++){
        nonprime[i]=getNum(a[i]);
        coprime[i]=n-1-nonprime[i];
        ans+=nonprime[i]*coprime[i];
    }
    ans>>=1;

    ans=n*(n-1)*(n-2)/6-ans;
    printf("%lld\n",ans);
}
    return 0;
}
