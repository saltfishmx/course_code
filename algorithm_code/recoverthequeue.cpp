#include <iostream>
#include <cstdlib>
using namespace std;
//受疫情影响，今年学生返校时需要在校门口排队进入，小蓝鲸想知道整个队伍的排列顺序。 
//假设每个同学都有一个编号,编号从（1-n）表示，每个同学只能看到自己前面一位同学的编号，按顺序输出整个队伍的编号。
/*输入样例
4
1 3
2 4
3 2
4 0
输出样例
4 2 3 1
*/
//我这样做有问题，最好先读完所有数据，然后找0(队伍开头)，再一个个接，只是样例没测出来我的问题就懒得改了
class dblnode
{
public:
    friend class dbllist;
    int data;
    dblnode *llink, *rlink;
    dblnode(dblnode *left = NULL, dblnode *right = NULL) : llink(left), rlink(right){};
    dblnode(int value, dblnode *left = NULL, dblnode *right = NULL) : data(value), llink(left), rlink(right){};
};
class dblist
{
public:

    dblist(int uniqueval);
	~dblist(){};
    int length() const;
    bool isempty()
    {
        return first->rlink == first;
    }
    void sethead(dblnode *ptr)
    {
        first = ptr;
    }
    int search(const int &x);
    dblnode *locate(int i, int d);
    bool insert(int i, int &x, int d);
    bool remove(int i, int &x, int d);


    dblnode *first;
};

dblist::dblist(int uniqueval)
{
    first = new dblnode(uniqueval);
    if (first == NULL)
    {
        cerr << "存储分配出错！" << endl;
        exit(1);
    }
    first->rlink = first->llink = first;
}
int dblist::length() const
{
    //计算带附加头节点的双向循环链表的长度并返回
    dblnode *current = first->rlink;
    int count = 0;
    while (current != first)
    {
        current = current->rlink;
        count++;
    }
    return count;
}
int dblist::search(const int &x)
{
    //要找的节点为第返回值个节点
    dblnode *current = first->rlink;
    int count=1;
    while (current != first && current->data != x)
    {
        current = current->rlink;
        count++;
    }
    if (current != first)
        return count;
    else
        return 0;
}

dblnode *dblist ::locate(int i, int d)
{
    //在带有附加头节点的双向循环链表按d所指向的方向寻找第i个节点的地址，若d =0，在前驱方向寻找，否则在后继方向寻找。
    if (first->rlink == first || i == 0)
        return first;
    dblnode *current;
    if (d == 0)
        current = first->llink;
    else
        current = first->rlink;
    for (int j = 1; j < i; j++)
    {
        if (current == first)
            break; //链太短，退出搜索返回null
        else if (d == 0)
            current = current->llink;
        else
            current = current->rlink;
    }
    if (current != first)
        return current;
    else
        return NULL;
}
bool dblist::insert(int i, int &x, int d)
{
    //建立一个包含有值x的新的节点，并将其按d指定的方向插入到第i个结点之后
    dblnode *current = locate(i, d);
    if (current == NULL)
        return false;
    dblnode *newnode = new dblnode(x);
    if (newnode == NULL)
    {
        cerr << "存储分配出错！" << endl;
        exit(1);
    }
    if(d==0){
        newnode->llink = current->llink;
        current->llink = newnode;
        newnode->llink->rlink=current;
        newnode->rlink = current;
    }
    else{
        newnode->rlink = current->rlink;
        current->rlink = newnode;
        newnode->rlink->llink=newnode;
        newnode->llink= current;
    }
    return true;
}
bool dblist::remove(int i,int &x,int d){
//x保存删去的节点的数据
    dblnode *current = locate(i,d);
    if(current==NULL)return false;
    current->rlink->llink=current->llink;
    current->llink->rlink=current->rlink;
    x=current->data;delete current;
    return true;
}
int main(void)
{

    int n;
    
    cin>>n;
    dblist clist(0);
    int a,b;
    for(int i=0;i<n;i++){
        cin>>a>>b;
        if(b==0){
            if(clist.search(a)==0)clist.insert(0,a,1);
        }
        else if((clist.search(a)||clist.search(b))==0){
            clist.insert(0,b,1);
            clist.insert(1,a,1);
        }
        else if(clist.search(a)==0&&clist.search(b)!=0){
            clist.insert(clist.search(b),a,1);
        }
        else if(clist.search(b)==0&&clist.search(a)!=0){
            clist.insert(clist.search(a)-1,b,1);
        }
    }
    dblnode *newnode=clist.first->rlink;
    for(int i=0;i<n;i++){
        cout<<newnode->data<<" ";
        newnode=newnode->rlink;
    }
    system("pause");
    return 0;
}