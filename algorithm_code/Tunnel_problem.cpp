#include<iostream>
#include<stack>
#include<string>
#include<math.h>
using namespace std;
int N;
//现在有大量的汽车要通过一个隧道，但是隧道中只允许依次通过，不允许超车，超车的车辆将被罚款。 假定每个车辆有一个ID(从1到NN的整数)，
//如果第ii辆车比任意一辆车进入隧道晚，但是比这辆车离开隧道早，那么车辆ii就是要被罚款的。统计所有的被罚款的车辆。
//3 5 2 1 4 -》4 3 2 5 1  check 结束时在3前面的，全加上，check 5 ，若在3后面，5 到 3 之间的 
int find(int index,int *array){
    for(int i=0;i<N;i++){
        if(index==array[i]){
            return i;
        }
    }
    return -1;
}
int main(void){

    cin>>N;
    int array1[N];
    int array2[N];
    int position=0,positionpre=0;
    int i=0;
    int num=0;
    int a;
    int j=0;
    while(j<N){
        cin>>a;
        array1[j]=a;
        j++;
    }
    j=0;
    while(j<N){
        cin>>a;        
        array2[j]=a;
        j++;
    }    
    while(position!=N-1&&i<=N-1){
        positionpre=position;
        position=find(array1[i],array2);//进入数组里的数在出去数组里的位置
        if(i==0)num+=position-i;

        else num+=position-positionpre-1;
        
        while(i<N-1&&find(array1[i+1],array2)<position){
            i++;
            
        }

        if(i<N-1)i++;//此时find(array1[i],array2>position)

    }
    cout<<num;
    system("pause");
}