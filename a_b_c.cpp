//计算a^b^c%p，其中p必须是素数
#include<bits/stdc++.h>
using namespace std;
long long POWER(long long a,long long n,long long p){
    long long ans=1;
    while (n){
        if (n&1) ans=ans*a%p;
        a=a*a%p;
        n>>=1;
    }
    return ans;
}
long long FUN(long long a,long long b,long long c,long long p){
    long long n=POWER(b,c,p-1);
    long long ans=POWER(a,n,p);
    return ans;
}
int main(){
    cout<<FUN(2,2,3,10007);
    return 0;
}
