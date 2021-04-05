#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;
static int lans = 0;
class solution
{
public:
    void func0(int y)
    {
        int x = (y + lans) % mod;
        array.push_back(x);
    }
    void func1(int y)
    {
        int x = (y + lans) % mod;
        int count = 0;

        vector<int>::iterator itr = array.begin();
        while (itr != array.end())
        {
            if (*itr == x&&count==0)
            {
                itr = array.erase(itr);
                count++;
            }
			else if(*itr==x&&count!=0){
				count++;
				itr++;
			}
            else
                itr++;
        }
        std::cout<<count<<std::endl;
    }
    void func2(int u, int v){
        int l= (u+lans) % mod;
        int r= (v+lans) % mod;
        if(l>r){
            int tmp = l;
            l = r;
            r = tmp;
        }
        int sum=0;
        vector<int>::iterator itr = array.begin();
        while (itr != array.end())
        {
            if (*itr >l && *itr <=r)
            {
                sum+=*itr;
            }

            
            itr++;
        }     
        std::cout<<sum<<std::endl;
        lans=sum;   
    }

public:
    vector<int> array;
    int mod;
};
int main()
{
    solution a;

    int Q;
    int x, l, r;
    scanf("%d", &Q);
    scanf("%d", &a.mod);
    int mode;
    for (int i = 0; i < Q; i++)
    {
        scanf("%d", &mode);
        switch (mode)
        {
        case 0:
            scanf("%d", &x);
            a.func0(x);
            break;
        case 1:
            scanf("%d", &x);
            a.func1(x);
            break;
        case 2:
            scanf("%d", &l);
            scanf("%d", &r);
            a.func2(l, r);
            break;
        default:
            printf("error\n");
        }
    }
    system("pause");
    return 0;
}