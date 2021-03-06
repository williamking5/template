#include<bits/stdc++.h>
using namespace std;
const double PI = acos(-1.0);
struct Complex{
	double x,y;
	Complex (double xx=0.0,double yy=0.0){
		x=xx;
		y=yy;
	}
	Complex operator - (const Complex &b) const {
		return Complex(x-b.x,y-b.y);
	}
	Complex operator + (const Complex &b) const {
		return Complex(x+b.x,y+b.y);
	}
	Complex operator * (const Complex &b) const {
		return Complex(x*b.x-y*b.y,x*b.y+y*b.x);
	}
};
void change(Complex y[],int len){
    int i,j,k;
    for(i = 1, j = len/2;i < len-1; i++)
    {
        if(i < j)swap(y[i],y[j]);
        //交换互为小标反转的元素，i<j保证交换一次
        //i做正常的+1，j左反转类型的+1,始终保持i和j是反转的
        k = len/2;
        while( j >= k)
        {
            j -= k;
            k /= 2;
        }
        if(j < k) j += k;
    }
}
//将系数向量y转换成点阵，对应的x向量是由n个不同的n次单位根构成的
void fft(Complex y[],int len,int on){
	change(y,len);
	for (int h=2;h<=len;h<<=1){
		Complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
		for (int j=0;j<len;j+=h){
			Complex w(1,0);
			for (int k=j;k<j+h/2;k++){
				Complex u=y[k];
				Complex t=w*y[k+h/2];
				y[k]=u+t;
				y[k+h/2]=u-t;
				w=w*wn;
			}
		}
	}
	//如果on=-1则表示逆FFT
	if (on==-1)
		for (int i=0;i<len;i++)
			y[i].x/=len;
}
const int MAXN=200010;
Complex x1[MAXN],x2[MAXN];
char str1[MAXN/2],str2[MAXN/2];
int sum[MAXN];
int main(){
	while (scanf("%s%s",str1,str2)==2){
		int len1=strlen(str1);
		int len2=strlen(str2);
//注意，len必须严格大于(长度+1)*2，这是傅立叶变换所要求的
		int len=1;
		while (len<len1*2||len<len2*2) len<<=1;

        for(int i = 0;i < len1;i++)
            x1[i] = Complex(str1[len1-1-i]-'0',0);
        for(int i = len1;i < len;i++)
            x1[i] = Complex(0,0);
        for(int i = 0;i < len2;i++)
            x2[i] = Complex(str2[len2-1-i]-'0',0);
        for(int i = len2;i < len;i++)
            x2[i] = Complex(0,0);
//将两个系数向量进行FFT
		fft(x1,len,1);
		fft(x2,len,1);
//点乘
        for(int i = 0;i < len;i++)
            x1[i] = x1[i]*x2[i];
//将点向量转换成系数向量
        fft(x1,len,-1);
		for (int i=0;i<len;i++)
			sum[i]=(int) (x1[i].x+0.5);

		for (int i=0;i<len;i++){
			sum[i+1]+=sum[i]/10;
			sum[i]%=10;
		}
		len=len1+len2-1;
        while(sum[len] <= 0 && len > 0)len--;
		for (int i=len;i>=0;i--)
			printf("%c",sum[i]+'0');
		printf("\n");
	}
	return 0;
}
