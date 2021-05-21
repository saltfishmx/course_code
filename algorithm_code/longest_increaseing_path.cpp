#include <iostream>
#include <stdlib.h>
using namespace std;
int row,col;
int **visit;
int compute(int **a,int x,int y){
    int max=1;
    if(visit[x][y])return visit[x][y];
    if(x-1>=0&&a[x][y]<a[x-1][y]){
        int c1=1+compute(a,x-1,y);
        if(max<c1){
            max=c1;
        }
    }
    if(x+1<row&&a[x][y]<a[x+1][y]){
        int c2=1+compute(a,x+1,y);
        if(max<c2){
            max=c2;
        }
    }    
    if(y-1>=0&&a[x][y]<a[x][y-1]){
        int c3=1+compute(a,x,y-1);
        if(max<c3){
            max=c3;
        }
    }    
    if(y+1<col&&a[x][y]<a[x][y+1]){
        int c4=1+compute(a,x,y+1);
        if(max<c4){
            max=c4;
        }
    } 
    visit[x][y]=max;
    return max;      
    
}
int main(void){
    
    cin>>row>>col;
    int **a = new int *[row];
    visit = new int *[row];
    for(int i=0;i<row;i++){
        a[i]=new int [col]();
        visit[i]=new int [col]();
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cin>>a[i][j];
        }
    }
    int max=0;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            int h=compute(a,i,j);
            if(max<h){
                max=h;
            }
        }
    }
    cout<<max;
    system("pause");
    return 0;

}