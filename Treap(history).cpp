#include <iostream> 
#include <cstdio> 
#include <cstring> 
#include <string> 
#include <cmath> 
#include <cstdlib> 
#include <fstream> 
#include <vector> 
#include <set> 
#define INF 1000000000
#define maxn 100010
using namespace std; 
struct node { 
    node* ch[2]; 
    int MIN,MAX;
    int c;
    int sz, r; 
    void up() 
    { 
        sz = ch[0]->sz + ch[1]->sz + 1; 
        MIN = min(ch[0]->MIN,ch[1]->MIN);
        MIN = min(c,MIN);
        MAX = max(ch[0]->MAX,ch[1]->MAX);
        MAX = max(c,MAX);
    } 
} *null; 
void out(node *o){
    if (o == null) return;
    out(o->ch[0]);
    printf("%d ", o->c);
    out(o->ch[1]);
}
node *origin,*rever,*currentRoot; 
int s[maxn];
void newnode(node* &x, int cc = 0) 
{ 
    x = new node(); 
    x->c = cc; 
    x->sz = 1; 
    x->r = rand(); 
    x->ch[0] = x->ch[1] = null; 
} 
   
void copy(node* &x, node* y) 
{ 
    if (y == null) x = y; 
    else newnode(x), *x = *y;///可持久化时，修改操作经过的路径要新建节点 
} 
   
void merge(node* &o, node* a, node* b) 
{ 
    if (a == null) copy(o, b); 
    else if (b == null) copy(o, a); 
    else if (a->r < b->r) 
    { 
        copy(o, a); 
        merge(o->ch[1], a->ch[1], b); 
        o->up(); 
    } 
    else 
    { 
        copy(o, b); 
        merge(o->ch[0], a, b->ch[0]); 
        o->up(); 
    } 
} 
void split(node* o, node* &a, node* &b, int k) 
{ 
    if (!k) { 
        copy(b, o); 
        a = null; 
    } 
    else if (o->sz <= k){ 
       copy(a, o); 
       b = null; 
    } 
    else if (o->ch[0]->sz >= k) 
    { 
        copy(b, o); 
        split(o->ch[0], a, b->ch[0], k); 
        b->up(); 
    } 
    else 
    { 
        copy(a, o); 
        split(o->ch[1], a->ch[1], b, k - o->ch[0]->sz - 1); 
        a->up(); 
    } 
} 
   
void build(node* &o, int l, int r) 
{ 
    if (l > r) return ; 
    int m = (l + r) >> 1; 
    newnode(o, s[m]); 
    build(o->ch[0], l, m - 1); 
    build(o->ch[1], m + 1, r); 
    o->up(); 
} 
   
void Init() 
{ 
    srand(time(NULL));
    newnode(null); 
    null->sz = 0; 
    null->MIN = INF;
    null->MAX = 0;
    rever = origin = null;
} 
int tmpAsk(node *o,int x){
    if (o->MAX>=x && o->MIN<x) return (o->c<x)+tmpAsk(o->ch[0],x)+tmpAsk(o->ch[1],x);
    else if (o->MAX<x) return o->sz;
    else return 0;
}
int Ask(int n,int l,int r,int x){
    node *a,*b,*c,*d;
    split(origin,a,b,l-1);
    split(b,c,d,r-l+1);
    return tmpAsk(c,x);
}
void tmpSwap(node *&o,int l1,int r1,int l2,int r2){
    node *a,*b,*c,*d,*e,*f;
    split(o,a,b,l1-1);
    split(b,c,d,r1-l1+1);
    split(d,b,e,l2-1-r1);
    split(e,d,f,r2-l2+1);
    node *tmp1,*tmp2,*tmp3;
    merge(tmp1,a,d);
    merge(tmp2,tmp1,b);
    merge(tmp3,tmp2,c);
    merge(o,tmp3,f);
}
void Swap(int n,int l1,int r1,int l2,int r2){
    if (l1>l2) {
        swap(l1,l2);
        swap(r1,r2);
    }
    tmpSwap(origin,l1,r1,l2,r2);
    tmpSwap(rever,n+1-r2,n+1-l2,n+1-r1,n+1-l1);
}
void Reverse(int n,int l,int r){
    node *a,*b,*c,*d,*e,*f,*g;
    split(origin,a,b,l-1);
    split(b,c,d,r-l+1);
    split(rever,b,e,n-r);
    split(e,f,g,r-l+1);
    node *tmp1,*tmp2,*tmp3;
    merge(tmp1,a,f);
    merge(origin,tmp1,d);
    merge(tmp2,b,c);
    merge(rever,tmp2,g);
}
   
int main(){
    Init();
    int n;
    scanf("%d",&n);
    for (int i =1;i<=n;i++)
        scanf("%d",s+i);
    build(origin,1,n);
    for (int i =1;i*2<=n;i++)
        swap(s[i],s[n+1-i]);
    build(rever,1,n);
 
    int m,x,y,z,l1,l2,r1,r2;
    char ope[10];
    scanf("%d",&m);
    for (int i =0;i<m;i++){
        scanf("%s",ope);
        if (ope[0] == 'A'){
            scanf("%d%d%d",&x,&y,&z);
            printf("%d\n", Ask(n,x,y,z));
        }
        else if (ope[0] == 'S'){
            scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
            Swap(n,l1,r1,l2,r2);
        }
        else if (ope[0] == 'R'){
            scanf("%d%d",&x,&y);
            Reverse(n,x,y);
        }
    }
    return 0;
}
