struct DATA{
/* 以int类型为例*/
    int x;
    DATA (int t){x=t;}
    DATA (){}
/* 该函数的作用是产生数学后继，在统计元素数目(SBT::Count)的时候需要使用*/
    DATA operator()(){
        return x+1;
    }
};
/* 下列比较函数中，只要更改<号即可，其他的不需要更改。*/
bool operator < (const DATA a,const DATA b){
    return a.x<b.x;
}
bool operator > (const DATA a,const DATA b){
    return b<a;
}
bool operator == (const DATA a,const DATA b){
    return !(a<b||a>b);
}
bool operator != (const DATA a,const DATA b){
    return (a<b||a>b);
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
struct sbt{
    int left,right,size;
    data_class data;
    sbt(){
        left=right=size=0;
    }
};
sbt tree[300000];
int top;
struct SBT{
public:
	int datacmp(const data_class a,const data_class b){
		if (a.data<b.data) return 1;
		if (a.data>b.data) return -1;
		return 0;
	}
	int root;
	//如果要维护父亲节点和儿子节点的其他域值则修改adapt
	void adapt(int x){
		tree[x].size=tree[tree[x].left].size+tree[tree[x].right].size+1;
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
	/*注意，这个remove是危险的，在删除之前必须使用Find检查元素的存在性*/
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
	data_class getmin(){
		int x=root;
		while (tree[x].left) x=tree[x].left;
		return tree[x].data;
	}
	data_class getmax(){
		int x=root;
		while (tree[x].right) x=tree[x].right;
		return tree[x].data;
	}
	//插入一个数
	void Insert(DATA data){
		insert(root,data_class(top+1,data));
	}
	//删除一个数，在相同的情况下，任意删除其中一个
	void Remove(DATA data){
		remove(0,root,data_class(0,data));
	}
	//查询第k小的数字
	DATA Select(int k){
		return select(root,k).data;
	}
	//查询比data小（严格）的数字有多少个
	int Rank(DATA data){
		return rank(root,data_class(-1,data));
	}
	//查找data是否存在
	bool Find(DATA data){
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
	int Count(DATA data){
		bool exi=Find(data);
		if (exi){
			int aaa=Rank(data);
			int bbb=Rank(data());
			return bbb-aaa;
		}
		else return 0;
	}
	//查询最大值
	DATA Getmax(){
		return getmax().data;
	}
	//查询最小值
	DATA Getmin(){
		return getmin().data;
	}
};
SBT a;
int main(){
    a.Insert(1);
    a.Insert(4);
    a.Insert(5);
    a.Insert(1);
    a.Insert(4);
    a.Insert(5);
    a.Insert(1);
    a.Insert(1);
    //删除所有的4
    while (a.Find(4))
        a.Remove(4);
}
