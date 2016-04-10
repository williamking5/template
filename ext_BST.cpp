//可以自定义旋转调整的平衡树（以维护最小值为例）
#include<iostream>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define MAX 100000
using namespace __gnu_pbds;
using namespace std;
int H,MIN[MAX];
struct nodeclass{
	int a,HASH;
	nodeclass(int x,int y){a=x;HASH=y;}
	nodeclass(int x){a=x;HASH=++H;}
};
struct treecmp{
	bool operator()(const nodeclass& a,const nodeclass &b) const {
		return a.a<b.a||a.a==b.a&&a.HASH<b.HASH;
	}
};
template <class Node_CItr, class Node_Itr, class Cmp_Fn, class _Alloc>
struct my_node_update :public tree_order_statistics_node_update <Node_CItr,Node_Itr,Cmp_Fn,_Alloc>{
	virtual Node_CItr node_begin() const = 0;
	virtual Node_CItr node_end() const = 0;
    typedef int metadata_type;

	inline void operator()(Node_Itr it,Node_CItr end_it) const {
        Node_Itr l = it . get_l_child () , r = it . get_r_child ();
        int left = 0 , right = 0;
        if ( l != end_it ) left = l . get_metadata ();
        if ( r != end_it ) right = r . get_metadata ();
        const_cast < metadata_type & >( it . get_metadata ())= left + right + 1;

		left=10000000,right=10000000;
		if (l !=end_it) left = MIN[(*l)->HASH];
		if (r !=end_it) right= MIN[(*r)->HASH];
		MIN[(*it)->HASH]=(MIN[(*it)->HASH]>left?left:MIN[(*it)->HASH]);
		MIN[(*it)->HASH]=(MIN[(*it)->HASH]>right?right:MIN[(*it)->HASH]);
    }
};
typedef tree< nodeclass , null_type , treecmp , rb_tree_tag , my_node_update > SBT;
SBT::iterator Find(SBT &t,int x){
    int kk=t.order_of_key(nodeclass(x,0));
    cout<<kk<<endl;
    SBT::iterator iter=t.find_by_order(kk);
    return (iter->a==x?iter:t.end());
}
int main(){
	SBT bbt;
	SBT::iterator iter;

    for (int i=1;i<MAX;i++)
        MIN[i]=10;
	bbt.insert(1);
	bbt.insert(2);
	bbt.insert(2);
    bbt.insert(3);
	bbt.insert(4);
	bbt.insert(4);
	bbt.insert(4);

    cout<<bbt.order_of_key(nodeclass(10,0));
	return 0;
}
