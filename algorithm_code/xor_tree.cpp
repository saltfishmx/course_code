#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stack>
using namespace std;

int check(int *init, int *goal, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (goal[i] != init[i])
        {
            return i;
        }
    }
    return -1;
}

struct treenode
{
    int data;
    vector<int> array1; //就是用下动态数组的功能，不然一下子开一个大数组空间太大了
    treenode() : data(0){};
};
void reverse(int *init, treenode *array, int i)
{
    stack<int> s;
    s.push(i);
    int p;
    while (!s.empty())
    {
        p = s.top();
        init[p] ^= 1;
        s.pop();
        for (int i = 0; i < array[p].array1.size(); i++)
        {
            for (int j = 0; j < array[array[p].array1[i]].array1.size(); j++)
            {
                s.push(array[array[p].array1[i]].array1[j]);
            }
        }
    }
}
int main(void)
{
    int n;
    cin >> n;
    treenode *array = new treenode[n];
    array[0].data = 1;
    int a, b;
    int rest = 0;

    int *ra = new int[n];
    int *rb = new int[n];
    for (int i = 0; i < n - 1; i++)
    {
        cin >> a >> b;
        a--;
        b--;
        if (array[a].data == 0 && array[b].data != 0)
        {
            array[a].data = array[b].data + 1;
            array[b].array1.push_back(a);
        }
        else if (array[b].data == 0 && array[a].data != 0)
        {
            array[b].data = array[a].data + 1;
            array[a].array1.push_back(b);
        }
        else
        {
            ra[rest] = a;
            rb[rest] = b;
            rest++;
        }
    }
    int flag = 1;
    while (flag)
    {
        flag = 0;
        for (int i = 0; i < rest; i++)
        {
            if (array[ra[i]].data == 0 && array[rb[i]].data != 0)
            {
                array[ra[i]].data = array[rb[i]].data + 1;
                array[rb[i]].array1.push_back(ra[i]);
                flag = 1;
            }
            else if (array[rb[i]].data == 0 && array[ra[i]].data != 0)
            {
                array[rb[i]].data = array[ra[i]].data + 1;
                array[ra[i]].array1.push_back(rb[i]);
                flag = 1;
            }
        }
    }

    int *init = new int[n]();
    int *goal = new int[n]();
    for (int i = 0; i < n; i++)
    {
        cin >> init[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> goal[i];
    }
    int *pos = new int[n]();
    int num = 0;
    int min = n;
    int x = check(init, goal, n);
    while (x != -1)
    {
        min = min + 1;
        for (int i = x; i < n; i++)
        {
            if (init[i] != goal[i])
            {
                if (array[i].data < min)
                {
                    min = array[i].data;
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (init[i] != goal[i] && array[i].data == min)
            {
                reverse(init, array, i);
                pos[num++] = i + 1;
            }
        }
        x = check(init, goal, n);
    }
    cout << num << endl;
    int *result = new int[n + 1];
    for (int i = 0; i < n + 1; i++)
    {
        result[i] = -1;
    }
    for (int i = 0; i < num; i++)
    {
        result[pos[i]] = pos[i];
    }
    x = 0;
    for (int i = 0; i < n + 1; i++)
    {
        if (result[i] != -1)
        {
            if (x != num - 1)
            {
                cout << result[i] << " ";
            }
            else
                cout << result[i];
            x++;
        }
    }

    system("pause");
    return 0;
}