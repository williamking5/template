#include<bits/stdc++.h>
#define N 100
using namespace std;
bool check[N+10];
long long prime[N+10],mu[N+10],tot=0;
int main(){
	memset(check,0,sizeof check);

	mu[1]=1;
	for (int i=2;i<=N;i++){
		if (!check[i]){
			prime[tot++]=i;
			mu[i]=-1;
		}
		for (int j=0;j<tot;j++){
			if (i*prime[j]>N) break;
			check[i*prime[j]]=true;
			if (i%prime[j]==0){
				mu[i*prime[j]]=0;
				break;
			}
			else {
				mu[i*prime[j]]=-mu[i];
			}
		}
	}
	for (int i=1;i<=20;i++)
		cout<<mu[i]<<' ';
	cout<<endl;
	return 0;
}
