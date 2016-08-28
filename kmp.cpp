#include<stdio.h>
#include<string.h>
#include<iostream>
#define LEN 100000
using namespace std;
//将字符串p的next数组求出来存在ne数组中
void getnext(char *p,int ne[]){
	ne[0]=0;
	ne[1]=0;
	int k=0;

	int l=strlen(p+1);
	for (int q=2;q<=l;q++){
		while(k>0&&p[k+1]!=p[q])
			k=ne[k];
		if (p[k+1]==p[q]) k++;
		ne[q]=k;
	}
}
//x为模式串，y为子串，ne为y的next数组,ans为匹配位置数组
int kmp(char *x,char *y,int ne[],int ans[]){
	int sum=-1,i=0,j=0,n=strlen(x+1),m=strlen(y+1);
	while (i<=n&&j<=m){
		if (j==m) {
			ans[++sum]=i-j;
			j=ne[j];
		}
		if (y[j+1]==x[i+1]){
			j++;i++;
		}
		else {
			if (!j) i++;
			else {
				j=ne[j];
			}
		}
	}
	return sum;
}
int ne[LEN],ans[LEN];
char s[LEN],p[LEN];
int main(){
	scanf("%s%s",s+1,p+1);
	int ans[100];
	getnext(p,ne);
	int sum=kmp(s,p,ne,ans);

	for (int i=0;i<=sum;i++)
		cout<<ans[i]<<' ';
	return 0;
}

