#include<iostream>
#include<stdio.h>
using namespace std;
long long a[100001],f[100001];
int main(){
	int i,j,n,r,h;
	cin>>n;
	for (i=0;i<n;i++){
		cin>>r>>h;
		a[i]=r*r*h;
	}
	for (i=0;i<n;i++){
		long long max=0;
		for (j=0;j<i;j++)
			if (a[j]<a[i]&&max<f[j]) max=f[j];
		f[i]=max+a[i];
	}

	long long max=0;
	for (i=0;i<n;i++)
		if (f[i]>max) max=f[i];
	printf("%.9lf\n",max*3.14159265358979);
	return 0;
}
