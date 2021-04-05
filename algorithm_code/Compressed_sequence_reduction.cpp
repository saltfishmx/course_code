#include<iostream>
#include<stack>
#include<string>
#include<math.h>
using namespace std;
int main(void){
    string str;
    cin >> str;
 
    int positionl=-1;
    int positionr=-1;    
    while(positionl==-1){
     
        for(int i=0;i<str.length();i++){//找最内层的[
        
            if(str[i]=='['){
                positionl=i;
                
            }
        }
        if(positionl==-1)break;
        for(int i=positionl;i<str.length();i++){//找最内层的]
        
            if(str[i]==']'){
                positionr=i;
                break;
            }
        }  
        if(positionl!=-1){//括号还没消除干净
            int length=positionr-positionl-1;
            string substr=str.substr(positionl+1,length);
            int num=0;
            int i=0;
            char ch=str[positionl-i-1];
            while(isdigit(ch)){
                i++;
                ch=str[positionl-i-1];
            }
            for(int j=0;j<i;j++){
                ch=str[positionl-i+j];
                num*=10;
                num+=ch-'0';
                
            }
            str.erase(positionr,1);
            for(int k=0;k<num-1;k++){
                str.insert(positionl+1,substr);
            }
            
            str.erase(positionl-i,i+1);
            positionl=-1;
        }      
        else {
            break;
        }
    }
    cout<<str;
    system("pause");
}