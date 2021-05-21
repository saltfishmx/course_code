#include <iostream>
#include <stdlib.h>
using namespace std;
int row,col;
int find(int x,int *b){
    while(b[x]>=0){
        x=b[x];
    }
    return x;
}
void u(int x,int y,int *b){
    int root1=find(x,b);
    int root2=find(y,b);
    if(root1==root2)return;
    b[root1]+=b[root2];
    b[root2]=root1;

}
int compute(int x,int y){
    return x*col+y;
}
int main(void){
    
    cin>>row>>col;
    int **a = new int *[row];
    int *b = new int [row*col]();
    for(int i=0;i<row;i++){
        a[i]=new int [col]();
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cin>>a[i][j];
            b[col*i+j]=-1;
        }
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(a[i][j]==1){
                if(i-1>=0&&a[i-1][j]==1){
                    u(compute(i,j),compute(i-1,j),b);
                }
                if(j-1>=0&&a[i][j-1]==1){
                    u(compute(i,j),compute(i,j-1),b);
                }    

            }
        }
    }
    int res=0;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(b[col*i+j]<0&&a[i][j]==1){res++;}
        }
    }
    cout<<res;
    system("pause");
}