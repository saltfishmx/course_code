#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

int main(void)
{
    int n;
    cin >> n;
    int *a = new int[n]();
    int *b = new int[n]();
    int x = 0;
    int num = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        a[i] = x;
        b[i] = -1;
    }
    for (int i = 0; i < n; i += 2)
    {
        int flag1 = 1, flag2 = 1, postochange;
        if (a[i]/2 !=a[i+1]/2)
        {
            int pos1 = 0, pos2 = 0;
            if (a[i] % 2 == 0)//pos1是要和当前数连起来的数，比如3的pos1是4
            {
                pos1 = a[i] + 1;
            }
            else
            {
                pos1 = a[i] - 1;
            }
            if (a[i + 1] % 2 == 0)
            {
                pos2 = a[i + 1] + 1;
            }
            else
            {
                pos2 = a[i + 1] - 1;
            }


            if (b[pos1] != -1 && b[pos2] != -1 && abs(b[pos1] - b[pos2]) == 1)
            {
                num++;
            }
            else
            {

                if (b[pos1] != -1)
                {
                    num++;
                    if ((b[pos1]) % 2 == 1)
                    {
                        postochange = b[pos1] - 1;
                    }
                    else
                    {
                        postochange = b[pos1] + 1;
                    }

                    b[a[postochange]] = i;
                    int temp=a[i];
                    a[i]=a[postochange];
                    a[postochange]=temp;
                }
                else
                {
                    b[a[i]] = i;
                }

                if (b[pos2] != -1)
                {
                    num++;
                    if ((b[pos2]) % 2 == 1)
                    {
                        postochange = b[pos2] - 1;
                    }
                    else
                    {
                        postochange = b[pos2] + 1;
                    }

                    b[a[postochange]] = i+1;
                    int temp=a[i+1];
                    a[i+1]=a[postochange];
                    a[postochange]=temp;                    
                }
                else
                {
                    b[a[i + 1]] = i + 1;
                }
            }
        }
    }
    cout << num;
    system("pause");
}