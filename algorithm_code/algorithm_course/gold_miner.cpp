#include <stdio.h>
#include <iostream>
#include <vector>
//#define debug
using std::vector;

struct arraypair
{
    vector<int> row;
    vector<int> col;
};

class solution
{
public:
    static void doublesize(int n, vector<arraypair> &p)
    {
        int x;
        if (n % 2 == 1)
        {
            x = n / 2 + 1;
            for (std::vector<int>::size_type i = 0; i < p.size(); i++)
            {
                int row = p[i].row.size();
                int col = p[i].col.size();
                for (std::vector<int>::size_type j = 0; j < row; j++)
                {
                    p[i].row.push_back(x + p[i].row[j]);
                }
                for (std::vector<int>::size_type j = 0; j < col; j++)
                {
                    p[i].col.push_back(x + p[i].col[j]);
                }
            }
        }

        else if (n % 2 == 0)
        {
            x = n / 2;
            for (std::vector<int>::size_type i = 0; i < p.size(); i++)
            {
                int row = p[i].row.size();
                int col = p[i].col.size();
                int flag = 1;
                for (int j = 0; j < row; j++)
                {
                    for (int k = 0; k < col; k++)
                    {
                        if (p[i].row[j] == 1 && p[i].col[k] == x)
                            flag = 0;
                    }
                }
                if (flag)
                {
                    for (int j = 0; j < row; j++)
                    {
                        p[i].row.push_back(x + p[i].row[j]);
                    }
                    for (int j = 0; j < col; j++)
                    {
                        p[i].col.push_back(x + p[i].col[j]);
                    }
                }
                if (!flag)
                {
                    for (int j = 0; j < row; j++)
                    {
                        if (p[i].row[j] != 1)
                        {
                            p[i].row.push_back(x + p[i].row[j]);
                        }
                    }
                    for (int j = 0; j < col; j++)
                    {

                        p[i].col.push_back(x + p[i].col[j]);
                    }
                }
            }
        }
    }
    static void T(int n, vector<arraypair> &p)
    {
        if (n == 2)
        {

            p[0].row.push_back(1);
            p[0].col.push_back(2);
        }
        if (n == 3)
        {

            p[0].row.push_back(3);
            p[0].col.push_back(1);

            p[1].row.push_back(1);
            p[1].col.push_back(2);
            p[1].col.push_back(3);

            p[2].row.push_back(2);
            p[2].col.push_back(3);
        }

        else if (n >= 4)
        {

            T(n / 2, p);
            doublesize(n, p);

            p[n].row.push_back((n / 2) + 1);
            for (int i = 1; i < n / 2; i++)
            {
                p[n].col.push_back(i);
            }
            for (int i = n / 2 + 2; i <= n; i++)
            {
                p[n].col.push_back(i);
            }
            //上面两个循环是加了一行
            p[n + 1].col.push_back((n + 1) / 2);
            for (int i = 1; i < (n + 1) / 2; i++)
            {
                p[n + 1].row.push_back(i);
            }
            for (int i = (n + 1) / 2 + 2; i <= n; i++)
            {
                p[n + 1].row.push_back(i);
            }
            //上面两个循环加了一列
            for (int i = 1; i < (n + 1) / 2; i++)
            {
                p[n + 2].col.push_back(i);
            }
            for (int i = n / 2 + 2; i <= n; i++)
            {
                p[n + 2].row.push_back(i);
            }
            //上面两个循环加了左下角的一个框框
            for (int i = (n + 1) / 2 + 1; i <= n; i++)
            {
                p[n + 3].col.push_back(i);
            }
            for (int i = 1; i < n / 2 + 1; i++)
            {
                p[n + 3].row.push_back(i);
            }
            //上面两个循环加了右上角的一个框框
            /*
            if (n % 2 == 1)
            {
                p[4998].col.push_back(n / 2);
                for (int i = 2; i < n/2; i++)
                {
                    p[4998].row.push_back(i);
                }
            }
            */
        }
    }
};

int main()
{
    vector<arraypair> p;
    //arraypair* p=new arraypair[50];
    p.resize(5000);

    int n;
    scanf("%d", &n);
    solution::T(n, p);
    p[4999].col.push_back(n);

    for (int i = 1; i < n; i++)
    {
        p[4999].row.push_back(i);
    }
#ifdef debug
    vector<int> a;
    vector<int> b;
    int **array = new int *[n];

    for (int i = 0; i < n; i++)
    {

        array[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            array[i][j] = 0;
        }
    }
#endif
    for (std::vector<int>::size_type i = 0; i < p.size(); i++)
    {
        if (p[i].row.size() == 0)
        {
            continue;
        }
        for (std::vector<int>::size_type j = 0; j < p[i].row.size(); j++)
        {
            std::cout << p[i].row[j] << " ";
            //a.push_back(p[i].row[j]);
        }
        std::cout << std::endl;
        for (std::vector<int>::size_type j = 0; j < p[i].col.size(); j++)
        {
            std::cout << p[i].col[j] << " ";
            //b.push_back(p[i].col[j]);
        }
        std::cout << std::endl;

    }
    system("pause");
    return 0;

}