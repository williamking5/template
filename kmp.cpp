#include<stdio.h>
#include<string.h>
#include<iostream>
#define LEN 100000
class kmpstring{
public:
	char s[LEN],p[LEN];
	int next[LEN];
	void getnext(char *p){
		next[0]=0;
		next[1]=0;
		int k=0;
		for (int q=2;q<=strlen(p+1);q++){
			while(k>0&&p[k+1]!=p[q])
				k=next[k];
			if (p[k+1]==p[q]) k++;
			next[q]=k;
		}
	}
	int kmp(char *x,char *y,int* ans){
		strcpy(s+1,x);
		strcpy(p+1,y);
		getnext(p);
		int sum=-1,i=0,j=0,n=strlen(s+1),m=strlen(p+1);
		while (i<=n&&j<=m){
			if (j==m) {
				ans[++sum]=i-j;
				j=next[j];
			}
			if (p[j+1]==s[i+1]){
				j++;i++;
			}
			else {
				if (!j) i++;
				else {
					j=next[j];
				}
			}
		}
		return sum;
	}
} test;
int main(){
	char s[100],p[100];
	scanf("%s%s",s,p);
	int ans[100];
	int sum=test.kmp(s,p,ans);
	for (int i=0;i<=sum;i++)
		cout<<ans[i]<<' ';
	return 0;
}
