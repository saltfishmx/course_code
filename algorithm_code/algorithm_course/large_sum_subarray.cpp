#include <stdio.h>
#include <iostream>
class solution
{
public:
    static long long count_large_sum_array(long long *array, long long n, long long t)
    {
        long long *sum = new long long[n + 1];
        sum[0] = 0;
        for (long long i = 0; i < n; i++)
        {
            sum[i + 1] = sum[i] + array[i];
        }
        long long ans = 0;

        /*for(int i=0;i<=n;i++){
            std::cout<<sum[i]<<std::endl;
        }
        */
        long long begin = 0, end = n;
        ans = mergeSort(sum, begin, end, t);
        return ans;
    }

    static long long merge(long long A[], long long begin, long long mid, long long end, long long t)
    {
        static long long count = 0;
        long long result[end - begin + 1];
        long long i = begin;
        long long j = mid + 1;
        long long k = 0;

        while (i <= mid && j <= end)
        {
            if (A[i] <= A[j])
            {

                result[k++] = A[i++];
            }
            else
            {
                //count += mid - i + 1;
                result[k++] = A[j++];
            }
        }
        while (j <= end)
            result[k++] = A[j++];
        while (i <= mid)
            result[k++] = A[i++];
        i = mid;
        j = end;

        while (i >=begin && j >= mid+1)
        {
            if (A[i] + t < A [j])
            {

                count += i - begin + 1 ;
                j--;
            }
            else
            {
                i--;
            }
        }

        for (k = 0; k < end - begin + 1; k++)
            A[begin + k] = result[k];

        /*
        i=mid;
        while (i >= begin)
        {
            j=mid+1;
            while (j <= end)
            {
                if (A[j] - A[i] > t)
                {
                    count++;
                }
                j++;
            }
            i--;
  
        }     
 */
        return count;
    }

    static long long mergeSort(long long a[], long long begin, long long end, long long t)
    {
        long long sum = 0;
        if (begin < end)
        {
            long long mid = (begin + end) / 2;
            mergeSort(a, begin, mid, t);
            mergeSort(a, mid + 1, end, t);
            sum = merge(a, begin, mid, end, t);
        }
        return sum;
    }
};
int main()
{

    long long n;
    long long t;

    std::cin >> n >> t;
    long long *array = new long long[n];
    for (long long i = 0; i < n; i++)
    {
        scanf("%lld", &array[i]);

        //std::cin>>array[i];
    }
    std::cout << (solution::count_large_sum_array(array, n, t));
    system("pause");
    return 0;
}