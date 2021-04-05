#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

struct triple
{
    int row, col;
    int value;

    triple(int r, int c, int v)
    {
        row = r;
        col = c;
        value = v;
    }
};
int main(void)
{
    int n, t, m;
    cin >> n >> t >> m;
    int a;
    vector<triple> a1;
    vector<triple> a2;
    vector<triple> a3;
    int num1 = 0, num2 = 0;
    triple *p;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < t; j++)
        {
            cin >> a;
            if (a != 0)
            {
                num1++;
                p = new triple(i, j, a);
                a1.push_back(*p);
            }
        }
    }
    for (int i = 0; i < t; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> a;
            if (a != 0)
            {
                num2++;
                p = new triple(i, j, a);
                a2.push_back(*p);
            }
        }
    }
    int *rowsize = new int[t]();
    int *rowstart = new int[t]();
    int *tmp = new int[m];

    for (int i = 0; i < num2; i++)
    {
        rowsize[a2[i].row]++; //b各行非0元素数
    }
    for (int i = 1; i < t; i++)
    {
        rowstart[i] = rowstart[i - 1] + rowsize[i - 1]; //b第i行非0元素开始位置
    }
    int **final = new int *[n]();
    for (int i = 0; i < n; i++)
    {
        final[i] = new int[m]();
    }
    for (int i = 0; i < num1; i++)
    {
        int k = a1[i].col;
        if (rowsize[k] != 0)
        {

            for (int e = 0; e < rowsize[k]; e++)
            {
                final[a1[i].row][a2[rowstart[k] + e].col] += a1[i].value * a2[rowstart[k] + e].value;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {

        for (int j = 0; j < m; j++)
        {

            cout << final[i][j] << " ";
        }
        if (i != n - 1)
            cout << endl;
    }
    system("pause");
    return 0;
}
