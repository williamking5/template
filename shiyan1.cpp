#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
struct sbt
{
	int left,right,size,data;
}tree[100000];
int top,root;
int n;
int opt;
int key;
void left_rot(int &x)
{
	int y=tree[x].right;
	tree[x].right=tree[y].left;
	tree[y].left=x;
	tree[y].size=tree[x].size;
	tree[x].size=tree[tree[x].left].size+tree[tree[x].right].size+1;
	x=y;
}
void right_rot(int &x)
{
	int y=tree[x].left;
	tree[x].left=tree[y].right;
	tree[y].right=x;
	tree[y].size=tree[x].size;
	tree[x].size=tree[tree[x].left].size+tree[tree[x].right].size+1;
	x=y;
}
void Maintain(int &x,bool flag)
{
	if (!flag)
	{
		if (tree[tree[tree[x].left].left].size>tree[tree[x].right].size)
		    right_rot(x);
		else
		if (tree[tree[tree[x].left].right].size>tree[tree[x].right].size)
		    left_rot(tree[x].left),right_rot(x);
		else
		return;
	}
	else
	{
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
void insert(int &x,int data)
{
	if (x==0)
	{
		x=++top;
		tree[x].size=1;
		tree[x].left=tree[x].right=0;
		tree[x].data=data;
	}
	else
	{
		tree[x].size++;
		if (data<tree[x].data) insert(tree[x].left,data);
		else insert(tree[x].right,data);
		Maintain(x,data>=tree[x].data);
	}
}
int remove(int &x,int data)
{
	tree[x].size--;
	if (data>tree[x].data)
	    remove(tree[x].right,data);
	else
	if (data<tree[x].data)
	    remove(tree[x].left,data);
	else
	{
		if (tree[x].left!=0&&tree[x].right==0)
		{
			int ret=x;
			x=tree[x].left;
			return x;
		}
		else
		if (tree[x].right!=0&&tree[x].left==0)
		{
			int ret=x;
			x=tree[x].right;
			return x;
		}
		else
		if (tree[x].left==0&&tree[x].right==0)
		{
			int ret=x;
			x=0;
			return ret;
		}
		else
		{
			int ret=tree[x].right;
			while (tree[ret].left) ret=tree[x].left;
			tree[x].data=tree[ret].data;
			remove(tree[x].right,tree[ret].data);
		}
	}
}
int select(int &x,int k)
{
	int r=tree[tree[x].left].size+1;
	if (k<r) return select(tree[x].left,k);
	else
	if (k>r) return select(tree[x].right,k-r);
	else
	return tree[x].data;
}
int rank(int &x,int data)
{
	if (x==0) return 0;
	if (data>tree[x].data) return tree[tree[x].left].size+1+rank(tree[x].right,data);
	else
	if (data<tree[x].data) return rank(tree[x].left,data);
	else
	return tree[tree[x].left].size+1;
}
int prev(int &x,int y,int data)
{
	if (x==0) return y;
	if (data>=tree[x].data) return prev(tree[x].right,x,data);
	else return prev(tree[x].left,y,data);
}
int succ(int &x,int y,int data)
{
	if (x==0) return y;
	if (data>=tree[x].data) return succ(tree[x].right,y,data);
	else return succ(tree[x].left,x,data);
}
int getmin()
{
	int x=root;
	while (tree[x].left) x=tree[x].left;
	return tree[x].data;
}
int getmax()
{
	int x=root;
	while (tree[x].right) x=tree[x].right;
	return tree[x].data;
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&opt);
		switch (opt)
		{
			case 1:
				scanf("%d",&key);
				insert(root,key);
				break;
			case 2:
				scanf("%d",&key);
				printf("%d\n",rank(root,key));
				break;
			case 3:
				scanf("%d",&key);
				printf("%d\n",select(root,key));
				break;
			case 4:
				printf("%d\n",getmax());
				break;
			case 5:
				printf("%d\n",getmin());
				break;
			case 6:
				scanf("%d",&key);
				printf("%d\n",succ(root,0,key));
				break;
			case 7:
				scanf("%d",&key);
				printf("%d\n",prev(root,0,key));
				break;
			case 8:
				scanf("%d",&key);
				remove(root,key);
		}
	}
}
