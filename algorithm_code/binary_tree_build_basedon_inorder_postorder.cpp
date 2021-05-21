#include <iostream>
#include <stdlib.h>
#include <string>
#include<stack>
#include<queue>
using namespace std;
template <class T>
struct treenode{
    T data;
    treenode<T> *left,*right;
    treenode():left(NULL),right(NULL){};
    treenode(T x,treenode<T> *l=NULL,treenode<T>* r=NULL):data(x),left(l),right(r){}
};
template <class T>
treenode<T> *createbinarytree(T *reversed_postorder,T * inorder,int n){
    if(n==0){
        return NULL;
    }
    int k = n-1;
    int x=0;
    while(reversed_postorder[0]!=inorder[k-x])x++;
    treenode<T> *t=new treenode<T>(reversed_postorder[0]);
    t->right=createbinarytree(reversed_postorder+1,inorder+n-x,x);
    t->left=createbinarytree(reversed_postorder+x+1,inorder,n-x-1);
    return t;
}
template<class T>
void levelorder(treenode<T>* root){
    stack<treenode<T>*> stack1;
    stack<treenode<T>*> stack2;
    stack1.push(root);
    treenode<T> * p;
    int i=0;
    while(!stack1.empty()||!stack2.empty()){
        while(!stack1.empty()){
            p=stack1.top();
            cout<<p->data<<" ";
            stack1.pop();
            if(p->right!=NULL)stack2.push(p->right);
            if(p->left!=NULL)stack2.push(p->left);
        }
        while(!stack2.empty()){
            p=stack2.top();
            cout<<p->data<<" ";
            stack2.pop();
            if(p->left!=NULL)stack1.push(p->left);
            if(p->right!=NULL)stack1.push(p->right);            
        }

    }


}
int main(void){
    int N;
    cin>>N;
    int *a=new int[N]; //inorder
    int *b=new int[N];//postorder
    for(int i=0;i<N;i++){
        cin>>a[i];
    }
    for(int i=0;i<N;i++){
        cin>>b[N-1-i]; //reversed postorder
    }    
    treenode<int> *node=createbinarytree(b,a,N);
    levelorder(node);
    system("pause");
    return 0;
}
/*
题目描述
小蓝鲸来到了著名的二叉摸鱼海滩度假。二叉树摸鱼海滩是一个由小海域组成的度假滩，整个海滩是一个二叉树结构，每个小海域都代表一个二叉树结点，每个小海域都养一条鱼，假定给每个鱼一个编号。现在，小蓝鲸以“S型层次摸鱼”的方式一次把鱼都摸走。也就是说，从树顶根开始，逐级串起鱼，从左到右和从右到左交替。例如，对于下面的树，他串起的鱼序列是:1 11 5 8 17 12 20 15。现给出一棵二叉树的后序和中序遍历这个序列(一对给定的后序和中序遍历序列可以确定一个唯一的二叉树)，请求出小蓝鲸串起的鱼序列。



输入格式
第一行给出一个正整数N (<= 31)，即二叉树中的节点总数。

第二行给出了中序遍历的摸鱼序列。

第三行给出了后序遍历的摸鱼序列。
输入
8 
12 11 20 17 1 15 8 5   //inorder 
12 20 17 11 15 8 5 1          //reverse 1 5 8 15 11 17 20 12 
输出
1 11 5 8 17 12 20 15
*/