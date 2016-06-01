//矩阵快速幂
#include<bits/stdc++.h>
#define MAXN 2
#define p 100007
using namespace std;
void matrix_multi(long long a[][MAXN],long long b[][MAXN],long long c[][MAXN]){
    for (int i=0;i<MAXN;i++)
        for (int j=0;j<MAXN;j++)
            c[i][j]=0;

    for (int i=0;i<MAXN;i++){
        for (int j=0;j<MAXN;j++){
            for (int k=0;k<MAXN;k++)
                c[i][j]=(c[i][j]+a[i][k]*b[k][j])%p;
        }
    }
}
void copymatrix(long long a[][MAXN],long long b[][MAXN]){
    for (int i=0;i<MAXN;i++)
        for (int j=0;j<MAXN;j++)
            a[i][j]=b[i][j];
}
void FAST_MULTI(long long a[][MAXN],long long n,long long ansans[][MAXN]){
    long long ans[MAXN][MAXN],tmp[MAXN][MAXN];
    for (int i=0;i<MAXN;i++){
        for (int j=0;j<MAXN;j++)
            ans[i][j]=0;
    }
    for (int i=0;i<MAXN;i++)
        ans[i][i]=1;
    while (n){
        if (n&1) {
            matrix_multi(a,ans,tmp);
            copymatrix(ans,tmp);
        }
        matrix_multi(a,a,tmp);
        copymatrix(a,tmp);
        n>>=1;
    }

    copymatrix(ansans,ans);
}
int main(){
    long long a[MAXN][MAXN],ans[MAXN][MAXN];
    a[0][0]=a[0][1]=a[1][0]=1;
    a[1][1]=0;
    FAST_MULTI(a,40,ans);
            for (int i=0;i<MAXN;i++){
        for (int j=0;j<MAXN;j++)
            cout<<ans[i][j]<<' ';
        cout<<endl;
    }
    return 0;
}
