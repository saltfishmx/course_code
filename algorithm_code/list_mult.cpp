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
    dblist clist1(666),clist2(666),clist3(666);
    int a,b;
    int i=0;
    while(cin>>a){
        
        clist1.insert(i,a,1);
        i++;
        if (getchar()=='\n')
            break;
    }


    int j=0;
    while(cin>>b){
        
        clist2.insert(j,b,1);
        j++;
        if (getchar()=='\n')
            break;        

    }

    int carry=0,sum=0;
    int k=1;
    while(k<=i){//默认测试样例第一个位数多一点
        sum=0;
        int all=k+1;
        int m=all-1;
        while(m>0&&all-m<=j){
            sum+=clist1.locate(m,1)->data*clist2.locate(all-m,1)->data;
            m--;
        }
        sum+=carry; 
        carry=sum%10;
		int x=sum-carry*10;
        clist3.insert(k-1,x,1);  
        k++;
        
    }
    if(carry>0)
        clist3.insert(k,carry,1);
    dblnode *current=clist3.first->llink;

    while(current->llink!=clist3.first){
        cout<<current->data;
        current=current->llink;
    }
    cout<<current->data;
    system("pause");
    return 0;
}