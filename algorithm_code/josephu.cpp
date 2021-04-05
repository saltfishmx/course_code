#include <iostream>
#include <cstdlib>
using namespace std;
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
    /*
    bool isempty()
    {
        return first->rlink == first;
    }
    void sethead(dblnode *ptr)
    {
        first = ptr;
    }
    */
    dblnode *search(const int &x);
   
    dblnode *locate(int i, int d);
    bool insert(int i, int &x, int d);
    //bool remove(int i, int &x, int d);


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
/*
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
*/
dblnode *dblist::search(const int &x)
{
    //在带附加头节点的双向循环链表寻找值等于x的节点，若找到，返回节点地址，否则返回null
    dblnode *current = first;
    while ( current->data != x)
    {
        current = current->rlink;
    }
  
    return current;

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
/*
bool dblist::remove(int i,int &x,int d){
//x保存删去的节点的数据
    dblnode *current = locate(i,d);
    if(current==NULL)return false;
    current->rlink->llink=current->llink;
    current->llink->rlink=current->rlink;
    x=current->data;delete current;
    return true;
}
*/
void josephussmalltobig(dblist &js,int n,int m,int k){
    dblnode *p=js.search(k),*pre=p->llink;
    int i,j;
    for( i=0;i<n;i++){
        for(j=1;j<m;j++){
           
            pre=p;
            p=p->rlink;

        }
       if(i==n-1)
            cout<<p->data;
        else
            cout<<p->data<<" ";
        pre->rlink=p->rlink;
        delete p;
        p=pre->rlink;
    }

}
void josephusbigtosmall(dblist &js,int n,int m,int k){
    dblnode *p=js.search(k),*pre=p->rlink;
    int i,j;
    for( i=0;i<n;i++){
        for(j=1;j<m;j++){
       
            pre=p;
            p=p->llink;
   
        }
        if(i==n-1)
            cout<<p->data;
        else
            cout<<p->data<<" ";
        pre->llink=p->llink;
        delete p;
        p=pre->llink;
    }

}
int main(void)
{
//约瑟夫环定义如下：n个人，编号从1到n，n个人围成一个环，按照某种顺序依次报数。规定从编号为k的人开始报数，从1开始报数，
//假定从编号小的向编号大的方向报数，那么编号为k+1的人报数为2，依次类推，直到报数为m的人被选中，这个人从环里剔除；
//他的下一个人又从1开始报数，报数为m的那个人又被剔除；依此规律重复下去，直到所有人全部被剔除。根据所有人被剔除的顺序，输出所有人的编号。
//用双向循环链表实现约瑟夫环问题，并输出从编号小的向编号大的方向报数和从编号大的向编号小的方向的报数的结果。    
    int m, n, k;
    cin>>n>>m>>k;
    dblist clist1(1),clist2(1);
    for(int i=2;i<=n;i++){
        clist1.insert(i-2,i,1);
        clist2.insert(i-2,i,1);
    }
    josephussmalltobig(clist1,n,m,k);
    cout<<endl;
    josephusbigtosmall(clist2,n,m,k);

    return 0;
}