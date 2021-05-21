#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <stack>
using namespace std;

class node
{
public:
    int data;
    int bf;
    node *left, *right;
    node *bsl, *bsr;
    node()
    {
        left = NULL;
        right = NULL;
        bsl = NULL;
        bsr = NULL;
        bf = 0;
    }
};
void rotatel(node *&ptr)
{
    node *subl = ptr;
    ptr = subl->right;
    subl->right = ptr->left;
    ptr->left = subl;
    ptr->bf = subl->bf = 0;
}
void rotater(node *&ptr)
{
    node *subr = ptr;
    ptr = subr->left;
    subr->left = ptr->right;
    ptr->right = subr;
    ptr->bf = subr->bf = 0;
}
void rotatelr(node *&ptr)
{
    node *subr = ptr, *subl = subr->left;
    ptr = subl->right;
    subl->right = ptr->left;
    ptr->left = subl;
    if (ptr->bf <= 0)
        subl->bf = 0;
    else
        subl->bf = -1;
    subr->left = ptr->right;
    ptr->right = subr;
    if (ptr->bf == -1)
        subr->bf = 1;
    else
        subr->bf = 0;
    ptr->bf = 0;
}
void rotaterl(node *&ptr)
{
    node *subl = ptr, *subr = subl->right;
    ptr = subr->left;
    subr->left = ptr->right;
    ptr->right = subr;
    if (ptr->bf >= 0)
        subr->bf = 0;
    else
        subr->bf = 1;
    subl->right = ptr->left;
    ptr->left = subl;
    if (ptr->bf == 1)
        subl->bf = -1;
    else
        subl->bf = 0;
    ptr->bf = 0;
}
bool insert(node *&ptr, int &e1)
{
    node *pr = NULL, *p = ptr, *q;
    int d;
    stack<node *> st;
    while (p != NULL)
    {
        if (e1 == p->data)
            return false;
        pr = p;
        st.push(pr);
        if (e1 < p->data)
            p = p->left;
        else
            p = p->right;
    }
    p = new node;
    p->data = e1;
    if (pr == NULL)
    { //空树
        ptr = p;
        return true;
    }
    if (e1 < pr->data)
    {
        pr->left = p;
    }
    else
    {
        pr->right = p;
    }
    while (st.empty() == false)
    {
        pr = st.top();
        st.pop();
        if (p == pr->left)
            pr->bf--;
        else
            pr->bf++;
        if (pr->bf == 0)
            break;
        if (pr->bf == 1 || pr->bf == -1)
        {
            p = pr;
        }
        else
        {
            d = (pr->bf < 0) ? -1 : 1;
            if (p->bf == d)
            {
                if (d == -1)
                    rotater(pr);
                else
                    rotatel(pr);
            }
            else
            {
                if (d == -1)
                {
                    rotatelr(pr);
                }
                else
                    rotaterl(pr);
            }
            break;
        }
    }
    if (st.empty() == true)
        ptr = pr;
    else
    {
        q = st.top();
        if (q->data > pr->data)
        {
            q->left = pr;
        }
        else
            q->right = pr;
    }
    return true;
}
node *find(node *p, int target)
{
    if (p == NULL)
        return NULL;
    if (p->data == target)
    {
        return p;
    }
    else if (p->data < target)
    {
        return find(p->right, target);
    }
    else
    {
        return find(p->left, target);
    }
}
void find_ar_in_avl(node *p, int target, node *&p1)
{ //大于他的最小数

    if (p == NULL)
    {
        return;
    }
    if (p->data > target)
    {
        if (p1 == NULL)
        {
            p1 = p;
        }
        if (p->data < p1->data)
        {
            p1 = p;
        }
        find_ar_in_avl(p->left, target, p1);
    }
    else
    {
        find_ar_in_avl(p->right, target, p1);
    }
    return;
}
void find_al_in_avl(node *p, int target, node *&p1)
{ //小于他的最大数
    if (p == NULL)
    {
        return;
    }
    if (p->data < target)
    {
        if (p1 == NULL)
        {
            p1 = p;
        }
        if (p->data > p1->data)
        {
            p1 = p;
        }
        find_al_in_avl(p->right, target, p1);
    }
    else
    {
        find_al_in_avl(p->left, target, p1);
    }
    return;
}
void insertbst(node *p, node *pbst, node *target, node *al, node *ar)
{
    if (pbst == NULL)
        return;
    if (target->data > pbst->data)
    {
        if (pbst->bsr == NULL)
        {
            //cout<<pbst->data<<" ";
            printf("%d ", pbst->data);
            pbst->bsr = target;
        }
        else
        {

            if (al == NULL || al->bsr != NULL)
            {

                ar->bsl = target;
                printf("%d ", ar->data);
            }
            else
            {
                al->bsr = target;
                printf("%d ", al->data);
            }
        }
    }
    else
    { //小于
        if (pbst->bsl == NULL)
        {
            //cout<<pbst->data<<" ";
            printf("%d ", pbst->data);
            pbst->bsl = target;
        }
        else
        {

            if (al == NULL || al->bsr != NULL)
            {

                ar->bsl = target;
                printf("%d ", ar->data);
            }
            else
            {
                al->bsr = target;
                printf("%d ", al->data);
            }
        }
    }
}
int main(void)
{
    int n;
    scanf("%d", &n);
    int *a = new int[n]();
    node *p = NULL;
    node *bstroot;
    node *al, *ar;
    for (int i = 0; i < n; i++)
    {
        al = ar = NULL;
        scanf("%d", &a[i]);
        if (i != 0)
        {
            find_al_in_avl(p, a[i], al);
            find_ar_in_avl(p, a[i], ar);
        }
        insert(p, a[i]);
        if (i == 0)
        {
            bstroot = find(p, a[0]);
        }

        if (i != 0)
            insertbst(p, bstroot, find(p, a[i]), al, ar);
    }

    system("pause");
}