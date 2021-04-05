//实现一个简易的计算器来计算一个简单的字符串表达式的值。字符串表达式可以包含左括号 ( ，右括号 )，加号 + ，减号 -，乘号x，非负整数。
//规定所有给出的表达式都是有效的、可以计算的。
//先用栈转化成后缀，再用
#include<iostream>
#include<stack>
#include<string>
#include<math.h>
using namespace std;
int isp(char ch){
    switch (ch){
        case '#':
            return 0;
            break;

        
        case '(':
            return 1;
            break;

        
        case 'x':
            return 5;
            break;
        case '/':
            return 5;
            break;
        case '%':
            return 5;
            break;
        case '+':
            return 3;
            break;   
        case '-':
            return 3;
            break; 
        case ')':
            return 6;
            break;                                                       
    }
    return -1;             
}
int icp(char ch){
    switch (ch){
        case '#':
            return 0;
            break;

        
        case '(':
            return 6;
            break;

        
        case 'x':
            return 4;
            break;
        case '/':
            return 4;
            break;
        case '%':
            return 4;
            break;
        case '+':
            return 2;
            break;   
        case '-':
            return 2;
            break;  
        case ')':
            return 1;
            break;                                                       
    }
    return -1;          
}
class caculator{
public:
    void run(string e);
    stack<double>s;    
private:
  
    void addoperand(double value);
    bool get2operands(double &left,double &right);
    void dooperator(char op);
};
void caculator::dooperator(char op){
    double left,right,value;int result;
    result=get2operands(left,right);
    if(result==true){
        switch(op){
            case '+':value=left+right;s.push(value);break;
            case '-':value=left-right;s.push(value);break;  
            case 'x':value=left*right;s.push(value);break;      
            case '/':if(right==0){
                cerr<<"divide by 0"<<endl;
               
            }
            else{
                value=left/right;
                s.push(value);
                break;
            }
                                          
        }
    }
}
bool caculator::get2operands(double&left,double&right){
    if(s.empty()){
        cerr<<"缺少右操作数"<<endl;
        return false;

    }
    right=s.top();
    s.pop();
    if(s.empty()){
        cerr<<"缺少左操作数"<<endl;
        return false;
    }
    left=s.top();
    s.pop();
    return true;
}
void caculator::addoperand(double value){
    s.push(value);
}
void caculator::run(string e){
    char ch;
    double newoperand;
    int i=0;
    
    while(ch=e[i++],i!=e.length()+1){
        switch(ch){
            case '+':case '-':case 'x':case '/':
            dooperator(ch);
            break; 
       
        default:
            addoperand(ch-'0');
        }     
    }
}



string postfix(string e){
    stack<char>s;
    string res;
    int i=0;
    int length=e.length();
    char ch='#',ch1,op;
    s.push(ch);
    ch=e[i];
    i++;
    while(s.empty()==0&&i!=length+1){
        if(isdigit(ch)){
            res+=ch;
           
            ch=e[i]; 
            i++;   
        }
        else{
            ch1=s.top();
            if(isp(ch1)<icp(ch)){
                s.push(ch);
               
                ch=e[i];
                i++;
            }
            else if(isp(ch1)>icp(ch)){
                op=s.top();
                s.pop();
                res+=op;
            }
            else{
                op=s.top();
                s.pop();
                if(op=='('){
                   
                    ch=e[i];
                    i++;
                }
            }

        }
    }
    return res;
}
int main(void){
    string str,str1;
    cin>>str;
    str+='#';
    //cout<<str;
    str1=postfix(str);
    //cout<<str1<<endl;
    caculator cal;
    cal.run(str1);
    int res=cal.s.top();
    cout<<res;
    system("pause");
    return 0;
}
