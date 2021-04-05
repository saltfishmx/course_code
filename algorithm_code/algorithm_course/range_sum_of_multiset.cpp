#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#define INF 0x7FFFFFFF

using namespace std;
static long long lans = 0;
enum COLOR
{
    RED,
    BLACK
};

struct TreeNode
{
    long long key;
    TreeNode *parent;
    TreeNode *left, *right;
    COLOR color;
    long long sum;

    TreeNode &operator=(TreeNode &node) //Reload the "=" for assignment
    {
        this->key = node.key;
        this->parent = node.parent;
        this->left = node.left;
        this->right = node.right;
        this->color = node.color;
        return *this;
    }
};

TreeNode NULL_NODE = {INF, nullptr, nullptr, nullptr, BLACK, 0};

class Red_Black_Tree
{
public:
    TreeNode *root;

    TreeNode *NIL;

    void Left_Rotate(TreeNode *x);
    void Right_Rotate(TreeNode *x);

    //Insertion or deletion may cause red-black tree's quality destroyed
    //So we just try to fix it by this two options.
    void RB_Insert_FixUp(TreeNode *z);
    void RB_Delete_FixUp(TreeNode *z);

    void Transplant(TreeNode *u, TreeNode *v);

    TreeNode *Tree_Minimum(TreeNode *root);
    TreeNode *Tree_Maximum(TreeNode *root);

public:
    Red_Black_Tree()
    {
        size = 0;
        NIL = &NULL_NODE;
        root = &NULL_NODE;
    }

    void RBTree_Insert(long long _key);
    bool RBTree_Delete(long long _key);

    long long Preorder_Traversal(long long _key, TreeNode *root1);
    long long Preorder_Traversal_sum(long long l, long long r, TreeNode *root1);
    long long Preorder_Traversal_size();
    TreeNode *Find(long long _key);

public:
    long long size;
};
/**
 * Left rotate the subtree 
 * @param x : The root of the subtree to be rotated
 */
void Red_Black_Tree::Left_Rotate(TreeNode *x)
{
    if (x == NIL)
    {
        x = x->parent;
    }
    if (x->right == NIL)
        return;

    TreeNode *y = x->right; //Set y
    x->right = y->left;     //Turn y's left subtree long longo x's subtree

    if (y->left != NIL)
    {
        y->left->parent = x;
    }

    y->parent = x->parent; //Link x's parent to y

    if (x->parent == NIL)
    {
        root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }

    y->left = x; //Put x on y's left
    x->parent = y;
}
/**
 * Right rotate the subtree 
 * Symmetry with the function "Left Rotate" above.
 * @param x : The root of the subtree to be rotated
 */
