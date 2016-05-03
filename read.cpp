#include<bits/stdc++.h>
using namespace std;
inline int read( )
{
    int x=0;
    char ch=getchar();
    while (ch<'0'||ch>'9') ch=getchar();
    x=0;
    while (ch<='9' && ch>='0')
    {
        x*=10,x+=ch-'0';
        ch=getchar();
    }
    return x;
}
int main(){
  int a,b;
  a=read();
  b=read();
  cout<<a+b<<endl;
  return 0;
}
