#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
int get_between(char *origin, int &depth, string &s, int &flag)
{

    int i = 0;
    if (origin[i] != '/')
    {
        printf("the first char is not / \n,something must be wrong");
        depth += 0;
        flag = 0;
        return i + 1;
    }
    while (origin[i + 1] == '/')
    {
        i++;
    }
    if (origin[i + 1] == '\0')
    {
        depth += 0;
        flag = 0;
        return 1;
    }

    else if (origin[i + 1] == '.')
    {
        if (origin[i + 2] == '\0')
        {
            flag = 0;
            return i + 2;
        }
        else if (origin[i + 2] == '.' && origin[i + 3] == '/')
        {
            depth -= 1;
            flag = 0;
            return i + 3;
        }
        else if (origin[i + 2] == '.' && origin[i + 3] == '\0')
        {
            depth -= 1;
            flag = 0;
            return i + 3;
        }
        else if (origin[i + 2] == '/')
        {

            flag = 0;
            return i + 2;
        }
        else
        {
            flag = 1;
            while (origin[i + 1] != '/')
            {
                s += origin[i + 1];
                i++;
            }
            depth += 1;
            return i + 1;
        }
    }
    else
    {
        flag = 1;
        while (origin[i + 1] != '/')
        {
            s += origin[i + 1];
            i++;
        }
        depth += 1;
        return i + 1;
    }
}
int main(void)
{
    string str, s1;
    cin >> str;
    char **array = new char *[100]; //存放过程中的目录名
    int depth = 0;                  //最终目录层数
    int flag = 0;                   //判断get_between返回的是不是一个目录名
    int num = 0;
    int newstart = 0;
    char ch;
    for (int i = 0; i < str.length();)
    {
        s1 = "";
        i += get_between(&(str[i]), depth, s1, flag);
        if (depth <= 0)
        {
            //如果某次发现目录层数不对了，要建立新的工作区
            newstart += num;
            num = 0;
            depth = 0;
        }
        if (flag)
        {
            int length = s1.length();
            char *s2 = new char[length];
            strcpy(s2, &s1[0]);
            array[newstart + num] = s2;
            num++;
        }
    }
    if (depth == 0)
    {
        cout << "/";
    }
    for (int i = 0; i < depth; i++)
    {

        cout << "/";

        cout << array[newstart + i];
    }
     system("pause");
    return 0;
}