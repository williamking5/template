//划分树，可以维护比K位大的区间数之和以及比K位小的区间数之和。
#include<iostream>
#include<algorithm>
#define NUM 100000
#define H 20
using namespace std;
struct node{
	int data,HASH;
};
int cmp(node a,node b){
	if (a.data<b.data) return 1;
	if (a.data>b.data) return -1;
	if (a.HASH<b.HASH) return 1;
	if (a.HASH>b.HASH) return -1;
	return 0;
}
int sortcmp(node a,node b){
	if (a.data<b.data) return 1;
	if (a.data>b.data) return 0;
	if (a.HASH<b.HASH) return 1;
	return 0;
}
node tree[H][NUM];
node a[NUM];
int as[H][NUM];
long long sum[H][NUM];
long long ans,total;
void build(int ll,int rr,int d){
	int mid=(ll+rr)/2,j=ll,k=mid+1;
	node MD=a[mid];

	if (cmp(tree[d][ll],MD)>=0) as[d][ll]++;
	for (int i=ll+1;i<=rr;i++)
		if (cmp(tree[d][i],MD)>=0) as[d][i]=as[d][i-1]+1;
		else as[d][i]=as[d][i-1];

	for (int i=ll;i<=rr;i++)
		sum[d][i]=sum[d][i-1]+tree[d][i].data;

	for (int i=ll;i<=rr;i++){
		if (j<=mid&&cmp(tree[d][i],MD)>=0){
			tree[d+1][j++]=tree[d][i];
			continue;
		}
		tree[d+1][k++]=tree[d][i];
	}

	if (ll==rr) return;
	build(ll,mid,d+1);
	build(mid+1,rr,d+1);
}
node select(int left,int right,int ll,int rr,int k,int d){
	if (left==right)
		return tree[d][left];

	int s,ss,mid=(left+right)/2;
	if (ll==left) s=0;
	else s=as[d][ll-1];

	if (ll==left) ss=as[d][rr];
	else ss=as[d][rr]-as[d][ll-1];

	if (k<=ss) {
		ans+=sum[d+1][mid+rr-left+1-as[d][rr]]-sum[d+1][ll-left-s+mid];
		return select(left,mid,left+s,left+s+ss-1,k,d+1);
	}
	else {
		ans-=sum[d+1][left+as[d][rr]-1]-sum[d+1][left+s-1];
		return select(mid+1,right,mid+1+ll-left-s,mid+1+rr-left-s-ss,k-ss,d+1);
	}
}
int main(){
	int i,j,m,n;
	cin>>n>>m;
	memset(tree,0,sizeof tree);
	for (i=1;i<=n;i++){
		cin>>tree[0][i].data;
		tree[0][i].HASH=i;
		a[i]=tree[0][i];
	}

	sort(a+1,a+n+1,sortcmp);

	build(1,n,0);

	int x,y;
	for (int i=0;i<m;i++){
		ans=0;
		cin>>x>>y;
		node tmp=select(1,n,x,y,(x+y)/2-x+1,0);
		if ((y-x)%2) ans-=tmp.data;
		total+=ans;
	}

	cout<<total<<endl;
	return 0;
}
