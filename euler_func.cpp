#include<bits/stdc++.h>
#define N 100
using namespace std;
bool check[N+10];
long long prime[N+10],fai[N+10],tot=0;
int main(){
	memset(check,0,sizeof check);

	fai[1]=1;
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
	for (int i=1;i<=20;i++)
		cout<<fai[i]<<' ';
	cout<<endl;
	return 0;
}
