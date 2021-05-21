#include <iostream>
#include <stdlib.h>
#include <algorithm>
using namespace std;
class node
{
public:
    int val;
    node *left, *right;
    node()
    {
        left = NULL;
        right = NULL;
    }
};
node *construct(int &x, int n, int *a,int height)
{
    if (x == 2*n+1)
    {
        return NULL;
    }
    else
    {

        if (a[x] != -1)
        {
            node *p = new node;
            p->val = a[x++];
            if(height!=n){
                p->left = construct(x, n, a,height+1);
                p->right = construct(x, n, a,height+1);
            }

            return p;
        }
        else
        {
            x++;

            return NULL;
        }
    }
}
void midorder(int *b,int &n,node *p){
    if(p==NULL){
        return;
    }
    else{
        midorder(b,n,p->left);
        b[n++]=p->val;
        midorder(b,n,p->right);
    }
}
int main(void)
{
    int n;
    cin >> n;
    int *a = new int[2 * n + 1]();
    for (int i = 0; i < 2 * n + 1; i++)
    {
        cin >> a[i];
    }
    int x = 0;
    node *p = construct(x, n, a ,1);
    int *b=new int[2 * n + 1]();
    x=0;
    midorder(b,x,p);
    int *c=new int[x]();
    for(int i=0;i<x;i++){
        c[i]=b[i];
    }
    sort(c,c+x);
    for(int i=0;i<x;i++){
        if(c[i]!=b[i]){
            cout<<c[i]<<" ";
        }
    }
    system("pause");
}