#include<iostream>
#include<stdio.h>
using namespace std;
struct sbt{
	int left,right,size;
	long long data,maxans,dmax;
};
int cmp(long long a,long long b){
    if (a<b) return 1;
    if (a==b) return 0;
    if (a>b) return -1;
}
long long max(long long a,long long b){
    if (a>b) return a;
    else return b;
}
class SBT{
public:
	int top,root;
	sbt* tree;

	SBT(int n){
		tree=new sbt[n+1];
		top=root=0;
		for (int i=0;i<=n;i++)
			tree[i].left=tree[i].right=tree[i].size=0;
	}
	void left_rot(int &x){
		int y=tree[x].right;
		tree[x].right=tree[y].left;
		tree[y].left=x;
		tree[y].size=tree[x].size;
		tree[y].maxans=max(tree[tree[y].left].maxans,tree[tree[y].right].maxans);
		tree[y].maxans=max(tree[y].maxans,tree[y].dmax);
		tree[x].size=tree[tree[x].left].size+tree[tree[x].right].size+1;
		tree[x].maxans=max(tree[tree[x].left].maxans,tree[tree[x].right].maxans);
		tree[x].maxans=max(tree[x].maxans,tree[x].dmax);
		x=y;
	}
	void right_rot(int &x){
		int y=tree[x].left;
		tree[x].left=tree[y].right;
		tree[y].right=x;
		tree[y].size=tree[x].size;
		tree[y].maxans=max(tree[tree[y].left].maxans,tree[tree[y].right].maxans);
		tree[y].maxans=max(tree[y].maxans,tree[y].dmax);
		tree[x].size=tree[tree[x].left].size+tree[tree[x].right].size+1;
		tree[x].maxans=max(tree[tree[x].left].maxans,tree[tree[x].right].maxans);
		tree[x].maxans=max(tree[x].maxans,tree[x].dmax);
		x=y;
	}
	void Maintain(int &x,bool flag){
		if (!flag){
			if (tree[tree[tree[x].left].left].size>tree[tree[x].right].size)
				right_rot(x);
			else
			if (tree[tree[tree[x].left].right].size>tree[tree[x].right].size)
				left_rot(tree[x].left),right_rot(x);
			else
			return;
		}
		else{
			if (tree[tree[tree[x].right].right].size>tree[tree[x].left].size)
				left_rot(x);
			else
			if (tree[tree[tree[x].right].left].size>tree[tree[x].left].size)
				right_rot(tree[x].right),left_rot(x);
			else
			return;
		}
		Maintain(tree[x].left,0);
		Maintain(tree[x].right,1);
		Maintain(x,1);
		Maintain(x,0);
	}
	void insert(int &x,long long data,long long maxans){
		if (x==0){
			x=++top;
			tree[x].size=1;
			tree[x].left=tree[x].right=0;
			tree[x].data=data;
			tree[x].maxans=tree[x].dmax=maxans;
		}
		else{
			tree[x].size++;
			tree[x].maxans=max(tree[x].maxans,maxans);
			if (cmp(data,tree[x].data)==1) insert(tree[x].left,data,maxans);
			else {
                if (cmp(data,tree[x].data)==-1) insert(tree[x].right,data,maxans);
			}
			Maintain(x,data>=tree[x].data);
		}
	}
	void Insert(long long data,long long maxans){
        insert(root,data,maxans);
	}
    void showx(int i){
        if (!i) return ;
        cout<<i<<'\t'<<"["<<tree[i].data<<"]"<<'\t'<<"["<<tree[i].maxans<<"]"<<'\t'<<tree[i].left<<'\t'<<tree[i].right<<endl;
        showx(tree[i].left);
        showx(tree[i].right);
    }
    void show(){
        cout<<"Number"<<'\t'<<"[Data]"<<'\t'<<"[MAX]"<<'\t'<<"Left"<<'\t'<<"Right"<<endl;
        showx(root);
    }
    long long getans(long long x){
        long long i=root,ans=0;
        while (i){
            if (tree[i].data<x){
                ans=max(tree[i].dmax,ans);
                if (tree[i].left) ans=max(ans,tree[tree[i].left].maxans);
                i=tree[i].right;
            }
            else {
                if (tree[i].data==x){
                    if (tree[i].left) ans=max(ans,tree[tree[i].left].maxans);
                    break;
                }
                else i=tree[i].left;
            }
        }
        return ans;
    }
};
long long f[100001];
SBT a(100001);
int main(){
    long long i,j,r,h,n;
    cin>>n;
    cin>>r>>h;
    f[0]=r*r*h;
    a.Insert(f[0],f[0]);
    for (i=1;i<n;i++){
        cin>>r>>h;
        j=a.getans(r*r*h);
        f[i]=j+r*r*h;
        a.Insert(r*r*h,f[i]);
    }
    long long max=0;
    for (i=0;i<n;i++)
        max=(f[i]<max?max:f[i]);
    printf("%.9lf\n",max*3.14159265358979);
	return 0;
}
