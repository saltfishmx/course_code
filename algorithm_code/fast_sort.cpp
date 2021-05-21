#include<iostream>
#include<stdlib.h>
using namespace std;
void sort(int *a,int l,int r){
    int x=a[l];
    int low=l;
    int high=r;
    if(l>=r)return;
    while(low<high){
        while(low<high&&a[high]>=x){
            high--;
        }
        if(low<high){
            a[low++]=a[high];
        }
        while(low<high&&a[low]<x){
            low++;
        }
        if(low<high){
            a[high--]=a[low];
        }
    }
    a[low]=x;
    sort(a,l,low-1);
    sort(a,low+1,r);
}
int main(void){
    int *a=new int[10];
    a[0]=9;
    a[1]=3;
    a[2]=6;
    a[3]=7;
    a[4]=4;
    a[5]=45;
    a[6]=2;
    a[7]=3;
    a[8]=31;

    a[9]=1;
    sort(a,0,9);
    system("pause");
}