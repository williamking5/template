#include<bits/stdc++.h>
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
    return ret.second;
}
int main(){
    cout<<reci(2,7);
    return 0;
}
