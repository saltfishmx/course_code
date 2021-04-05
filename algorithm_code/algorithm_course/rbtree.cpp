#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>

using namespace std;

enum Color
{
    RED,
    BLACK
};

struct TreeNode
{
    Color color;
    long long key;
    TreeNode *left, *right, *p;

    TreeNode(long long _key = 0) : color(RED), key(_key), left(nullptr), right(nullptr), p(nullptr) {}
};

class RedBlackTree
{
public:
    RedBlackTree();                 //构造函数
    void rb_insert(long long key);        //插入
    long long inorder_tree_walk(long long l,long long r);       //中序遍历红黑树
    void rb_delete(long long key);        //删除结点
    TreeNode *tree_search(long long val); //元素搜索

    long long tree_count(long long val);

public:
    TreeNode *root;
    void rb_insert_fixup(TreeNode *z);      //插入修正
    void left_rotate(TreeNode *x);          //左旋
    void right_rotate(TreeNode *x);         //右旋
    long long inorder_tree_walk(TreeNode *node,long long l,long long r); //中序遍历红黑树
    void rb_transplant(TreeNode *u, TreeNode *v);
    void rb_delete_fixup(TreeNode *x); //删除修正
    TreeNode *tree_search(TreeNode *node, long long val);

    long long tree_count(TreeNode *node, long long val);
    TreeNode *tree_minimun(TreeNode *node); //最小元素
};

RedBlackTree::RedBlackTree() : root(nullptr) {}

void RedBlackTree::left_rotate(TreeNode *x)
{
    //左旋和右旋一共要改变6个指针的指向
    TreeNode *y = x->right;
    x->right = y->left;
    if (y->left)
        y->left->p = x;
    y->p = x->p;
    if (x->p == nullptr)
        root = y;
    else if (x->p->left == x)
        x->p->left = y;
    else
        x->p->right = y;
    y->left = x;
    x->p = y;
}

void RedBlackTree::right_rotate(TreeNode *x)
{
    TreeNode *y = x->left;
    x->left = y->right;
    if (y->right)
        y->right->p = x;
    y->p = x->p;
    if (x->p == nullptr)
        root = y;
    else if (x->p->left == x)
        x->p->left = y;
    else
        x->p->right = y;
    y->right = x;
    x->p = y;
}

void RedBlackTree::rb_insert(long long key)
{
    TreeNode *z = new TreeNode(key);
    TreeNode *y = nullptr;
    TreeNode *x = root;
    while (x)
    {
        y = x;
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->p = y;
    if (y == nullptr)
        root = z;
    else if (key < y->key)
        y->left = z;
    else
        y->right = z;
    rb_insert_fixup(z);
}

void RedBlackTree::rb_insert_fixup(TreeNode *z)
{
    while (z->p && z->p->color == RED)
    {
        if (z->p->p->left == z->p)
        {
            TreeNode *y = z->p->p->right;
            if (y && y->color == RED) //case 1
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if (z == z->p->right) //case 2
                {
                    z = z->p;
                    left_rotate(z);
                } //case 3
                z->p->color = BLACK;
                z->p->p->color = RED;
                right_rotate(z->p->p);
            }
        }
        else
        {
            TreeNode *y = z->p->p->left;
            if (y && y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if (z == z->p->left)
                {
                    z = z->p;
                    right_rotate(z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                left_rotate(z->p->p);
            }
        }
    }
    root->color = BLACK;
}

long long RedBlackTree::inorder_tree_walk(long long l,long long r)
{
    return inorder_tree_walk(root,l,r);
}

long long RedBlackTree::inorder_tree_walk(TreeNode *node,long long l,long long r)
{
	long long sum=0;
	while (node)
    {
        if (node->key > r)
        {
            node = node->left;
        }
        else if (node->key <= l)
        {
            node = node->right;
        }
        else if (node->key > l && node->key <= r)
        {
            sum += node->key;
            sum += inorder_tree_walk(node->left,l, r);
            sum += inorder_tree_walk(node->right,l, r);
            break;
        }
    }
	return sum;
}

void RedBlackTree::rb_delete(long long key)
{
    TreeNode *z = tree_search(key);
    TreeNode *x;
    if (z == nullptr)
    {

        return;
    }
    TreeNode *y = z;
    Color original_color = y->color;
    if (z->left == nullptr)
    {
        x = z->right;
        rb_transplant(z, z->right);
    }
    else if (z->right == nullptr)
    {
        x = z->left;
        rb_transplant(z, z->left);
    }
    else
    {
        y = tree_minimun(z->right);
        original_color = y->color;
        x = y->right;
        if (y->p == z)
        {
            if (x)
                x->p = y;
        }
        else
        {
            rb_transplant(y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        rb_transplant(z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }
    if (original_color == BLACK)
        rb_delete_fixup(x);
}

void RedBlackTree::rb_transplant(TreeNode *u, TreeNode *v)
{
    if (u->p == nullptr)
        root = v;
    else if (u == u->p->left)
        u->p->left = v;
    else
        u->p->right = v;
    if (v)
        v->p = u->p;
}

void RedBlackTree::rb_delete_fixup(TreeNode *x)
{
    if (x == nullptr)
        return;
    while (x != root && x->color == BLACK)
    {
        if (x == x->p->left)
        {
            TreeNode *w = x->p->right;
            if (w->color == RED) //case 1
            {
                w->color = BLACK;
                x->p->color = RED;
                left_rotate(x->p);
                w = x->p->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) //case 2
            {
                w->color = RED;
                x = x->p;
            }
            else
            {
                if (w->right->color == BLACK) //case 3
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(w);
                    w = x->p->right;
                }
                w->color = x->p->color; //case 4
                x->p->color = BLACK;
                w->right->color = BLACK;
                left_rotate(x->p);
                x = root;
            }
        }
        else
        {
            TreeNode *w = x->p->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                right_rotate(x->p);
                w = x->p->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->p;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                right_rotate(x->p);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

TreeNode *RedBlackTree::tree_search(long long val)
{
    return tree_search(root, val);
}

TreeNode *RedBlackTree::tree_search(TreeNode *node, long long val)
{
    if (!node || node->key == val)
        return node;
    if (val < node->key)
        return tree_search(node->left, val);
    else
        return tree_search(node->right, val);
}

long long RedBlackTree::tree_count(long long val)
{
    return tree_count(root, val);
}

long long RedBlackTree::tree_count(TreeNode *node, long long val)
{
    long long count = 0;
    if (!node)
        return 0;
    if (node->key == val)
    {
        count++;

    }
 
    count += tree_count(node->left, val);

    count += tree_count(node->right, val);
    return count;    
}

TreeNode *RedBlackTree::tree_minimun(TreeNode *node)
{
    TreeNode *temp = node;
    while (temp && temp->left)
        temp = temp->left;
    return temp;
}

static long long lans = 0;
class solution
{
public:
    void func0(long long y)
    {
        long long x = (y + lans) % mod;
        RBTree.rb_insert(x);
    }
    void func1(long long y)
    {
        long long x = (y + lans) % mod;
        long long count = 0;
        count = RBTree.tree_count(x);
        if (count >= 1)
        {
            RBTree.rb_delete(x);
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
        sum = RBTree.inorder_tree_walk(RBTree.root,l, r );

        std::cout << sum << std::endl;
        lans = sum;
    }

public:
    long long mod;
    RedBlackTree RBTree;
};
int main()
{
    solution a;

    long long Q;
    long long x, l, r;
    scanf("%lld", &Q);
    scanf("%lld", &a.mod);
    long long mode;
    for (long long i = 0; i < Q; i++)
    {
        scanf("%lld", &mode);
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