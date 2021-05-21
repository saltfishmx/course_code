#include <iostream>
#include <stdlib.h>
using namespace std;
int max(int a, int b)
{
    if (a < b)
        return b;
    else
        return a;
}
struct treenode
{
    int ldepth, rdepth;
    treenode *left, *right;
    treenode() : ldepth(0), left(NULL), right(NULL), rdepth(0){};
};
void func(treenode *root)
{
    if (root->left != NULL)
    {
        func(root->left);
        root->ldepth = max(root->left->ldepth, root->left->rdepth) + 1;
    }
    if (root->right != NULL)
    {
        func(root->right);
        root->rdepth = max(root->right->ldepth, root->right->rdepth) + 1;
    }
    return;
}
int main(void)
{
    int n;
    cin >> n;
    treenode *array = new treenode[n];
    int a, b;
    for (int i = 0; i < n; i++)
    {
        cin >> a >> b;
        if (a != -1)
        {
            array[i].left = &array[a];
        }

        if (b != -1)
        {
            array[i].right = &array[b];
        }
    }
    func(&array[0]);
    int m = 0;
    int pos = 0;
    for (int i = 0; i < n; i++)
    {
        if (array[i].ldepth + array[i].rdepth > m)
        {
            m = array[i].ldepth + array[i].rdepth;
            pos = i;
        }
    }
    int left = n - 1 - m;
    cout << m + left * 2;
    system("pause");
}