#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <math.h>
#include <set>
#include <map>
#include <vector>
using namespace std;
map<string, int> mm;
int father[100009],RANK[100009];
//找到根节点并且压缩路径，同时计算与根节点的关系RANK
int find(int x)
{
    if(x==father[x])
    return x;
    int tmp=father[x];
    father[x]=find(tmp);
    RANK[x]=(RANK[x]+RANK[tmp])%2;
    return father[x];
}
int main(){
	int n,m,q;
	cin>>n>>m>>q;
	string tmp,tmp1;
	for (int i=1;i<=n;i++){
		cin>>tmp;
		mm[tmp]=i;
		father[i]=i;
		RANK[i]=0;
	}

	int kind,x,y;
	for (int i=1;i<=m;i++){
		cin>>kind>>tmp>>tmp1;
		kind++;
		kind%=2;
		x=mm[tmp];
		y=mm[tmp1];

		int fatherx=find(x),fathery=find(y);
		if (fatherx==fathery) {
   //在判断关系的时候，要具体情况具体分析，不一定是mod 2关系，但如果只有两类，一般采取mod 2关系，1代表相反，0代表相同。
      if ((RANK[x]+RANK[y])%2!=(kind%2)){
				printf("NO\n");
			}
			else printf("YES\n");
		}
		else {
			father[fatherx]=fathery;
			RANK[fatherx]=(RANK[x]+RANK[y]+kind)%2;
			printf("YES\n");
		}
	}

	for (int i=0;i<q;i++){
		cin>>tmp>>tmp1;
		x=mm[tmp];y=mm[tmp1];
		int fatherx,fathery;
		fatherx=find(x);fathery=find(y);
		if (fatherx!=fathery){
			printf("3\n");
		}
		else {
			if ((RANK[x]+RANK[y])%2==0){
				printf("1\n");
			}
			else printf("2\n");
		}
	}
	return 0;
}
