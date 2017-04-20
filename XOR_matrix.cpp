#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string.h>
#include <string>
#define P 1000000007
#define PINV 166666668
using namespace std;
long long squareSum(long long a, long long b){
	long long ans = b*(b+1)%P*(2*b+1)%P*PINV%P;
	long long tmp = (a-1)*a%P*(2*a-1)%P*PINV%P;
	ans = (ans-tmp)%P+P;
	ans%=P;
	return ans;
}
void show(int num){
	for (int i = 7;i>=0;i--){
		printf("%d", (num&(1<<i))!=0);
	}
	printf("\n");
}
long long solve(long long num1,int pos1,long long num2,int pos2){
	num1&=(~(1<<pos1));
	num2&=(~(1<<pos2));
	int pos = max(pos1,pos2);
	long long num = num1^num2;
	num = num>>pos<<pos;
	long long minnum = num , maxnum = (1<<pos)-1 + num;
	int minpos = min(pos1,pos2);
	long long ans = squareSum(minnum,maxnum);
	for (int i = 0;i<minpos;i++)
		ans = ans*2%P;
	return ans;
}
int main(){
	int t;
	scanf("%d",&t);
while (t--){
	long long n,m;
	cin>>n>>m;
	n++,m++;
	long long ans = 0;
	for (int i = 31;i>=0;i--){
		for (int j = 31;j>=0;j--){
			if ((n&(1<<i))&&(m&(1<<j))) {
				ans = ans + solve(n,i,m,j);
				ans%=P;
			}
		}		
	}

	cout<<ans<<endl;
}
	return 0;
}
