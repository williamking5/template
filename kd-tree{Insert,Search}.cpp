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
#include <float.h>
#define maxn 200010
#define alpha 0.7
#define d_num 2
#define INF 9000000000000000000
using namespace std;
struct node_class{
    int value[d_num];
    int split,size;
    int left,right,father;
    int id;
} node[2*maxn],dataNum[2*maxn];
int memoryNum[2*maxn];
int currentd;
bool cmp(node_class a,node_class b){
    return a.value[currentd]<b.value[currentd];
}
struct stack_struct{
    int pool[2*maxn],size,top;
    stack_struct(){
        size = 0;
    }
    void push(int x){
        pool[size++] = x;
        top = x;
    }
    void pop(){
        size--;
        if (size>0) top = pool[size-1];
    }
    void init(int n){
        for (int i = 1;i<=n;i++)
            push(i);
    }
} pool,searchStack;
struct kd_tree{
    int root;
    int rebuildNode,vis_top;
    long long currentNear;
    int currentNode;
    kd_tree(){
        currentd = root = 0;
    }
    double calVarience(int l,int r,int d){
        double x2=0,xbar=0;
        for (int i = l;i<=r;i++){
            x2+=1LL*dataNum[i].value[d]*dataNum[i].value[d];
            xbar+=dataNum[i].value[d];
        }
        xbar/=(r-l+1);
        return x2/(r-l+1)-xbar*xbar;
    }
    long long calDistance(node_class a,node_class b){
        long long ans = 0;
        for (int i = 0;i<d_num;i++)
            ans+=1LL*(a.value[i]-b.value[i])*(a.value[i]-b.value[i]);
        return ans;
    }
    void downSearch(int root,node_class t){
        if (!root) return ;
        int sonnode = 0, d = node[root].split;
        searchStack.push(root);
        long long tmpdis = calDistance(node[root],t);
        if (tmpdis < currentNear) {
            currentNode = root;
            currentNear = tmpdis;
        }
        else if (tmpdis == currentNear){
            if (node[root].id<node[currentNode].id||currentNode ==0) currentNode = root;
        }

        if (node[root].value[d]>=t.value[d])
            sonnode = node[root].left;
        else sonnode = node[root].right;
        if (sonnode) downSearch(sonnode,t);
        else return;
    }
    int search(int root,node_class t){
        currentNear = INF;
        currentNode = 0;
        downSearch(root,t);

        while (searchStack.size){
            int topNode = searchStack.top;
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

        return currentNode;
    }
    int tmpinsert(int root, node_class x,int d){
        if (kd_tree :: root == 0){
            root = kd_tree::root = pool.top;
            pool.pop();
            node[root] = x;
            node[root].split = node[root].left = node[root].right = node[root].father = 0;
            node[root].size = 1;
            return root;
        }

        if (root == 0){
            root = pool.top;
            node[root] = x;
            node[root].left = node[root].right = 0;
            node[root].split = d;
            node[root].size = 1;
            pool.pop();
            return root;
        }
        else {
            node[root].size++;
            d = node[root].split;
            if (x.value[d]<=node[root].value[d]) {
                if (!node[root].left){
                    node[root].left = tmpinsert(node[root].left,x,(d+1)%d_num);
                    node[node[root].left].father = root;
                }
                else tmpinsert(node[root].left,x,d);
            }
            else {
                if (!node[root].right){
                    node[root].right = tmpinsert(node[root].right,x,(d+1)%d_num);
                    node[node[root].right].father = root;
                }
                else tmpinsert(node[root].right,x,d);
            }
        }
        if (node[root].size*alpha<max(node[node[root].left].size,node[node[root].right].size)) rebuildNode = root;
        return 0;     
    }
    void travel(int root){
        if (!root) return ;
        travel(node[root].left);
        dataNum[vis_top] = node[root];
        dataNum[vis_top].left = dataNum[vis_top].right = dataNum[vis_top].father =dataNum[vis_top].split =0;
        memoryNum[vis_top] = root;
        vis_top++;
        travel(node[root].right);
    }
    int tmpbuild(int root,int l,int r){
        if (l>r) return 0;
        double max=-1;
        int d=0;
        for (int i = 0;i<d_num;i++){
            double tmpmax = calVarience(l,r,i);
            if (tmpmax>max){
                max = tmpmax;
                d = i;
            }
        }

        currentd = d;
        sort(dataNum+l,dataNum+r+1,cmp);
        int mid = (l+r)>>1;
        while (mid<r&&dataNum[mid].value[d]==dataNum[mid+1].value[d]) mid++;
        node[memoryNum[mid]] = dataNum[mid];
        int tmpmid = mid;
        mid = memoryNum[mid];
        node[mid].split = d;
        node[mid].father = root;
        node[mid].size = r-l+1;
        node[mid].left = tmpbuild(mid,l,tmpmid-1);
        node[mid].right = tmpbuild(mid,tmpmid+1,r);
        return mid;
    }
    void rebuild(int root){
        vis_top = 0;
        travel(root);
        int father = node[root].father;
        int newroot = tmpbuild(father,0,vis_top-1);
        if (father){
            if (node[father].left == root) node[father].left = newroot;
            else node[father].right = newroot;
        }
        else kd_tree::root = newroot;
    }
    void Insert(node_class x){
        rebuildNode = 0;
        tmpinsert(root,x,0);
        if (rebuildNode) rebuild(rebuildNode);
    }
    void clearTree(int root){
        if (!root) return ;
        clearTree(node[root].left);
        clearTree(node[root].right);
        node[root].left = node[root].right = node[root].father = node[root].size = 0;
        pool.push(root);
    }
    void clear(){
        clearTree(root);
        root = 0;
    }
} kdtree;
struct Point_struct{
    int x,y,c,id;
    int ans;
} points[maxn],ope[maxn];
bool cmp1(Point_struct a,Point_struct b){
    return a.c<b.c;
}
bool cmp2(Point_struct a,Point_struct b){
    return a.id<b.id;
}
int main(){
    pool.init(maxn);
int t;
scanf("%d",&t);
while (t--){
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i = 0;i<n;i++){
        scanf("%d%d%d",&points[i].x,&points[i].y,&points[i].c);
        points[i].id = i+1;
    }
    sort(points,points+n,cmp1);
    for (int i =0;i<m;i++){
        scanf("%d%d%d",&ope[i].x,&ope[i].y,&ope[i].c);
        ope[i].id =i;
    }
    sort(ope,ope+m,cmp1);

    int j =0;
    node_class toInsert,toSearch;
    for (int i = 0;i<m;i++){
        while (j<n&&points[j].c<=ope[i].c){
            toInsert.id = points[j].id;
            toInsert.value[0] = points[j].x;
            toInsert.value[1] = points[j].y;
            kdtree.Insert(toInsert);
            j++;
        }

        toSearch.value[0] = ope[i].x;
        toSearch.value[1] = ope[i].y;
        ope[i].ans = node[kdtree.search(kdtree.root,toSearch)].id;
    }

    sort(ope,ope+m,cmp2);
    sort(points,points+n,cmp2);
    for (int i = 0;i<m;i++)
        printf("%d %d %d\n", points[ope[i].ans-1].x,points[ope[i].ans-1].y,points[ope[i].ans-1].c);
    kdtree.clear();
}
    return 0;
}
