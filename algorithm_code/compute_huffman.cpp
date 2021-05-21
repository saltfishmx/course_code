#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;
class node{
public:    
    node *left,*right;
    int num;
    int height;

    node(){
        left=NULL;
        right=NULL;
        height=0;
        num=-1;
    }
};
void setheight(node *root){
    if(root==NULL)return;
    root->height++;
    setheight(root->left);
    setheight(root->right);
}  
int mi(int pos1,int *at,node *a,int len){
    int res=99999999;
    int pos=0;
    for(int i=0;i<len;i++){
        if(res>a[i].num&&i!=pos1&&at[i]!=1){
            res=a[i].num;
            pos=i;
        }
    }
    return pos;
}
int main(void){
    string s;
    cin>>s;
    int *a=new int[26]();
    for(int i=0;i<s.length();i++){
        if(s[i]!='\0')a[(s[i]-'A')]++;
    }
    int *b=new int[26]();
    int len=0;
    for(int i=0;i<26;i++){
        if(a[i]!=0){
            b[len++]=a[i];
        }
    }
    node *p=new node[len+len-1]();
    for(int i=0;i<len;i++){
        p[i].num=b[i];
    }
    int *at=new int[len+len-1]();
    int i=0;
    while(i<len-1){
        int x=mi(-1,at,p,len+i);
        int y=mi(x,at,p,len+i);
        p[len+i].num=p[x].num+p[y].num;
        p[len+i].left=&p[x];
        p[len+i].right=&p[y];
        at[x]=1;
        at[y]=1;
        setheight(&p[len+i]);
        i++;
    }
    int total=0;
    
    for(int i=0;i<len;i++){
        total+=p[i].num*p[i].height;
    }
    cout<<total;
    system("pause");

}