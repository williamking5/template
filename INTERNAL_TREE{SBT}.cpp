#include<stdio.h>
#include<algorithm>
#include<iostream>
using namespace std;
//data默认为int类型，如果要进行修改，请定义新的类型，并重载比较运算符
struct DATA{
    int x;
    DATA (int t){
        x=t;
    }
    DATA (){}
};
bool operator < (const DATA a,const DATA b){
    return a.x<b.x;
}
bool operator > (const DATA a,const DATA b){
    return a.x>b.x;
}
bool operator == (const DATA a,const DATA b){
    return a.x==b.x;
}
bool operator != (const DATA a,const DATA b){
    return a.x!=b.x;
}
struct data_class{
    int HASH;
	DATA data;
    data_class(int h,DATA d){
        HASH=h;data=d;
    }
    data_class(){}
};
bool operator < (const data_class a,const data_class b){
    return (a.data<b.data||a.data==b.data&&a.HASH<b.HASH);
}
bool operator > (const data_class a,const data_class b){
    return (a.data>b.data||a.data==b.data&&a.HASH>b.HASH);
}
bool operator == (const data_class a,const data_class b){
    return a.data==b.data&&a.HASH==b.HASH;
}
bool operator >= (const data_class a,const data_class b){
    return a>b||a==b;
}
struct sbt
{
    int left,right,size;
    data_class data;
    sbt(){
        left=right=0;
        size=0;
    }
};
sbt tree[1000000];
int top;
struct SBT{
public:
    int root;
    SBT(){
        root=0;
    }
	int datacmp(const data_class a,const data_class b){
		if (a.data<b.data) return 1;
		if (a.data>b.data) return -1;
		return 0;
	}
	//如果要维护父亲节点和儿子节点的其他域值则修改adapt
	void adapt(int x){
		tree[x].size=tree[tree[x].left].size+tree[tree[x].right].size+1;
	}
	DATA getDATA(int n){
        return tree[n].data.data;
	}
	void left_rot(int &x){
		int y=tree[x].right;
		tree[x].right=tree[y].left;
		tree[y].left=x;
		tree[y].size=tree[x].size;
		adapt(x);
		x=y;
	}
	void right_rot(int &x){
		int y=tree[x].left;
		tree[x].left=tree[y].right;
		tree[y].right=x;
		tree[y].size=tree[x].size;
		adapt(x);
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
	void insert(int &x,data_class data){
		if (x==0){
			x=++top;
			tree[x].size=1;
			tree[x].left=tree[x].right=0;
			tree[x].data=data;
		}
		else{
			tree[x].size++;
			if (data<tree[x].data) insert(tree[x].left,data);
			else insert(tree[x].right,data);
			Maintain(x,data>=tree[x].data);
		}
	}
	int remove(int fa,int &x,data_class data){
		if (!x) return 0;
		tree[x].size--;
		if (datacmp(data,tree[x].data)==-1)
			remove(x,tree[x].right,data);
		else
		if (datacmp(data,tree[x].data)==1)
			remove(x,tree[x].left,data);
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
			}
			else{
				int ret=tree[x].right;
				while (tree[ret].left)
					ret=tree[ret].left;
				tree[x].data=tree[ret].data;
				remove(x,tree[x].right,tree[ret].data);
			}
		}
	}
	data_class select(int &x,int k){
		int r=tree[tree[x].left].size+1;
		if (k<r) return select(tree[x].left,k);
		else
		if (k>r) return select(tree[x].right,k-r);
		else
		return tree[x].data;
	}
	int rank(int &x,data_class data){
		if (x==0) return 0;
		if (data>tree[x].data) return tree[tree[x].left].size+1+rank(tree[x].right,data);
		else
		if (data<tree[x].data) return rank(tree[x].left,data);
		else
		return tree[tree[x].left].size+1;
	}
	//插入一个数
	void Insert(int data){
		insert(root,data_class(top+1,data));
	}
	//删除一个数，在相同的情况下，任意删除其中一个
	void Remove(int data){
		remove(0,root,data_class(0,data));
	}
	//查询第k小的数字
	DATA Select(int k){
		return select(root,k).data;
	}
	//查询比data小（严格）的数字有多少个
	int Rank(int data){
		return rank(root,data_class(-1,data));
	}
	//查找data是否存在
	bool Find(int data){
		if (!root) return 0;
		else {
			int x=root;
			while (tree[x].data.data!=data&&x){
				if (tree[x].data.data<data) x=tree[x].right;
				else x=tree[x].left;
			}
			if (!x) return 0;
			else if (tree[x].data.data==data) return 1;
		}
	}
	//统计data一共有多少个
	int Count(int data){
		bool exi=Find(data);
		if (exi){
			int aaa=Rank(data);
			int bbb=Rank(data+1);
			return bbb-aaa;
		}
		else return 0;
	}
};
struct INTERVAL_DATA{
    int left,right;
    SBT SET;
    INTERVAL_DATA(){
        left=right=0;
    }
};
int st[10000],TOP=-1;
struct INTERVAL_TREE{
    int n;
    INTERVAL_DATA *tree;
    INTERVAL_TREE(int height){
        tree=new INTERVAL_DATA[2<<height];
        n=height;

        int h=0;
        tree[0].left=0;tree[0].right=(1<<n)-1;
        for (int i=0;i<((1<<n)-1);i++){
            if (i>(2<<h)-2) h++;
            tree[i*2+1].left=tree[i].left;
            tree[i*2+2].left=(1<<(n-h-1))|tree[i].left;
            tree[i*2+1].right=tree[i*2+1].left+(1<<(n-h-1))-1;
            tree[i*2+2].right=tree[i*2+2].left+(1<<(n-h-1))-1;
        }
        tree[0].left++;tree[0].right++;
        for (int i=0;i<(1<<n)-1;i++){
            tree[i*2+1].left++;tree[i*2+1].right++;
            tree[i*2+2].left++;tree[i*2+2].right++;
        }
    }
    void add(int index,int x){
        index+=(1<<n)-2;
        while (index){
            tree[index].SET.Insert(x);
            index=(index-1)>>1;
        }
        tree[0].SET.Insert(x);
    }
    void change(int index,int y){
        index+=(1<<n)-2;
        int x=tree[index].SET.getDATA(tree[index].SET.root).x;
        while (index){
            tree[index].SET.Remove(x);
            tree[index].SET.Insert(y);
            index=(index-1)>>1;
        }
        tree[0].SET.Remove(x);
        tree[0].SET.Insert(y);
    }
    void getinterval(int root,int l,int r){
        if (tree[root].left==l&&tree[root].right==r) st[++TOP]=root;
        else {
            int mid=(tree[root].left+tree[root].right)/2;
            if (r<=mid) getinterval(root*2+1,l,r);
            else if (l>mid) getinterval(root*2+2,l,r);
            else {
                getinterval(root*2+1,l,mid);
                getinterval(root*2+2,mid+1,r);
            }
        }
    }
} a(16);
int getans(int I,int J,int K){
    TOP=-1;
    K--;
    a.getinterval(0,I,J);

    int Max=1000000000,Min=-1,tmp=0,RANK;
    while (Max-Min>1){
        tmp=(Max+Min)/2;
        RANK=0;
        for (int i=0;i<=TOP;i++)
            RANK+=a.tree[st[i]].SET.Rank(tmp);
        if (RANK<=K) Min=tmp;
        else Max=tmp;
    }
    return Min;
}
int main(){
    int n,m,tmp;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++){
        scanf("%d",&tmp);
        a.add(i,tmp);
    }

    char ord[3];
    int I,J,K;
    for (int i=1;i<=m;i++){
        scanf("%s",ord);
        if (ord[0]=='Q'){
            scanf("%d%d%d",&I,&J,&K);
            cout<<getans(I,J,K)<<endl;
        }
        else {
            scanf("%d%d",&I,&J);
            a.change(I,J);
        }
    }
    return 0;
}
