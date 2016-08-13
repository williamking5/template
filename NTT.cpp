#include <iostream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
//规模N
const long long N = (1<<18)+1;
//采用的模数P必须为c*2^x+1的形式
const long long P = 119*(  1<< 23) + 1;
//模P的最小原根G
const long long G = 3;
const long long NUM = 20;
long long  wn[NUM];
long long  a[N], b[N],c[N],f[N];
long long A[N];
long long inv[N],fac[N],facinv[N],POW[N],powinv[N];
//快速幂
long long power(long long A,long long B,long long C){
    long long ans=1;
    while (B){
        ans=ans*(B&1?A:1)%C;
        B/=2;
        A=A*A%C;
    }
    return ans;
}
//获取一组n个数论根
void GetWn(){
    for(int i = 0; i < NUM; i++){
        int t = 1 << i;
        wn[i] = power(G, (P - 1) / t, P);
    }
}
//Rader's fft 算法，参见维基百科
void Rader(long long a[], int len)
{
    int j = len >> 1;
    for(int i = 1; i < len - 1; i++)
    {
        if(i < j) swap(a[i], a[j]);
        int k = len >> 1;
        while(j >= k)
        {
            j -= k;
            k >>= 1;
        }
        if(j < k) j += k;
    }
}
//快速数论转换
void NTT(long long a[], int len, int on)
{
    Rader(a, len);
    int id = 0;
    for(int h = 2; h <= len; h <<= 1)
    {
        id++;
        for(int j = 0; j < len; j += h)
        {
            long long w = 1;
            for(int k = j; k < j + h / 2; k++)
            {
                long long u = a[k] % P;
                long long t = w * a[k + h / 2] % P;
                a[k] = (u + t) % P;
                a[k + h / 2] = (u - t + P) % P;
                w = w * wn[id] % P;
            }
        }
    }
    if(on == -1)
    {
        for(int i = 1; i < len / 2; i++)
            swap(a[i], a[len - i]);
        long long inv = power(len, P - 2, P);
        for(int i = 0; i < len; i++)
            a[i] = a[i] * inv % P;
    }
}
//进行转换并点乘，再将答案转换回去
void Conv(long long a[], long long b[], long long c[],int n)
{
    NTT(a, n, 1);
    NTT(b, n, 1);
    for(int i = 0; i < n; i++)
        c[i] = a[i] * b[i] % P;
    NTT(c, n, -1);
}
bool cmp(long long x,long long y){
    return x>y;
}
int main(){
    fac[0]=fac[1]=inv[0]=facinv[0]=inv[1]=facinv[1]=POW[0]=1;
    POW[1]=2;powinv[0]=1;powinv[1]=(P-P/2)%P;

	for(int i = 2; i <= 100100; ++i) {
        fac[i] = fac[i - 1] * i % P;
        inv[i] = inv[P % i] * (P - P / i) % P;
        facinv[i] = facinv[i - 1] * inv[i] % P;
        POW[i]=POW[i-1]*2%P;
        powinv[i]=powinv[i-1]*inv[2]%P;
    }
    GetWn();
int t;
cin>>t;
while (t--){
    int n;
    scanf("%d",&n);
    memset(A,0,sizeof A);
    for (int i=1;i<=n;i++)
        scanf("%lld",A+i);

    sort(A+1,A+1+n,cmp);

    for (int i=0;i<=n;i++){
        a[i]=POW[n-i]*facinv[i]%P;
        b[i]=A[n-i]*fac[n-i-1]%P;
    }

    int len=1;
    while (len<=2*(n+1)) len<<=1;

    for (int i=n+1;i<=len;i++)
        a[i]=b[i]=0;

    memset(c,0,sizeof c);
    Conv(a,b,c,len);

    for (int i=1;i<=n;i++)
        f[i]=c[n-i];

    for (int i=1;i<=n;i++)
        f[i]=f[i]%P*facinv[i-1]%P*powinv[i]%P;

    long long ans=0;
    for (int i=1;i<=n;i++){
        ans=(ans+f[i])%P;
        printf("%lld\n",ans);
    }
    printf("\n");
}
    return 0;
}
