#include<iostream>
using namespace std;
typedef pair<long long ,long long> PC;
//扩展欧几里得算法，但算出来的结果既可能相加为(a,b)也可能为-(a,b)
PC extend_euclid(long long a,long long b){
    if (a%b==0) return PC(1,0);
    else {
        PC ret=extend_euclid(b,a%b);
        return PC(ret.second-ret.first*(a/b),ret.first);
    }
}
//求最大公约数
long long gcd(long long a,long long b){
    return (a%b==0?b:gcd(b,a%b));
}
//求数论倒数（乘法逆元）
long long reci(long long a,long long p){
    if (gcd(a,p)-1) {
        cout<<"NOT FOUND"<<endl;
        return p+1;
    }
    PC ret=extend_euclid(a,p);
    if (ret.first*p+ret.second*a==-1) {
        ret.first=-ret.first;
        ret.second=-ret.second;
    }
    return (ret.second%p+p)%p;
}
//n<=10^18,m<=10^18,p<=10^5
long long getC(long long n,long long m,long long p){
    if (m>n) return 0;
    if (!n) return 1;
    long long a=1,b=1;
    for (int i=1;i<=n-m;i++)
        b=b*i%p;
    for (int i=n;i>=m+1;i--)
        a=a*i%p;

    long long ret=reci(b,p)%p;
    ret=ret*a%p;
    return ret;
}
//lucas定理具体实现,n<=10^18,m<=10^18,p<=10^5
long long pick(long long n,long long m,long long p){
    if (!m) return 0;
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
    cout<<pick(5,2,10007)<<endl;
    return 0;
}
