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
#define SIZE 60
using namespace std;
bool A[1010][SIZE];
bool vis[1010];
void show(bool A[][SIZE],int n,int m){
	for (int i = 0;i<n;i++){
		for (int j = 0;j<m;j++)
			printf("%d ", A[i][j]);
		printf("\n");
	}
	printf("\n");
}
int Gauss(bool A[][SIZE],int n,int m){
	for (int i = 0;i<m-1;i++){
		int baseLine;
		for (baseLine = 0;baseLine<n; baseLine++)
			if (A[baseLine][i] == 1 && vis[baseLine] ==0 ) break;
		if (baseLine>=n) continue;
		vis[baseLine] = 1;
		for (int j = 0;j<n;j++){
			if (j!=baseLine && A[j][i]) {
				for (int k = 0;k<m;k++)
					A[j][k]^=A[baseLine][k];
			}
		}
	}

	int ans = 0;
	for (int i = 0;i<m-1;i++){
		bool sum = 0;
		for (int j = 0;j<n;j++){
			if (A[j][i] == 1) {
				if (sum == 0) sum=1;
				else {
					ans++;
					break;
				}
			}
		}
	}
	
	for (int i = 0;i<n;i++){
		bool tmp = 0;
		for (int j = 0;j<m-1;j++)
			if (A[i][j]) {tmp=1;break;}
		if (tmp) continue;
		if (A[i][m-1]) return -1;
	}
	return ans;
}
int main(){
	int x,n = 4,m = 4;
	for (int i = 0;i<n;i++)
		for (int j = 0;j<m;j++)
			scanf("%d",&x),A[i][j] = x;
	cout<<Gauss(A,n,m)<<endl;
	return 0;
}
/*
1 1 1 0
0 0 1 1
0 1 0 1
1 0 0 1
*/
