/*
��дcmp����ʱ��(a<b?1:0)��ʾ��������(a>b?1:0)��ʾ��������
.set����������Ϊ��data��������
.find�����ķ���ֵ��ʾҪ���ҵ�Ԫ��Ӧ�ñ������λ�õ�ǰһ��λ�á�
*/
#include<iostream>
#include<algorithm>
using namespace std;
int cmp(const int& a,const int& b){
    return (a>b?1:0);
}
template<class T,int num>
class findable{
    public:
        T data[num];
        void set(int n,int cmd(const T& a,const T& b)){
            sort(data,data+n,cmd);
        }
        int find(T x,int n){
            int i=0,j=n-1,mid;
            while (i<j){
                if (j-i==1) break;
                mid=(i+j)/2;
                if (!cmp(x,data[mid])) i=mid;
                else j=mid;
            }
            if ((!cmp(x,data[i]))&&cmp(x,data[j])) return i;
            if ((!cmp(x,data[j]))&&cmp(x,data[i])) return j;
            if ((!cmp(x,data[i]))&&(!cmp(x,data[j]))) return n-1;
            return -1;
        }
};
//����
/*
int main(){
    findable<int,20> a;
    int i;
    for (i=0;i<8;i++)
        cin>>a.data[i];
    a.set(8,cmp);
    cout<<a.find(6,8);
    return 0;
}
*/
