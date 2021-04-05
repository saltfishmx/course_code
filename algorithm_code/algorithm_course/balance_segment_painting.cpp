#include <stdio.h>
#include <iostream>
static int count = 1;
class solution
{
public:
    void init()
    {
        scanf("%d", &n);
        a = new int[n];
        s = new int[n];
        weights = new int[n];        
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &a[i]);
            a[i] -= 1;
            s[i] = -1;
            weights[i] = 1;
        } 
    }
    void wUnion(int root1, int rootleft,int rootright)
    {
        s[root1]=1;
		int spot;
        if ( s[rootleft] >= 0 && s[rootright]>=0)
        {
            weights[root1] = weights[root1] + weights[rootleft]+weights[rootright];
			
			spot=root1-weights[rootleft];
			weights[spot]=weights[root1];
			spot=root1+weights[rootright];
			weights[spot]=weights[root1];
            if (weights[root1] > count)
            {
                count = weights[root1];
            }
        }
        else if(s[rootleft] >= 0 && s[rootright]<0){
            weights[root1] = weights[root1] + weights[rootleft];   
			spot=root1-weights[rootleft];
			weights[spot]=weights[root1];
            if (weights[root1] > count)
            {
                count = weights[root1];
            }            
        }
        else if(s[rootright] >= 0 && s[rootleft]<0){
            weights[root1] = weights[root1] + weights[rootright];   
			spot=root1+weights[rootright];
			weights[spot]=weights[root1];
            if (weights[root1] > count)
            {
                count = weights[root1];
            }            
        }
        else{
            return;
        }        
    }
    void out()
    {
        for (int i = 0; i < n; i++)
        {
  
            wUnion(a[i],a[i]-1,a[i]+1);  

            std::cout<<count<<" ";   
        }
    }

public:
    int n;
    int *a;
    int *s;
    int *weights;
};
int main()
{
    solution b;
    b.init();
    b.out();
    system("pause");
    return 0;
}