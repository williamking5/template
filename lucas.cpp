#include<iostream>
#include<string.h>
#include<algorithm>
#define P 110119
using namespace std;
typedef pair<long long ,long long> PC;
long long fac[P],inv[P],facinv[P];
//预处理出小于质数P的所有数的逆元，阶乘以及阶乘的逆元
void init_lucas(){
	fac[0]=fac[1]=inv[0]=facinv[0]=inv[1]=facinv[1]=1;
	for(int i = 2; i < P; ++i) {
        fac[i] = fac[i - 1] * i % P;
        inv[i] = inv[P % i] * (P - P / i) % P;
//注意这个公式可以在o(n)的复杂度内求出所有数的逆元
        facinv[i] = facinv[i - 1] * inv[i] % P;
    }
}
//n<=10^18,m<=10^18,p<=10^5，求组合数
long long getC(long long n,long long m,long long p){
    if (m>n) return 0;
    if (!n) return 1;
	long long ret=fac[n]*facinv[m]%p*facinv[n-m]%p;
    return ret;
}
//lucas定理具体实现,n<=10^18,m<=10^18,p<=10^5
long long pick(long long n,long long m,long long p){
    if (!m) return 1;
    long long a[100],b[100],i=-1;
    while (n){
        a[++i]=n%p;
        n/=p;
        b[i]=m%p;
        m/=p;
    }
    long long k=i;
    long long ret=1;
    for (int i=0;i<=k;i++){
        ret*=getC(a[i],b[i],p);
        ret%=p;
    }
    return ret;
}
int main(){
	init_lucas();
	cout<<pick(5,3,P)<<endl;
	return 0;
}
