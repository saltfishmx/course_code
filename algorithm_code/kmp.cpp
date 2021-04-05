#include <iostream>
#include <cstring>
#include <stdlib.h>
using namespace std;
void getnext(int *next, string s)
{
    int j = 0, k = -1, lengthp = s.length();
    next[0] = -1;
    j = 1;
    while (j < lengthp)
    {
        k = next[j - 1];
        while (1)
        {
            if (k == -1 || s[j - 1] == s[k])
            {
                k++;
                next[j] = k;
                j++;
                break;
            }
            else
                k = next[k];
        }
    }
}
int fastfind(string s, string &pat, int start, int next[])
{
    //从start开始寻找pat在this串中匹配的位置，若找到，
    //函数返回pat在this串中开始的位置，否则函数返回-1。
    //数组next存放pat的next[j]值
    int posp = 0, post = start;

    int lengthp = pat.length();
    int lengtht = s.length();
    if (start > lengtht - 1)
        return -1; //输入不合法
    while (posp < lengthp && post < lengtht)
    {
        if (posp == -1 || pat[posp] == s[post])
        {
            posp++;
            post++; //对应字符串匹配
        }
        else
            posp = next[posp];
    }
    if (posp < lengthp)
        return -1;
    else
        return post - lengthp;
}
int main(void)
{
    string s;
    string p;
    cin >> s >> p;
    int n = p.length();
    int *next = new int[n]();
    getnext(next, p);
    int start = fastfind(s, p, 0, next);
    if (start == -1)
        cout << start;
    else
    {
        while (start != -1)
        {
            cout << start;
            cout << " ";
            start = fastfind(s, p, start + 1, next);
        }
    }

    //system("pause");
}