/*
Node类是专门为SBT类设计的节点类型，其成员变量包括left,right,father,Size,data分别代表该节点的左右父节点以及Size域。
	data是Node类中用来记录节点数据的变量，其类型应该实际需要重写。

SBT类是一棵封装的节点平衡二叉树，其节点的存储采用的是数组实现，因此需要指出其最多节点大小。
    SBT::cmp函数是比较data变量的优先级的函数，用于确定平衡树的优先类型。cmp(左子树节点，根节点)=1。
    *其参数类型应该根据需要重写*
	SBT::Clear()函数用于清空当前所有的节点信息，即全部归0。
	SBT::RightRotation(int i)函数用于右旋编号为i的节点以及i的左子节点。
	*如果要维护某节点的其他域，则应该根据实际需要重写右旋*
	SBT::LeftRotation(int i)函数用于左旋编号为i的节点以及i的右子节点。
	*如果要维护某节点的其他域，则应该根据实际需要重写左旋*
	SBT::Maintain(int t,bool flag)函数用于维护SBT的平衡属性。
	SBT::Insert(Node x)函数用于向平衡树中插入一个Node类型的数据x。
	*如果要维护某节点的其他域，则应该重写Insertx(Node x,int t,int f)底层*
	SBT::Find(Node x)函数用于查找平衡树中一个data域与x相同的节点并返回其编号。如果返回值为0说明没有找到这样的节点。
	SBT::pre(int t)函数查找一个编号为t的节点的前驱节点。如果返回0说明没有找到，否则返回该节点编号
	SBT::suc(int t)函数查找一个编号为t的节点的后继节点。如果返回0说明没有找到，否则返回该节点编号
	SBT::Delete(Node x)函数删除一个与x的data域相同的节点，如果没有找到这样的节点，返回0，否则删除并返回1。
	*如果要维护某节点的其他域，应该重写Delete函数*
	SBT::show()函数用于输出这棵平衡树的所有节点信息，按照从根节点开始的中序遍历输出。
*/
class Node{
    public:
        int data;
        int left,right,father,Size;
};
class SBT{
    public:
        Node* node;
		int Size,root;
        SBT(int n){
            node=new Node[n+1];
			Size=root=0;
            for (int i=0;i<=n;i++){
                node[i].left=node[i].right=node[i].father=0;
                node[i].Size=0;
            }
        }
		int cmp(Node x,Node y){
			if (x.data<=y.data) return 1;
			else return 0;
		}
        void Clear(){
            for (int i=0;i<=Size;i++){
                node[i].left=node[i].right=node[i].father=0;
                node[i].Size=0;
            }
            Size=root=0;
        }
        bool RightRotation(int i){
            if (!i) return 0;
            int LEFT=node[i].left,FATHER=node[i].father;
            if (!LEFT) return 0;
            int RIGHT=node[LEFT].right;

            node[i].father=LEFT;
            node[i].left=RIGHT;
            node[LEFT].father=FATHER;
            node[LEFT].right=i;
            if (FATHER)
                if (node[FATHER].left==i) node[FATHER].left=LEFT;
                else node[FATHER].right=LEFT;
            if (RIGHT) node[RIGHT].father=i;
            node[i].Size=node[node[i].left].Size+node[node[i].right].Size+1;
            node[LEFT].Size=node[node[LEFT].left].Size+node[node[LEFT].right].Size+1;
            if (!node[LEFT].father) root=LEFT;
        }
        bool LeftRotation(int i){
            if (!i) return 0;
            int RIGHT=node[i].right,FATHER=node[i].father;
            if (!RIGHT) return 0;
            int LEFT=node[RIGHT].left;

            node[i].father=RIGHT;
            node[i].right=LEFT;
            node[RIGHT].father=FATHER;
            node[RIGHT].left=i;
            if (FATHER)
                if (node[FATHER].left==i) node[FATHER].left=RIGHT;
                else node[FATHER].right=RIGHT;
            if (LEFT) node[LEFT].father=i;
            node[i].Size=node[node[i].left].Size+node[node[i].right].Size+1;
            node[RIGHT].Size=node[node[RIGHT].left].Size+node[node[RIGHT].right].Size+1;
            if (!node[RIGHT].father) root=RIGHT;
        }
        bool Maintain(int t,bool flag){
            if (!t) return 0;
			if (!flag){
                if (node[node[node[t].left].left].Size>node[node[t].right].Size) RightRotation(t);
                else if (node[node[node[t].left].right].Size>node[node[t].right].Size) {
                    LeftRotation(node[t].left);
                    RightRotation(t);
                }
                else return 0;
            }
            else{
                if (node[node[node[t].right].right].Size>node[node[t].left].Size) LeftRotation(t);
                else if (node[node[node[t].right].left].Size>node[node[t].left].Size) {
                    RightRotation(node[t].right);
                    LeftRotation(t);
                }
                else return 0;
            }

            Maintain(node[t].left,false);
            Maintain(node[t].right,true);
            Maintain(t,false);
            Maintain(t,true);
        }
		void SimpleInsert(Node x,int t,int f){
			if (!t){
				node[++Size].data=x.data;
				node[Size].Size=1;
				node[Size].father=f;
				if (f){
					if (cmp(x,node[f])) node[f].left=Size;
					else node[f].right=Size;
				}
			}
			else {
				node[t].Size++;
				if (cmp(x,node[t])) SimpleInsert(x,node[t].left,t);
				else SimpleInsert(x,node[t].right,t);
			}
		}
		void Insertx(Node x,int t,int f){
            if (!root) root=Size+1;
            if (!t){
                node[++Size].data=x.data;
                node[Size].Size=1;
                node[Size].father=f;
                if (f){
                    if (cmp(x,node[f])) node[f].left=Size;
                    else node[f].right=Size;
                }
            }
            else{
                node[t].Size++;
                if (cmp(x,node[t])) SimpleInsert(x,node[t].left,t);
                else SimpleInsert(x,node[t].right,t);
                Maintain(t,(!cmp(x,node[t])));
            }
		}
		void Insert(Node x){
            Insertx(x,root,0);
		}
		int Findx(Node x,int tt){
            int t=tt;
            while (t){
                if (x.data==node[t].data) return t;
                else{
                    if (cmp(x,node[t])) t=node[t].left;
                    else t=node[t].right;
                }
            }
            return t;
		}
		int Find(Node x){
            return Findx(x,root);
		}
		int pre(int tt){
            int t=node[tt].left;
            while (node[t].right)
                t=node[t].right;
            return t;
		}
		int suc(int tt){
            int t=node[tt].right;
            while (node[t].left)
                t=node[t].left;
            return t;
		}
		int Delete(Node x){
			int v=Findx(x,root);
			if (!v) return 0;
			if (node[v].Size==1){
				int FA=node[v].father,ROOT=v;
				//删除后更新根节点
				while (node[ROOT].father!=0) ROOT=node[ROOT].father;
				if (ROOT==v) root=0;
				else root=ROOT;

				if (node[FA].left==v) node[FA].left=0;
				else node[FA].right=0;
				while (FA) {
					node[FA].Size--;
					FA=node[FA].father;
				}
				return 1;
			}
			if (!node[v].left){
				node[node[v].right].father=node[v].father;
				int FA=node[v].father,ROOT=node[v].right;

				if (FA){
					if (node[FA].left==v) node[FA].left=node[v].right;
					else node[FA].right=node[v].right;
				}
				while (FA){
					node[FA].Size--;
					FA=node[FA].father;
				}
                //删除后更新根结点
				while (node[ROOT].father!=0) ROOT=node[ROOT].father;
				root=ROOT;
				return 1;
			}
			int PRE=pre(v);
			node[v].data=node[PRE].data;
			if (node[PRE].Size==1) {
				int FA=node[PRE].father;
				if (node[FA].left==PRE) node[FA].left=0;
				else node[FA].right=0;
				while (FA){
					node[FA].Size--;
					FA=node[FA].father;
				}
			}
			else {
				int FA=node[PRE].father,LEFT=node[PRE].left;
				node[LEFT].father=FA;
				if (node[FA].left==PRE) node[FA].left=LEFT;
				else node[FA].right=LEFT;
				while (FA){
					node[FA].Size--;
					FA=node[FA].father;
				}
			}
			Maintain(v,true);
			return 1;
		}
        void showx(int i){
            if (!i) return ;
            cout<<i<<'\t'<<"["<<node[i].data<<"]"<<'\t'<<node[i].father<<'\t'<<node[i].left<<'\t'<<node[i].right<<endl;
            showx(node[i].left);
            showx(node[i].right);
        }
        void show(){
            cout<<"Number"<<'\t'<<"[Data]"<<'\t'<<"Father"<<'\t'<<"Left"<<'\t'<<"Right"<<endl;
            showx(root);
        }
};
