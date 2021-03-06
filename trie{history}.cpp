#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
#define N 600005
#define inf 2000000000
using namespace std;
int bin[30];
int n,m;
int a[N],b[N],root[N];
struct trie{
	int cnt;
	int ch[N*24][2],sum[N*24];
	int insert(int x,int val){
		int tmp,y;tmp=y=++cnt;
		for(int i=23;i>=0;i--){
			ch[y][0]=ch[x][0];ch[y][1]=ch[x][1];
			sum[y]=sum[x]+1;
			int t=val&bin[i];t>>=i;
			x=ch[x][t];
			ch[y][t]=++cnt;
			y=ch[y][t];
		}
		sum[y]=sum[x]+1;
		return tmp;
	}
	int query(int l,int r,int val){
		int tmp=0;
		for(int i=23;i>=0;i--){
			int t=val&bin[i];t>>=i;
			if(sum[ch[r][t^1]]-sum[ch[l][t^1]])
				tmp+=bin[i],r=ch[r][t^1],l=ch[l][t^1];
			else r=ch[r][t],l=ch[l][t];
		}
		return tmp;
	}
}trie;
int main(){
	bin[0]=1;for(int i=1;i<30;i++)bin[i]=bin[i-1]<<1;
	scanf("%d%d",&n,&m);
	n++;
	for(int i=2;i<=n;i++) scanf("%d",a+i);
	for(int i=1;i<=n;i++)b[i]=b[i-1]^a[i];
	for(int i=1;i<=n;i++)
		root[i]=trie.insert(root[i-1],b[i]);
	char ch[5];
	int l,r,x;
	while(m--)
	{
		scanf("%s",ch);
		if(ch[0]=='A')
		{
			n++;
			scanf("%d",a+n);b[n]=b[n-1]^a[n];
			root[n]=trie.insert(root[n-1],b[n]);
		}
		else
		{
			scanf("%d%d%d",&l,&r,&x);
			printf("%d\n",trie.query(root[l-1],root[r],b[n]^x));
		}
	}
	return 0;
}
