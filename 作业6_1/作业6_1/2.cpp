#include<iostream>
#include<string>
#include<stack>
#include<iomanip>

using namespace std;

	string postfix(string exp){
         char token;     //当前读取的字符 
         string s;
         stack<char>opStack;
         string postfixExp;  //目标后缀表达式
         for(int i=0;i<exp.length();i++)
         {
                   token=(char)exp[i]; 
                   switch(token) 
                   {
                   case '(':
                            opStack.push(token); //是 ( 则放入栈中 
                            break;
                   case ')':
                            while(opStack.top()!='(') //将与之匹配的（之前的所有元素出栈 
                            {
                                     s=opStack.top();
                                     postfixExp.append(s);
                                     opStack.pop();
                            }
                            opStack.pop();
                            break;
                   case '+'://若栈为空 或 栈顶为（ 或 当前为*/ 且栈顶为 +- （当前运算符优先级更高） 则直接入栈 
                   case '-':
                   case '*':
                   case '/':
                            if(opStack.empty()||opStack.top()=='('||(token=='*'||token=='/')&&(opStack.top()=='+'||opStack.top()=='-'))
                            {
                                     opStack.push(token);
                            }
                            else //若优先级低于栈顶元素  
                            {
                                     s=opStack.top();
                                     postfixExp.append(s);
                                     opStack.pop();
                                     if(opStack.top()=='+'||opStack.top()=='-')
                                     {
                                               s=opStack.top();
                                               postfixExp.append(s);
                                               opStack.pop();
                                     }
                                     opStack.push(token);
                            }
                            break;
                   default: //若为操作数则直接输出  
                                     s=token;
                                     postfixExp.append(s);
                                     break;
                   }
         }
         while(!opStack.empty())   //将栈中剩余的元素依次输出  
         {
                   s=opStack.top();
                   postfixExp.append(s);
                   opStack.pop();
         }
         return postfixExp;
};
class Tnode
{
public:
         char value;
         Tnode *left,*right;
         Tnode(){}
         Tnode(const char value,Tnode *left=NULL,Tnode *right=NULL):value(value), left(left), right(right)
         {}
         Tnode* buildTree(string exp);//后缀表达式生成二叉树
         int depth(Tnode *root);//返回树高
         void print(Tnode *node_ptr, int depth);//转向打印二叉树(逆时针转90度打印)
        // void inorderOutput(Tnode *t);
};
 //后缀表达式生成二叉树
Tnode* Tnode::buildTree(string exp)
{
         Tnode *ptr;         
         stack<Tnode*>nodeStack;
         char c;
         int i=0;
         c=exp[i++];
         while(c!='\0')
         {
                   if(c!='+' && c!='-' && c!='*' && c!='/')
                   {
                            ptr=new Tnode(c);
                            nodeStack.push(ptr);
                            c=exp[i++];
                   }
                   else
                   {
                            ptr=new Tnode(c);
                            if(!nodeStack.empty())
                            {
                                     ptr->right=nodeStack.top();
                                     nodeStack.pop();
                            }
                            if(!nodeStack.empty())
                            {
                                     ptr->left=nodeStack.top();
                                     nodeStack.pop();
                            }
                            nodeStack.push(ptr);
                            c=exp[i++];
                   }
         }
         return ptr;
}

//返回树高  
int Tnode::depth(Tnode *root)
{
         int i,j;
         if(root==NULL)
                   return 0;
         i=depth(root->left);
         j=depth(root->right);
         return (i>j)?i+1:j+1; 
}




void Tnode::print(Tnode *node_ptr, int depth)//逆时针90度打印二叉树(直接输出)
{ 
         if (node_ptr!= NULL)
    {
        print(node_ptr->right, depth+1);
        cout<<setw(3*depth)<<" ";
        cout<<node_ptr->value<<endl;
        print(node_ptr->left,depth+1);
    }
}
int main()
{
         string infix="a+b+c*(d+e)";  //输入的中缀表达式  
         //string infix;                  //自己输出任意表达式
         //cout<<"请输入中缀表达式"<<endl;
         //getline(cin,infix);
         string s=postfix(infix); //s为输出化为的后缀表达式  
         cout<<"后缀表达式为："<<s<<endl;
         Tnode tree(' ');
         Tnode *root;
         int high;
         root=tree.buildTree(s);
         high=tree.depth(root);
         tree.print(root,high);


}

