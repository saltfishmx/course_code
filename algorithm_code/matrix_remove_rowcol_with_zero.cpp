#include <iostream>
#include <stdlib.h>
using namespace std;
/*
为了鼓励小蓝鲸锻炼身体，系里决定对举办一场跑步活动，小蓝鲸每跑步一次都会获得一个积分，最后积分较高的小蓝鲸们将会获得奖品。

同时为了鼓励大家都尽可能参与这场跑步活动，使得尽可能多的人达到锻炼身体的目的，这次活动还设置了一个特殊规则。在活动开始前，小蓝鲸们被随机排列成m×n的方阵，如果在活动结束后某一个小蓝鲸的积分为0，那么和这个小蓝鲸在一行一列的其他人的积分也会被置零，这样每个小蓝鲸为了不拖累其他人都会尽可能参与到这场跑步活动中。

现在假设活动已经结束了，但是仍然有一些小蓝鲸的积分为0，那么同行同列的其他同学积分要被置0，现在需要编写程序统计最终每个小蓝鲸的积分。

要求：除去输入数据之外，额外空间复杂度为O(1)
*/
int main(void)
{
    int m, n;
    cin >> m >> n;
    int **matrix = new int *[m + 1];
    for (int i = 0; i < m+1; i++)
    {
        matrix[i] = new int[n + 1]();
    }
    for (int i = 0; i < m; i++)
    {

        for (int j = 0; j < n; j++)
        {
            cin >> matrix[i][j];
            if (matrix[i][j] == 0)
            {
                matrix[i][n] = -1;
                matrix[m][j] = -1;
            }
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {

            if (matrix[i][n] == -1 || matrix[m][j] == -1)
            {
                if (j == n - 1)
                    cout << 0;
                else
                    cout << 0 << " ";
            }
            else
            {
                if (j == n - 1)
                {
                    cout << matrix[i][j];
                }
                else
                    cout << matrix[i][j] << " ";
            }
        }
        cout << endl;
    }
    system("pause");
    return 0;
}