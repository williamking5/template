#include<iostream>
#include<algorithm>
#include<math.h>
#include<string.h>
#include<stdio.h>
using namespace std;
//规模N
const long long N = (1<<14)+1;
//采用的模数P必须为c*2^x+1的形式
const long long P = 1004535809;
//模P的最小原根G
const long long G = 3;
const long long NUM = 21;
long long  wn[NUM];
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
int top=0;
long long st[40];
//获取元根的两个函数
void init(long long m){
    top=0;
    memset(st,0,sizeof st);
    for (long long i=2;i<=sqrt(m)+1;i++){
        if (m%i==0){
            st[top++]=i;
            while (m%i==0) m/=i;
        }
    }
    if (m>1) st[top++]=m;
}
long long get_root(long long p){
    init(p-1);
    for (long long g=1;g<=p-1;g++){
        bool bb=true;
        for (int j=0;j<top;j++){
            long long mod=power(g,(p-1)/st[j],p);
            if (mod==1) {
                bb=false;
                break;
            }
        }
        if (bb){
            return g;
        }
    }
}
long long pp[8010],r[32][8010*4];
long long ans[8010*4],tmp[8010*4];
int pn[8010][32];
//为了方便数论变换，把运算集成到数组当中
int solve(int m,long long aa[],long long bb[],long long c[]){
    int len=1;
    while (len<=2*(m+1)) len<<=1;
    long long a[len+10],b[len+10];
    for (int i=0;i<m-1;i++){
        a[i]=aa[i];
        b[i]=bb[i];
    }
    for (int i=m-1;i<=len;i++)
        a[i]=b[i]=0;
    Conv(a,b,c,len);

    for (int i=0;i<m-1;i++){
        c[i]=(c[i]+c[i+m-1])%P;
        c[i+m-1]=0;
    }
    return len;
}
int main(){
    long long n,m,x,s,X;

    scanf("%lld%lld%lld%lld",&n,&m,&x,&s);
    long long gg=get_root(m);
    for (int i=1,j=0;j<m;i=i*gg%m,j++){
        pp[i]=j%(m-1);
    }

    X=pp[x]%(m-1);
    for (int i=0;i<s;i++){
        int xx;
        scanf("%d",&xx);
        if (!xx) continue;
        r[0][pp[xx]%(m-1)]=1;
    }

    GetWn();

    for(ans[0]=1;n;n>>=1,solve(m,r[0],r[0],r[0]))
        if(n&1){
          solve(m,ans,r[0],ans);
        }

    printf("%lld\n",ans[X]);
    return 0;
}
