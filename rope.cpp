#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <set>
#include <vector>
#include <map>
#include <ext/rope>
#define maxn 2000010
using namespace std;
using namespace __gnu_cxx;
crope a,b,tmp;
char ope[20],s[maxn];
void show(crope * x){
    int len = x->length();
    for (int i =0;i<len;i++)
        putchar(x->at(i));
    putchar('\n');
}
int main(){
    int n,k,x,m;
    int pos = 0;
    scanf("%d",&n);
    fgets(ope,2,stdin);
    for (int i = 0;i<n;i++){
        scanf("%s",ope);
        if (ope[0] == 'I'){
            scanf("%d",&m);
            fgets(s,2,stdin);
            fgets(s,m+1,stdin);
            s[m] = 0;
            a.insert(pos,s);
            for (int j = 0;2*j<m-1;j++)
                swap(s[j],s[m-1-j]);
            b.insert(b.length()-pos,s);
        }
        else if (ope[0] == 'M'){
            scanf("%d",&k);
            pos = k;
        }
        else if (ope[0] == 'P'){
            pos--;
        }
        else if (ope[0] == 'N'){
            pos++;
        }
        else if (ope[0] == 'G'){
            putchar(a[pos]);putchar('\n');
        }
        else if (ope[0] == 'D'){
            scanf("%d",&k);
            a.erase(pos,k);
            b.erase(b.length()-pos-k,k);
        }
        else if (ope[0] == 'R'){
            scanf("%d",&k);
            tmp = a.substr(pos,k);
            a = a.substr(0,pos)+b.substr(b.length()-pos-k,k)+a.substr(pos+k,a.length()-pos-k);
            b = b.substr(0,b.length()-pos-k)+tmp+b.substr(b.length()-pos,pos);
        }
    }
    return 0;
}
