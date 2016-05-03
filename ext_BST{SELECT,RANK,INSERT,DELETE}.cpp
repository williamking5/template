#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
struct nodeclass{
    int first,second;
    nodeclass(int x){first=x;second=x;}
};
struct cmp{
    bool operator()(nodeclass a,nodeclass b) const {
        return a.first<b.first||a.first==b.first&&a.second<b.second;
    };
};
tree <nodeclass,null_type,cmp,rb_tree_tag,tree_order_statistics_node_update> a;
tree <nodeclass,null_type,cmp,rb_tree_tag,tree_order_statistics_node_update>::iterator iter;
int main(){
    srand(time(NULL));
    for (int i=0;i<100000;i++)
        a.insert(i);

    iter=a.find_by_order(5);
    cout<<iter->first<<endl;
    return 0;
}
