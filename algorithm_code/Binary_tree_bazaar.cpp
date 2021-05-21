#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
int people = 0;
class node
{
public:
    node *left, *right, *parent;
    node()
    {
        left = NULL;
        right = NULL;
    }
};
node *construct(int *a, int &x, int num)
{

    if (a[x] == -1)
        return NULL;
    else
    {
        node *p = new node;
        x++;
        if (x < num)
            p->left = construct(a, x, num);
        x++;
        if (x < num)
            p->right = construct(a, x, num);
        return p;
    }
}
int min(int x, int y)
{
    if (x < y)
        return x;
    else
        return y;
}
int max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}
int postorder(node *root)
{
    if (root == NULL)
        return 1;
    int x = postorder(root->left);
    int y = postorder(root->right);
    int res = min(x, y) + 1; //和人的距离
    if (max(x, y) == 2)
    {
        res = 0;
        people++;
    }
    return res;
}

int main(void)
{
    int *a = new int[1500];

    int x;
    int num = 0;
    while (cin >> x)
    {
        a[num++] = x;
        if (getchar() == '\n')
            break;
    }
    x = 0;
    node *p = construct(a, x, num);

    if (postorder(p) == 2) //根节点没有上层了
        people++;

    cout << people;
    system("pause");
}