#include <iostream>
#include <stdlib.h>
#include <vector>
#include <deque>
//思路是判断无向图有没有长度为奇数的环
using namespace std;
int m;

int dfs(int h,int *visit,int **p){
    if(visit[h]==-1){
        visit[h]=0;
    }
    int len=p[h][0];
    for(int i=1;i<len+1;i++){
        int pos=p[h][i];
        if(visit[pos]!=-1){
            if(visit[pos]!=1-visit[h]){
                return 0;
                break;
            }
        }
        else{
            visit[pos]=1-visit[h];
            if(dfs(pos,visit,p)==0){
                return 0;
            }
        }
        

    }
    return 1;
}
int main(void){
    int n;
    cin>>n>>m;
    int x,y;
    int **p = new int *[n];
    int *visit = new int[n];
    deque<int> a;
    for(int i=0;i<n;i++){
        p[i]=new int[n+1]();
        visit[i]=-1;
    }

    for(int i=0;i<m;i++){
        cin>>x>>y;
        p[x][0]++;
        int len = p[x][0];
        p[x][len]=y;
        p[y][0]++;
        len = p[y][0];
        p[y][len]=x;
        
    }

    for(int i=0;i<n;i++){

        if(p[i][0]>1){
            a.push_back(i);
        }

    }
    int flag = 1;
    while(a.size()!=0){
        int len=a.size();
        for(int i=0;i<len;i++){
           
            int h = a[0];
            a.pop_front();
            flag = dfs(h,visit,p);
            if(flag==0)break;
        }
        if(flag==0)break;
    }
    if(flag){
        cout<<"Yes";
    }
    else{

        cout<<"No";
    }
    system("pause");

    return 0;
}