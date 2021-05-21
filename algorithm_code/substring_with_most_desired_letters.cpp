#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;
//参考了力扣1371，做了一天两晚总是超时查了一下qaq

int main(void)
{
    string str;
    cin >> str;
    int *pos = new int[1 << 5];
    int n = str.length();
    for (int i = 0; i < 32; i++)
    {
        pos[i] = -1;
    }
    pos[0] = 0;
    int max = 0, status = 0;
    for (int i = 0; i < n; i++)
    {
        char ch = str[i];
        if (ch == 'n')
        {
            status ^= 1;
        }
        else if (ch == 'j')
        {
            status ^= (1 << 1);
        }
        else if (ch == 'u')
        {
            status ^= (1 << 2);
        }
        else if (ch == 'c')
        {
            status ^= (1 << 3);
        }
        else if (ch == 's')
        {
            status ^= (1 << 4);
        }
        if (pos[status] >= 0)
        { //已经出现过了
            if (max < (i + 1 - pos[status])) //i+1是在考虑初始状态，可考虑字符串为nn
            {
                max = i + 1 - pos[status];
            }
        }
        else
        {
            pos[status] = i + 1;
        }
    }
    cout << max;
    system("pause");
    return 0;
}