void Red_Black_Tree::Right_Rotate(TreeNode *y)
{
    if (y == NIL)
    {
        y = y->parent;
    }
    if (y->left == NIL)
        return;

    TreeNode *x = y->left;
    y->left = x->right;

    if (x->right != nullptr)
    {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == NIL)
    {
        root = x;
    }
    else if (y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}
/**
 * Transplant the subtree u with the subtree v
 */
void Red_Black_Tree::Transplant(TreeNode *u, TreeNode *v)
{
    if (u->parent == NIL)
    {
        root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }

    v->parent = u->parent;
}
/**
 * Find a node whose key value equals to "_key"
 * @param  _key : The key value
 * @return      : If the node exists, return the node. Else, return the NULL_NODE.
 */
TreeNode *Red_Black_Tree::Find(/*TreeNode * root,*/ long long _key) //The circulation version of Search
{
    TreeNode *p = root;

    while (p != NIL && p->key != _key)
    {
        if (p->key > _key)
            p = p->left;
        else
            p = p->right;
    }
    return p;
}

//Get the minimum key in x's posterity and return the polong longer to that node
TreeNode *Red_Black_Tree::Tree_Minimum(TreeNode *root)
{
    TreeNode *p = root;

    while (p->left != NIL)
    {
        p = p->left;
    }
    return p;
}

//Get the maximum key in x's posterity and return the polong longer to that node
TreeNode *Red_Black_Tree::Tree_Maximum(TreeNode *root)
{
    TreeNode *p = root;

    while (p->right != NIL)
    {
        p = p->right;
    }
    return p;
}

long long Red_Black_Tree::Preorder_Traversal(long long _key, TreeNode *root1) //The circulation version of Preorder Traversal
{

    TreeNode *p = root1;
    long long count = 0;

    while (p != NIL)
    {
        if (p->key > _key)
        {

            p = p->left;
        }
        if (p->key < _key)
        {

            p = p->right;
        }
        if (p->key == _key)
        {
            count++;

            count += Preorder_Traversal(_key, p->left);
            count += Preorder_Traversal(_key, p->right);
            break;
        }
    }

    return count;
}
long long Red_Black_Tree::Preorder_Traversal_sum(long long l, long long r, TreeNode *root1) //The circulation version of Preorder Traversal
{

    TreeNode *p = root1;
    TreeNode *pr = root1;
    long long sum = 0;

    while (p != NIL)
    {

        if (p->key > l)
        {
            p = p->left;
        }
        else
        {
            break;
        }
    }
    while (pr != NIL)
    {

        if (pr->key <= r)
        {
            pr = pr->right;
        }
        else
        {
            break;
        }
    }
    if (pr->parent && p->parent)
    {
        if (pr->parent->key <= r && pr->parent->key > l && p->parent->key <= r && p->parent->key > l)
        {
            return root->sum - pr->sum - p->sum;
        }
    }
   if (pr->parent && !p->parent)
    {
        if (pr->parent->key <= r && pr->parent->key > l)
        {
            return root->sum - pr->sum;
        }
    }
     if (!pr->parent && p->parent)
    {
        if (p->parent->key <= r && p->parent->key > l)
        {
            return root->sum - p->sum;
        }
    }
    if (!pr->parent && !p->parent)
        return 0;
}
long long Red_Black_Tree::Preorder_Traversal_size(/*TreeNode * root */) //get size
{

    return size;
}
/**
 * Insert a new node long longo the RB-Tree
 * @param _key : the key value of the new node
 */
void Red_Black_Tree::RBTree_Insert(long long _key)
{
    size++;
    TreeNode *z = new TreeNode;
    z->key = _key;
    z->color = RED;
    z->left = z->right = NIL;
    z->sum = _key;

    TreeNode *y = NIL;
    TreeNode *x = root;

    while (x != NIL)
    {
        y = x;
        if (_key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NIL)
    {
        root = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    if (z->parent != NIL)
    {
        z->parent->sum += z->key;
    }

    RB_Insert_FixUp(z);
}
/**
 * Fix the double-red bug in this tree
 * @param z : a node which was just inserted
 */
void Red_Black_Tree::RB_Insert_FixUp(TreeNode *z)
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            TreeNode *y = z->parent->parent->right;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    Left_Rotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                Right_Rotate(z->parent->parent);
            }
        }
        else
        {
            TreeNode *y = z->parent->parent->left;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    Right_Rotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                Left_Rotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}
/**
 * Delete a node from the RB-Tree
 * @param  _key : The key value of the node which is to deleted
 * @return      : True for succeed, and false for no such node existed.
 */
bool Red_Black_Tree::RBTree_Delete(long long _key)
{
    TreeNode *z = Find(_key);
    if (z == NIL)
    {
        //cout<<"Error : No node valued "<<_key<<" !"<<endl;
        return false;
    }

    TreeNode *y = z;
    COLOR y_original_color = y->color;

    TreeNode *x;

    if (z->left == NIL)
    {
        x = z->right;
        Transplant(z, z->right);
    }
    else if (z->right == NIL)
    {
        x = z->left;
        Transplant(z, z->left);
    }
    else
    {
        y = Tree_Minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;

        y->color = z->color;
    }

    if (x == NIL)
    {
        x = x->parent;
    }
    y->parent = z->parent;

    if (x->left != NIL)
    {
        x->sum += x->left->sum;
    }
    if (x->right != NIL)
    {
        x->sum += x->right->sum;
    }

    if (y_original_color == BLACK)
        RB_Delete_FixUp(x);
    delete z;
    size--;
    return true;
}
/**
 * Delete a node may cause Black-Height changed, and this function is to fix this bug.
 * @param x : The place where the substitude node used to be
 */
void Red_Black_Tree::RB_Delete_FixUp(TreeNode *x)
{

    while (x != root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            TreeNode *w = x->parent->right;

            if (w->color == RED)
            {
                w->color = BLACK;
                w->parent->color = RED;
                Left_Rotate(x->parent);
                w = x->parent->right;
            }

            /***notice***/
            if (w->left == 0 && w->right == 0)
            {
                w->color = RED;
                x = x->parent;
            }

            else if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    Right_Rotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                Left_Rotate(x->parent);
                x = root;
            }
        }
        else
        {
            TreeNode *w = x->parent->left;

            if (w->color == RED)
            {
                w->color = BLACK;
                w->parent->color = RED;
                Left_Rotate(w);
                w = x->parent->left;
            }
            if (w->left == 0 && w->right == 0)
            {
                w->color = RED;
                x = x->parent;
            }
            else if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    Left_Rotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                Right_Rotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}
class solution
{
public:
    void func0(long long y)
    {
        long long x = (y + lans) % mod;
        RBTree.RBTree_Insert(x);
    }
    void func1(long long y)
    {
        long long x = (y + lans) % mod;
        long long count = 0;

        count = RBTree.Preorder_Traversal(x, RBTree.root);
        if (count >= 1)
        {
            RBTree.RBTree_Delete(x);
        }
        std::cout << count << std::endl;
        count--;
    }
    void func2(long long u, long long v)
    {
        long long l = (u + lans) % mod;
        long long r = (v + lans) % mod;
        if (l > r)
        {
            long long tmp = l;
            l = r;
            r = tmp;
        }
        long long sum = 0;
        sum = RBTree.Preorder_Traversal_sum(l, r, RBTree.root);

        std::cout << sum << std::endl;
        lans = sum;
    }

public:
    long long mod;
    Red_Black_Tree RBTree;
};
int main()
{
    solution a;

    long long Q;
    long long x, l, r;
    scanf("%d", &Q);
    scanf("%lld", &a.mod);
    int mode;
    for (long long i = 0; i < Q; i++)
    {
        scanf("%d", &mode);
        switch (mode)
        {
        case 0:
            scanf("%lld", &x);
            a.func0(x);
            break;
        case 1:
            scanf("%lld", &x);
            a.func1(x);
            break;
        case 2:
            scanf("%lld", &l);
            scanf("%lld", &r);
            a.func2(l, r);
            break;
        default:
            printf("error\n");
        }
    }
    system("pause");
    return 0;
}