#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<set>
#include<queue>
using namespace std;
struct node_class{
    int degree,num;
    node_class(int a,int b){
        degree=a;
        num=b;
    }
};
set<int> MAP[10010];
set<int>::iterator iter;
set<node_class> degree;
set<node_class>::iterator diter;
bool operator < (node_class a,node_class b){
    return a.degree < b.degree || a.degree==b.degree&&a.num<b.num;
}
long long value[10010];
bool vis[10010];
int sum=0;
long long dfs(int root){
    long long ans=value[root];

    set<int>::iterator iter;

    vis[root]=1;
    sum++;
    for (iter=MAP[root].begin();iter!=MAP[root].end();iter++){
        if (!vis[*iter]) ans+=dfs(*iter);
    }
    return ans;
}
int main(){
int T;
scanf("%d",&T);
while (T--){
    int p,m;
    scanf("%d%d",&p,&m);
    for (int i=1;i<=p;i++){
        scanf("%lld",value+i);
		MAP[i].clear();
	}

	degree.clear();
    int x,y;
    for (int i=0;i<m;i++){
        scanf("%d%d",&x,&y);
        MAP[x].insert(y);
        MAP[y].insert(x);
    }

    for (int i=1;i<=p;i++)
        degree.insert(node_class(MAP[i].size(),i));

    while (degree.size()){
        node_class tmp=*degree.begin();
        if (tmp.degree>1) break;
        if (tmp.degree<1) {
            degree.erase(degree.begin());
            continue;
        }

        iter=MAP[tmp.num].begin();
        MAP[*iter].erase(tmp.num);

        int now=MAP[*iter].size();
        degree.erase(degree.begin());
        degree.erase(node_class(now+1,*iter));
        degree.insert(node_class(now,*iter));
        MAP[tmp.num].erase(*iter);
    }

	long long SUM=0;
    memset(vis,0,sizeof vis);
    for (int i=1;i<=p;i++){
        sum=0;
        if (MAP[i].size()&&!vis[i]){
            long long ans=dfs(i);
            if (sum%2){
                SUM+=ans;
            }
        }
    }
	printf("%lld\n",SUM);
}
    return 0;
}
