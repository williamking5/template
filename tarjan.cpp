#include<iostream>
#include<stdio.h>
#include<math.h>
#include<string.h>
#define MAX 100000
#pragma comment(linker,"/STACK:102400000,102400000")
using namespace std;
struct edge{
	edge * next;
	int t;
	edge(){
		t=0;
		next=NULL;
	}
} v[MAX];
int edgetotal,head[MAX];
void add(int from,int to){
	edgetotal++;
	v[edgetotal].t=to;
	if (head[from]) v[edgetotal].next=v+head[from];
	head[from]=edgetotal;
}
int belong[MAX],low[MAX],dfn[MAX],dindex,instack[MAX],stop,bcnt,Stap[MAX];
void solve();
void tarjan(int i){
    int j;
    dfn[i]=low[i]=++dindex;
    instack[i]=true;
    Stap[++stop]=i;

    edge *e=NULL;
    if (head[i]) e=v+head[i];
    while (e){
        j=e->t;
        if (!dfn[j]){
            tarjan(j);
            if (low[j]<low[i])
                low[i]=low[j];
        }
        else if (instack[j] && dfn[j]<low[i])
            low[i]=dfn[j];
        e=e->next;
    }
    if (dfn[i]==low[i]){
        bcnt++;
        do{
            j=Stap[stop--];
            instack[j]=false;
            belong[j]=bcnt;
        }
        while (j!=i);
    }
}
void solve(int N){
    int i;
    stop=bcnt=dindex=0;
    memset(dfn,0,sizeof(dfn));
    for (i=1;i<=N;i++)
        if (!dfn[i])
            tarjan(i);
}
int main(){
	int n,m;
	cin>>n>>m;

	for (int i=1;i<=m;i++){
		int tmp1,tmp2;
		cin>>tmp1>>tmp2;
		add(tmp1,tmp2);
	}

	solve(n);

	for (int i=1;i<=n;i++)
		cout<<belong[i]<<" ";
    cout<<endl;
	return 0;
}
