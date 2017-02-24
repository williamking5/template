/*查询在第一关键字满足某个范围的前提下，第二关键字的最大值，采用treap实现*/
#include<bits/stdc++.h>
using namespace std;
struct DATA{
    int x,y,MAX;
    DATA(int t,int u){x=t;y=u;MAX=y;}
    DATA(){}
/*产生数学后继*/
    DATA operator()(){
        return DATA(x+1,y);
    }
};
/* 下列比较函数只需要更改<即可 */
bool operator <(const DATA &a,const DATA &b){
    return a.x<b.x;
}
bool operator == (const DATA &a,const DATA &b){
    return !(a<b||b<a);
}
struct NODE{
    int size,HASH,left,right;
    int RANDOM;
    DATA data;
    NODE(){
        left=right=size=0;
    }
};
int top;
NODE tree[2000000];
struct TREAP{
    int root;
    int st[100];
    TREAP(){
        root=0;
        srand(time(NULL));
    }
    void adapt(int x){
		tree[x].size=tree[tree[x].left].size+tree[tree[x].right].size+1;
		tree[x].data.MAX=max(tree[tree[x].left].data.MAX,tree[tree[x].right].data.MAX);
		tree[x].data.MAX=max(tree[x].data.MAX,tree[x].data.y);
	}
    void left_rot(int fa,int x){
		int y=tree[x].right;
		tree[x].right=tree[y].left;
		tree[y].left=x;
		tree[y].size=tree[x].size;
		if (fa){
            if (tree[fa].left==x) tree[fa].left=y;
            else tree[fa].right=y;
		}
		adapt(x);
		adapt(y);
		root=root==x?y:root;
	}
	void right_rot(int fa,int x){
		int y=tree[x].left;
		tree[x].left=tree[y].right;
		tree[y].right=x;
		tree[y].size=tree[x].size;
        if (fa){
            if (tree[fa].left==x) tree[fa].left=y;
            else tree[fa].right=y;
		}
		adapt(x);
		adapt(y);
		root=root==x?y:root;
	}
    void insert(int fa,int x,DATA data){
		if (x==0){
			x=++top;
			if (!root) root=top;
			tree[x].size=1;
			tree[x].left=tree[x].right=0;
			tree[x].data=data;
			tree[x].HASH=top;
			tree[x].RANDOM=rand();
		}
		else{
			tree[x].size++;
			if (data<tree[x].data||(data==tree[x].data)&&(tree[x].HASH>(top+1))) {
                insert(x,tree[x].left,data);
                if (!tree[x].left) tree[x].left=top;
                tree[x].data.MAX=max(data.y,tree[x].data.MAX);
                if (tree[x].RANDOM>tree[tree[x].left].RANDOM) right_rot(fa,x);
            }
			else {
                insert(x,tree[x].right,data);
                if (!tree[x].right) tree[x].right=top;
                tree[x].data.MAX=max(data.y,tree[x].data.MAX);
                if (tree[x].RANDOM>tree[tree[x].right].RANDOM) left_rot(fa,x);
            }
		}
	}
    int remove(int fa,int x,DATA data){
		if (!x) return 0;
		if (tree[x].data<data){
			int kk=remove(x,tree[x].right,data);
			if (kk) {
                tree[x].size--;
                tree[x].data.MAX=max(tree[tree[x].left].data.MAX,tree[tree[x].right].data.MAX);
                tree[x].data.MAX=max(tree[x].data.MAX,tree[x].data.y);
            }
			return kk;
        }
		else
		if (data<tree[x].data){
			int kk=remove(x,tree[x].left,data);
			if (kk) {
                tree[x].size--;
                tree[x].data.MAX=max(tree[tree[x].left].data.MAX,tree[tree[x].right].data.MAX);
                tree[x].data.MAX=max(tree[x].data.MAX,tree[x].data.y);
            }
			return kk;
        }
		else{
			if (tree[x].left!=0&&tree[x].right==0){
				tree[x]=tree[tree[x].left];
				return x;
			}
			else
			if (tree[x].right!=0&&tree[x].left==0){
				tree[x]=tree[tree[x].right];
				return x;
			}
			else
			if (tree[x].left==0&&tree[x].right==0){
				if (root==x) root=0;
				if (fa)
					if (tree[fa].left==x) tree[fa].left=0;
					else tree[fa].right=0;
                return x;
			}
			else{
				int ret=tree[x].right,faa=x;
				tree[x].size--;
				while (tree[ret].left){
                    tree[ret].size--;
                    faa=ret;
                    ret=tree[ret].left;
				}

				if (faa==x) tree[x].right=tree[ret].right;
				else tree[faa].left=tree[ret].right;
                tree[x].data=tree[ret].data;

                if (faa==x) {
                    tree[x].data.MAX=max(tree[tree[x].left].data.MAX,tree[x].data.MAX);
                }
                else {
                    int TOP=0;
                    ret=tree[x].right;st[0]=x;
                    while (ret){
                        st[++TOP]=ret;
                        ret=tree[ret].left;
                    }
                    for (int i=TOP;i>=0;i--){
                        tree[st[i]].data.MAX=max(tree[tree[st[i]].left].data.MAX,tree[tree[st[i]].right].data.MAX);
                        tree[st[i]].data.MAX=max(tree[st[i]].data.y,tree[st[i]].data.MAX);
                    }
                }
                return x;
			}
		}
	}
	void Insert(DATA data){
        insert(0,root,data);
	}
	int Remove(DATA data){
        return remove(root,root,data);
	}
		
	//查询排名第l到第r小的元素中，第二关键字的最大值，通常要引用rank函数才能实现按值查询
	int FUN(int root,int l,int r){
        if (tree[root].size==r&&l==1) return tree[root].data.MAX;
        else {
            int mid=tree[tree[root].left].size;
            if (r<=mid) return FUN(tree[root].left,l,r);
            if (l>=mid+2) return FUN(tree[root].right,l-mid-1,r-mid-1);
            if (r==mid+1) {
                if (l==r) return tree[root].data.y;
                else return max(tree[root].data.y,FUN(tree[root].left,l,r-1));
            }
            if (l==mid+1){
                return max(tree[root].data.y,FUN(tree[root].right,1,r-mid-1));
            }

            int result=max(FUN(tree[root].left,l,mid),FUN(tree[root].right,1,r-mid-1));
            result=max(result,tree[root].data.y);
            return result;
        }
	}
} a;
int main(){
    for (int i=0;i<100000;i++)
        a.Insert(DATA(i,rand()%99999999));
    cout<<a.FUN(a.root,5345,5400);
    return 0;
}
