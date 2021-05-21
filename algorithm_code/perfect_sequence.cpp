#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
/*题目描述
给定两个字符串ss和tt, ss长度为nn，tt长度为mm。

给定序列pp = {p1p1，p2p2，... pmpm}，其中1≤p1<p2<...<pm≤n1≤p1<p2<...<pm≤n，表示从字符串ss中抽取长度为mm的子串，pipi表示子串元素在原字符串ss中的对应下标。

如果对于1≤i≤m1≤i≤m 都有 spi=tispi=ti， 那么序列pp被称为完美序列，也就是ss中抽取的子串和tt完全相同。序列pp的宽度定义为max1≤i<m(pi+1−pi)max1≤i<m(pi+1−pi)。

请确定所有完美序列的最大宽度。

提示：无需穷举所有的完美序列，存在复杂度为O(n)O(n)的算法。

输入
第一行包含一个长度为nn的字符串ss，由小写字母组成。

第二行包含一个长度为mm的字符串tt，由小写字母组成。

输出
输出一个整数:所有完美序列的最大宽度。

如果没有完美序列，输出-1
*/
int main(void)
{
    string s;
    string t;
    int n, m;
    cin >> s >> t;
    n = s.length();
    m = t.length();
    int *array = new int[n];
    int j=0;
    int max=0;
    for(int i=0;i<n;i++){
        if(s[i]==t[j]){
            array[j++]=i;
        }
    }
    if(j<m-1){
        cout<<-1;
        return 0;
    }
    int x=m-1;
    for(int i=n-1;i>=0;i--){
        if(s[i]==t[x]&&x>0){
            if(max<i-array[x-1]){
                max=i-array[x-1];
            }
            x--;
        }
    }
    cout<<max;
    system("pause");
    return 0;
}