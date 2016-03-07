#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
class acc{
	public:
		int sizea,*a,pointa,sizeb,*b,pointb,*c,pointc,sizec;
		int ac;
		acc(char *x,char *y,int length){
			ac=length;

			sizea=strlen(x);
			if (strstr(x,".")==NULL){
				x[sizea++]='.';
			pointa=sizea
			memset(a,0,sizeof a);
			
		}
};
int main(){
	char a[100],b[100];
	scanf("%s%s",a,b);
	acc x(a,b);
	return 0;
}
