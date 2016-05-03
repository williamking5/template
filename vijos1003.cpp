#include<iostream>
#include<stdio.h>
#include<string.h>
#define P1 100007
#define P2 972997
using namespace std;
int i,j,n,ther;
int s[100],len,b[100],total,st[100],top;
long long cal(long long a,long long b,long long c,long long p){
	long long result;
	if (c==-3){
		result=1;
		for (int i=1;i<=b;i++){
			result=result*a%p;
			if (result<0) result+=p;
		}
	}
	else if (c==-4) {
		result=a*b%p;
		if (result<0) result+=p;
	}
	else if (c==-5) {
		result=(a+b)%p;
		if (result<0) result+=p;
	}
	else if (c==-6) {
		result=(a-b+p)%p;
		if (result<0) result+=p;
	}
	return result;
}
int getans(const char *tmp,int n,int a){
	int len=0,i=0,total=0,top=-1;

	while (i<n){
		if (tmp[i]==' '){
			i++;
			continue;
		}
		if (tmp[i]=='-') s[len++]=-6;
		else if (tmp[i]=='+') s[len++]=-5;
		else if (tmp[i]=='*') s[len++]=-4;
		else if (tmp[i]=='^') s[len++]=-3;
		else if (tmp[i]=='(') s[len++]=-2;
		else if (tmp[i]==')') s[len++]=-1;
		else if (tmp[i]=='a') s[len++]=a;
		else {
			int ans=0;
			while (tmp[i]>='0'&&tmp[i]<='9'){
				ans=ans*10+tmp[i]-'0';
				i++;
			}
			s[len++]=ans;
			continue;
		}
		i++;
	}

	for (i=0;i<len;i++){
		if (s[i]>=0){
			b[total++]=s[i];
		}
		else {
			if (s[i]==-1){
				while (st[top]!=-2){
					b[total++]=st[top--];
				}
				top--;
			}
			else if (s[i]==-2) st[++top]=s[i];
			else {
				if (top==-1){
					st[++top]=s[i];
				}
				else if (st[top]==-2) st[++top]=s[i];
				else {
					if (s[i]==-3) {
						while (st[top]==s[i]){
							if (st[top]==-2) break;
							if (top<0) break;
							b[total++]=st[top--];
						}
						st[++top]=s[i];
					}
					else if (s[i]==-4) {
						while (st[top]>=s[i]){
							if (st[top]==-2) break;
							b[total++]=st[top--];
							if (top<0) break;
						}
						st[++top]=s[i];
					}
					else if (s[i]==-5||s[i]==-6) {
						while (1){
							if (st[top]==-2) break;
							if (top<0) break;
							b[total++]=st[top--];
						}
						st[++top]=s[i];
					}
				}
			}
		}
	}

	for (i=top;i>=0;i--)
		b[total++]=st[i];

	top=-1;
	for (int i=0;i<total;i++){
		if (b[i]>0) st[++top]=b[i];
		else {
			int re=cal(st[top-1],st[top],b[i],P1);
			st[--top]=re;
		}
	}
	return st[0];
}
char stds[100],option[30][100];
int v[30];
int main(){
	fgets(stds,100,stdin);
	stds[strlen(stds)-1]=0;

	scanf("%d",&n);
	char tm[100];
	fgets(tm,100,stdin);
	for (i=0;i<n;i++){
		fgets(option[i],100,stdin);
		option[i][strlen(option[i])-1]=0;
	}

	int checknum[100]={17,97},ansnum[30],stdnum;
	
	for (int i=0;i<2;i++){
		stdnum=getans(stds,strlen(stds),checknum[i]);
		
		for (int j=0;j<n;j++){
			int kk=getans(option[j],strlen(option[j]),checknum[i]);
			if (kk!=stdnum) v[j]=1;
		}
	}

	for (int i=0;i<n;i++)
		if (!v[i]) printf("%c",i+'A');
	cout<<endl;
	return 0;
}
