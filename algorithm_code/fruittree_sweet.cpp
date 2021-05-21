#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <deque>

#include <vector>
using namespace std;
class node
{
public:
    float val;
    int num;
    node *left, *right, *parent;
    node()
    {
        val = 0;
        num = 1;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
};
deque<node *> s;
node *construct(int *a, int &x, int num)
{
    node *head = new node();
    node *p;
    if (a[0] == -1)
        return NULL;
    if (x < num)
    {

        head->val = a[x++];
        s.push_front(head);
    }
    while (x < num)
    {
        if (x < num)
        {
            p = s.front();
            s.pop_front();
            if (a[x] == -1)
            {
                p->left == NULL;
                x++;
            }
            else
            {
                node *p1 = new node();
                p1->val = a[x++];
                p->left = p1;
                p1->parent = p;
                s.push_back(p1);
            }
            
        }

        if (x < num)
        {
            if (a[x] == -1)
            {
                p->right == NULL;
                x++;
            }
            else
            {
                node *p2 = new node();
                p2->val = a[x++];
                p->right = p2;
                p2->parent = p;
                s.push_back(p2);
            }
        }
    }

    return head;
}
void handle(node *p){
    
    if(p==NULL){
        return;
    }
    handle(p->left);
    handle(p->right);
    if(p->left!=NULL){
        p->val += p->left->val;
        p->num += p->left->num;
    }
    if(p->right!=NULL){
        p->val += p->right->val;
        p->num += p->right->num;
    }    
}
void check(node *p,float &x){
    if(p==NULL){
        return;
    }
    if(p->val/p->num>x){
        x=p->val/p->num;
    }
    check(p->left,x);
    check(p->right,x);
}
int main(void)
{
    vector<float> a;
    float x;
    while (cin >> x)
    {
        if (getchar() == '\n')
        {
            break;
        }
        a.push_back(x);
    }
    int num = a.size();
    int q = 0;
    int *b = new int[num]();
    for (int i = 0; i < num; i++)
    {
        b[i] = a[i];
    }
    node *p = construct(b, q, num);
    handle(p);
    x=0;
    check(p,x);
    printf("%.5f",x);
    system("pause");
}