#include<iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
char s[60][60];
int a[60][60];
int SIZE[3000],num,pos[3000][2];
int bfs(int x,int y,int n,int m){
    int i,ans=0,flag=0;
    int q[3000][2];
    memset(q,0,sizeof q);
    int start=0,finish=0;
    q[start][0]=x;
    q[start][1]=y;
    a[x][y]=1;
    int tmp=finish;

    while (start<=finish){
        for (i=start;i<=finish;i++){
            if (q[i][0]==1||q[i][1]==1||q[i][0]==n||q[i][1]==m) flag=1;
            if (q[i][0]>1&&a[q[i][0]-1][q[i][1]]==0){
                tmp++;
                q[tmp][0]=q[i][0]-1;
                q[tmp][1]=q[i][1];
                a[q[i][0]-1][q[i][1]]=1;
            }
            if (q[i][0]<n&&a[q[i][0]+1][q[i][1]]==0){
                tmp++;
                q[tmp][0]=q[i][0]+1;
                q[tmp][1]=q[i][1];
                a[q[i][0]+1][q[i][1]]=1;
            }
            if (q[i][1]>1&&a[q[i][0]][q[i][1]-1]==0){
                tmp++;
                q[tmp][0]=q[i][0];
                q[tmp][1]=q[i][1]-1;
                a[q[i][0]][q[i][1]-1]=1;
            }
            if (q[i][1]<m&&a[q[i][0]][q[i][1]+1]==0){
                tmp++;
                q[tmp][0]=q[i][0];
                q[tmp][1]=q[i][1]+1;
                a[q[i][0]][q[i][1]+1]=1;
            }
        }
        start=finish+1;
        finish=tmp;
    }
    if (flag) return 0;
    else return finish+1;
}
void fillup(int x,int y,int n,int m){
    int i,ans=0,flag=0;
    int q[3000][2];
    memset(q,0,sizeof q);
    int start=0,finish=0;
    q[start][0]=x;
    q[start][1]=y;
    a[x][y]=1;
    s[x][y]='*';
    int tmp=finish;

    while (start<=finish){
        for (i=start;i<=finish;i++){
            if (q[i][0]==1||q[i][1]==1||q[i][0]==n||q[i][1]==m) flag=1;
            if (q[i][0]>1&&a[q[i][0]-1][q[i][1]]==0){
                tmp++;
                q[tmp][0]=q[i][0]-1;
                q[tmp][1]=q[i][1];
                a[q[i][0]-1][q[i][1]]=1;
                s[q[i][0]-1][q[i][1]]='*';
            }
            if (q[i][0]<n&&a[q[i][0]+1][q[i][1]]==0){
                tmp++;
                q[tmp][0]=q[i][0]+1;
                q[tmp][1]=q[i][1];
                a[q[i][0]+1][q[i][1]]=1;
                s[q[i][0]+1][q[i][1]]='*';
            }
            if (q[i][1]>1&&a[q[i][0]][q[i][1]-1]==0){
                tmp++;
                q[tmp][0]=q[i][0];
                q[tmp][1]=q[i][1]-1;
                a[q[i][0]][q[i][1]-1]=1;
                s[q[i][0]][q[i][1]-1]='*';
            }
            if (q[i][1]<m&&a[q[i][0]][q[i][1]+1]==0){
                tmp++;
                q[tmp][0]=q[i][0];
                q[tmp][1]=q[i][1]+1;
                a[q[i][0]][q[i][1]+1]=1;
                s[q[i][0]][q[i][1]+1]='*';
            }
        }
        start=finish+1;
        finish=tmp;
    }
}
int main(){
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    for (int i=1;i<=n;i++)
        scanf("%s",s[i]+1);

    memset(a,0,sizeof a);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            a[i][j]=s[i][j]=='*';

    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            if (a[i][j]==0){
                int ans=bfs(i,j,n,m);
                if (ans){
                    pos[num][0]=i;
                    pos[num][1]=j;
                    SIZE[num++]=ans;
                }
            }

    for (int i=0;i<num;i++){
        for (int j=i+1;j<num;j++)
            if (SIZE[j]<SIZE[i]){
                swap(SIZE[j],SIZE[i]);
                swap(pos[i][0],pos[j][0]);
                swap(pos[i][1],pos[j][1]);
            }
    }

    memset(a,0,sizeof a);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            a[i][j]=s[i][j]=='*';

    int ans=0;
    for (int i=0;i<num-k;i++){
        ans+=SIZE[i];
        fillup(pos[i][0],pos[i][1],n,m);
    }

    printf("%d\n",ans);
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++)
            printf("%c",s[i][j]);
        printf("\n");
    }
    return 0;
}
