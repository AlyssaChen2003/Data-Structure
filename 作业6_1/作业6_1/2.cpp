#include<iostream>
#include<string>
#include<stack>
#include<iomanip>

using namespace std;

	string postfix(string exp){
         char token;     //��ǰ��ȡ���ַ� 
         string s;
         stack<char>opStack;
         string postfixExp;  //Ŀ���׺���ʽ
         for(int i=0;i<exp.length();i++)
         {
                   token=(char)exp[i]; 
                   switch(token) 
                   {
                   case '(':
                            opStack.push(token); //�� ( �����ջ�� 
                            break;
                   case ')':
                            while(opStack.top()!='(') //����֮ƥ��ģ�֮ǰ������Ԫ�س�ջ 
                            {
                                     s=opStack.top();
                                     postfixExp.append(s);
                                     opStack.pop();
                            }
                            opStack.pop();
                            break;
                   case '+'://��ջΪ�� �� ջ��Ϊ�� �� ��ǰΪ*/ ��ջ��Ϊ +- ����ǰ��������ȼ����ߣ� ��ֱ����ջ 
                   case '-':
                   case '*':
                   case '/':
                            if(opStack.empty()||opStack.top()=='('||(token=='*'||token=='/')&&(opStack.top()=='+'||opStack.top()=='-'))
                            {
                                     opStack.push(token);
                            }
                            else //�����ȼ�����ջ��Ԫ��  
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
                   default: //��Ϊ��������ֱ�����  
                                     s=token;
                                     postfixExp.append(s);
                                     break;
                   }
         }
         while(!opStack.empty())   //��ջ��ʣ���Ԫ���������  
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
         Tnode* buildTree(string exp);//��׺���ʽ���ɶ�����
         int depth(Tnode *root);//��������
         void print(Tnode *node_ptr, int depth);//ת���ӡ������(��ʱ��ת90�ȴ�ӡ)
        // void inorderOutput(Tnode *t);
};
 //��׺���ʽ���ɶ�����
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

//��������  
int Tnode::depth(Tnode *root)
{
         int i,j;
         if(root==NULL)
                   return 0;
         i=depth(root->left);
         j=depth(root->right);
         return (i>j)?i+1:j+1; 
}




void Tnode::print(Tnode *node_ptr, int depth)//��ʱ��90�ȴ�ӡ������(ֱ�����)
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
         string infix="a+b+c*(d+e)";  //�������׺���ʽ  
         //string infix;                  //�Լ����������ʽ
         //cout<<"��������׺���ʽ"<<endl;
         //getline(cin,infix);
         string s=postfix(infix); //sΪ�����Ϊ�ĺ�׺���ʽ  
         cout<<"��׺���ʽΪ��"<<s<<endl;
         Tnode tree(' ');
         Tnode *root;
         int high;
         root=tree.buildTree(s);
         high=tree.depth(root);
         tree.print(root,high);


}

