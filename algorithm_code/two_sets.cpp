#include <iostream>
#include <stdlib.h>
#include <math.h>
#include<algorithm>
#include<vector>
#define debug
using namespace std;

int a, b;
int total = 0;
struct node{
    int pos;
    int val;
    node(int p,int v){
        pos=p;
        val=v;
    }
};
int find(int *a, int key, int left, int right)
{
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (a[mid] == key)
        {
            return mid;
        }
        else if (a[mid] > key)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return -1;
}
int main(void)
{
    int n;
    int change = 0;
    scanf("%d", &n);
    scanf("%d", &a);
    scanf("%d", &b);
    int k;

    if (a > b)
    { //让a小b大
        change = 1;
        int temp = a;
        a = b;
        b = temp;
    }
    vector<node*> p1;
    int *res = new int[n](); //现在位置0123
    int *p = new int[n](); //现在位置0123
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &k);
        node *q = new node(i,k);
        p1.push_back(q);

        res[i] = -1;
    }
    sort(p1.begin(),p1.end(),[](const node * a, const node* b) -> bool { return a->val < b->val; });
    for(int i=0;i<n;i++){
        p[i]=p1[i]->val;
    }
    int flag = 1;
    for (int i = 0; total < (n + 1) / 2 && i < n; i++)
    {
        if (res[p1[i]->pos] != -1)
            continue;

        int y = n - 1;
        int resb = find(p, b - p[i], i, y);
        if (resb == -1 || (resb != -1 && res[p1[resb]->pos] != -1))
        {
            int resa = find(p, a - p[i], i, y);
            if (resa == -1)
            {
                flag = 0;
                break;
            }
            else if ( res[p1[resa]->pos] != -1)
            {
                flag = 0;
                break;
            }
            else
            {
                res[p1[i]->pos] = 0;
                res[p1[resa]->pos] = 0;
                total++;
            }
        }
        else
        {
            res[p1[i]->pos] = 1;
            res[p1[resb]->pos] = 1;
            total++;
        }
    }
    for(int i=0;i<n;i++){
        if(res[i]==-1){
            flag=0;
        }
    }
    if (flag == 0)
    {
        printf("0\n");
#ifdef debug
        system("pause");
        return 0;
#endif
    }
    else
    {
        printf("1\n");

        for (int i = 0; i < n; i++)
        {
            if (change)
            {
                if (i != n - 1)
                {
                    printf("%d ", 1 - res[i]);
                }
                else
                {
                    printf("%d", 1 - res[i]);
                }
            }
            else
            {
                if (i != n - 1)
                {
                    printf("%d ", res[i]);
                }
                else
                {
                    printf("%d", res[i]);
                }
            }
        }
    }

#ifdef debug
    system("pause");
#endif
    return 0;
}