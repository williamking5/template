#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <string.h>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#define d_num 2
#define INF 1000000000000000000
using namespace std;
int currentd,root;
struct node_class{
    int value[d_num];
    int split;
    int left,right,father;
} node[100010];
bool cmp(node_class a,node_class b){
    return a.value[currentd]<b.value[currentd];
}
int build(int root,int l,int r,int d){
    if (l>r) return 0;
    currentd = d;
    sort(node+l,node+r+1,cmp);
    int mid = (l+r)>>1;
    node[mid].split = d;
    node[mid].father = root;
    node[mid].left = build(mid,l,mid-1,(d+1)%d_num);
    node[mid].right = build(mid,mid+1,r,(d+1)%d_num);
    return mid;
}
long long calDistance(node_class a,node_class b){
    long long ans = 0;
    for (int i = 0;i<d_num;i++)
        ans+=1LL*(a.value[i]-b.value[i])*(a.value[i]-b.value[i]);
    return ans;
}
int stackNode[100010];
struct stack_struct{
    int size;
    void push(int x){
        stackNode[size++] = x;
    }
    void pop(){
        size--;
    }
    int top(){
        return stackNode[size-1];
    }
} searchStack;
long long currentNear;
void downSearch(int root,node_class t){
    if (!root) return ;
    int sonnode = 0, d = node[root].split;
    searchStack.push(root);
    currentNear = min(currentNear,calDistance(node[root],t));

    if (node[root].value[d]>=t.value[d])
        sonnode = node[root].left;
    else sonnode = node[root].right;
    if (sonnode) downSearch(sonnode,t);
    else return;
}
void search(int root,node_class t){
    currentNear = INF;
    downSearch(root,t);

    while (searchStack.size){
        int topNode = searchStack.top();
        int d = node[topNode].split;
        searchStack.pop();
        long long cha = t.value[d]-node[topNode].value[d];
        if (cha*cha<=currentNear) {
            int sonnode = 0;
            if (t.value[d]<=node[topNode].value[d]) sonnode = node[topNode].right;
            else sonnode = node[topNode].left;
            downSearch(sonnode,t);
        }
    }
}
void dfs(int root){
    if (!root) return ;
    cout<<root<<" "<<node[root].left<<" "<<node[root].right<<" "<<node[root].value[0]<<" "<<node[root].value[1]<<endl;
    dfs(node[root].left);
    dfs(node[root].right);
}
int main(){
    int n,x,y;
    scanf("%d",&n);
    for (int i = 1;i<=n;i++){
        scanf("%d%d",&node[i].value[0],&node[i].value[1]);
    }
    build(0,1,n,0);
    root = (1+n)>>1;

    node_class tofind;
for (int i = 0;i<n;i++){
        scanf("%d%d",&tofind.value[0],&tofind.value[1]);
        search(root,tofind);
        printf("%lld\n",currentNear);
}
    return 0;
}
/*
2
8 6
9 2
6 3
*/
