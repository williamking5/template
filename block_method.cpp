#include<iostream>
#include<string.h>
#include<stdio.h>
#include<algorithm>
#include<math.h>
#define N 60000
using namespace std;
bool check[N+5];
long long prime[N+5],mprime[N+5],pprime[N+5],tao[N+5],miu[N+5],a[1000],b[1000];
long long smiu[N+5],stao[N+5];
int divide(int n,int m){
    memset(a,0,sizeof a);
    int top=0,i;
    for (i=1;i*i<=n;i++)
        a[top++]=i;
    i--;
    for (;i>=1;i--){
        a[top++]=n/(i+1)+1;
    }
    a[top++]=n+1;
 
    for (i=1;i*i<=m;i++)
        a[top++]=i;
    i--;
    for (;i>=1;i--)
        a[top++]=m/(i+1)+1;
    a[top++]=m+1;
 
    if (n==2||m==2){
        a[top++]=2;
    }
    if (n==3||m==3){
        a[top++]=2;
        a[top++]=3;
    }
    sort(a,a+top);
    top=unique(a,a+top)-a;
    return top;
}
int main(){
    int tot=0;
    for (int i=2;i<=N;i++)
        pprime[i]=1,miu[i]=-1;
 
    for (int i=2;i<=N;i++){
        if (!check[i]) {
            prime[tot++]=i;
            mprime[i]=i;
            tao[i]=2;
        }
        for (int j=0;j<tot;j++){
            if (i*prime[j]>N) break;
            check[i*prime[j]]=-1;
            mprime[i*prime[j]]=prime[j];
            pprime[i*prime[j]]+=(prime[j]==mprime[i])*pprime[i];
            tao[i*prime[j]]=tao[i]*(pprime[i*prime[j]]+1)/pprime[i*prime[j]];
            miu[i*prime[j]]*=(i%prime[j]==0?0:miu[i]);
            if (i%prime[j]==0) break;
        }
    }
 
    miu[1]=tao[1]=1;
    for (int i=1;i<=N;i++)
        smiu[i]=smiu[i-1]+miu[i],stao[i]=stao[i-1]+tao[i];
 
int T;
scanf("%d",&T);
while (T--){
    int n,m;
    scanf("%d%d",&n,&m);
    int rr=divide(n,m);
 
    long long ans=0;
    for (int i=0;i<rr&&n/a[i]>0&&m/a[i]>0;i++){
        ans+=(smiu[a[i+1]-1]-smiu[a[i]-1])*stao[n/a[i]]*stao[m/a[i]];
    }
 
    printf("%lld\n",ans);
}
    return 0;
}
