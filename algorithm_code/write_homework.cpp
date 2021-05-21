#include <iostream>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int n;

int compute(int *page, int left, int right, int t)
{
    int rightv;
    while (left <= right)
    {
        int res = 0;
        int mid = (left + right) / 2;
        for (int i = 0; i < n; i++)
        {
            if (mid >= page[i])
            {
                res++;
            }
            if (mid < page[i])
            {
                if (page[i] % mid != 0)
                {
                    res += page[i] / mid + 1;
                }
                else
                {
                    res += page[i] / mid;
                }
            }
        }

        if (res <= t)
        {
            rightv = mid;
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return rightv;
}
int main(void)
{
    int t, res = 0;
    cin >> n >> t;

    int *page = new int[n]();
    for (int i = 0; i < n; i++)
    {
        cin >> page[i];
    }
    sort(page, page + n);
    res = compute(page, 0, page[n - 1], t);

    cout << res;
    system("pause");
    return 0;
}