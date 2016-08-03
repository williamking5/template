#include<iostream>
#include<string.h>
#include<math.h>
#include<stdio.h>
#define P 1000000007
#define N 10000010
using namespace std;
long long pi[40],top;
long long prime[N],fai[N],sum[N];
bool check[N];
long long divide(long long n){
    top=0;
    int MAX=sqrt(n)+1;
    for (int i=2;i<=MAX;i++){
        if (n%i==0){
            pi[top++]=i;
            n/=i;
            MAX=sqrt(n)+1;
        }
    }
    if (n>1) pi[top++]=n;
}
long long Sum(long long m,long long n){
    if (m==0) return 0;
    if (n==1) return sum[m];
    else{
        int i;
        for (i=0;i<top;i++)
            if (n%pi[i]==0) break;

        return (((pi[i]-1)*(Sum(m,n/pi[i])%P))%P+Sum(m/pi[i],n)%P)%P;
    }
}
//快速幂，A为底数，B为指数，C为模
long long power(long long A,long long B,long long C){
    long long ans=1;
    while (B){
        ans=ans*(B&1?A:1)%C;
        B/=2;
        A=A*A%C;
    }
    return ans;
}
/*指数循环节，求k^k^k^k
根据欧拉公式，有A^B mod C=A^(B mod phi(C)+phi(C)) mod C
必须保证B>=phi(C)*/
long long getAns(long long A,long long C){
    if (C==1) return 0;
    long long B=getAns(A,fai[C])+fai[C];
    return power(A,B,C);
}
int main(){
    memset(check,0,sizeof check);

	fai[1]=1;
	int tot=0;
	for (int i=2;i<=N;i++){
		if (!check[i]){
			prime[tot++]=i;
			fai[i]=i-1;
		}
		for (int j=0;j<tot;j++){
			if (i*prime[j]>N) break;
			check[i*prime[j]]=true;
			if (i%prime[j]==0){
				fai[i*prime[j]]=fai[i]*prime[j];
				break;
			}
			else {
				fai[i*prime[j]]=fai[i]*(prime[j]-1);
			}
		}
	}

	for (int i=1;i<=N;i++)
        sum[i]=(sum[i-1]+fai[i])%P;

    long long n,m,p;
    while (scanf("%lld%lld%lld",&n,&m,&p)==3){
        divide(n);
        long long k=Sum(m,n);
        long long ans=getAns(k,p);
        printf("%lld\n",ans);
    }
    return 0;
}
