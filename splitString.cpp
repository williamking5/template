#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <string>
#include <regex>
#include <stdlib.h>
#include <set>
#include <vector>
#include <map>
#include <queue>
#define LEN 5000
using namespace std;
int ne[LEN],ans[LEN];
char s[LEN],p[LEN],tmp[LEN];
vector<string> result;
void getnext(const char *p,int ne[]){
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
int kmp(const char *x,const char *y,int ne[],int ans[]){
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
	return sum+1;
}
vector<string> split(char* x, char* y){
	getnext(y,ne);
	int sum = kmp(x,y,ne,ans),len = strlen(x+1),m=strlen(y+1);
	vector<string> result;
	int i = 0,j = 0,start = 0;
	
	while (i<len&&j<sum){
		if (i==ans[j]) {
			if (i>start) {
				strncpy(tmp,x+start+1,i-start);
				tmp[i-start]=0;
				result.push_back(tmp);
			}
			i+=m;
			start = ans[j]+m;
			j++;
		}
		else i++;
	}

	if (len>start){
		strncpy(tmp,x+start+1,len-start);
		tmp[len-start]=0;
		result.push_back(tmp);
	}

	return result;
}
int main(){
	fgets(s+1,LEN,stdin);
	s[strlen(s+1)]=0;
	fgets(p+1,LEN,stdin);
	p[strlen(p+1)]=0;
	result = split(s,p);
	for (auto iter:result)
		cout<<iter<<endl;

	return 0;
}
