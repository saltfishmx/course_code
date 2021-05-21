#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <deque>

#include <stack>
using namespace std;
int flag = 0; //-1什么都不是，1大根，2小根
class node
{
public:
    int val;
    node *left, *right, *parent;
    node()
    {
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
            node *p1 = new node();
            p1->val = a[x++];
            p->left = p1;
            p1->parent = p;
            s.pop_front();
            s.push_back(p1);
        }

        if (x < num)
        {
            node *p2 = new node();
            p2->val = a[x++];
            p->right = p2;
            p2->parent = p;
            s.push_back(p2);
        }
    }

    return head;
}
void handle(node *p)
{
    int set = 1;
    int a;
    int b = -1;
    stack<int> s;
    while (p->parent != NULL)
    {
        s.push(p->val);
        p = p->parent;
    }
    s.push(p->val);
    while (!s.empty())
    {
        if (set)
        {
            set = 0;
        }
        else
        {
            b = a;
        }
        a = s.top(); //a在子树的位置
        if (b != -1)
        {
            if (flag == 0)
            {
                if (b > a)
                {
                    flag = 1;
                }
                if (b < a)
                {
                    flag = 2;
                }
            }
            if (flag == 1 && b < a)
            {
                flag = -1;
            }
            if (flag == 2 && b > a)
            {
                flag = -1;
            }
        }

        s.pop();
        if (s.empty())
        {
            cout << a;
            cout << endl;
        }
        else
        {
            cout << a << " ";
        }
    }
}
void postorder(node *p)
{
    if (p == NULL)
        return;
    else
    {

        postorder(p->right);
        postorder(p->left);
        if (p->left == NULL && p->right == NULL)
        {
            void(handle(p));
        }
    }
}
int main(void)
{

    int num;
    int x = 0;
    cin >> num;
    int *a = new int[num]();
    for (int i = 0; i < num; i++)
    {
        cin >> a[i];
    }
    node *p = construct(a, x, num);
    postorder(p);
    if (flag == 1)
        cout << "Max Heap";
    else if (flag == 2)
        cout << "Min Heap";
    else if (flag == -1)
        cout << "Not Heap";
    system("pause");
}