#include<iostream>
#include<stdio.h>
#include<string>
#include<map>
#include<stack>
using namespace std;
template<class T>
struct binaryTreeNode{
	T element;
	binaryTreeNode<T> *leftChild,*rightChild;
	binaryTreeNode(){
		leftChild=rightChild=NULL;
	}
	binaryTreeNode(const T& x){
		element=x;
		leftChild=rightChild=NULL;
	}
	binaryTreeNode(const T& x,binaryTreeNode *L,binaryTreeNode *R){
		element=x;
		leftChild=L;
		rightChild=R;
	}
};
int GetLength(string s){	
	int len = 0;	
	while (s[len] != '\0'){		
		len++;	
	}	
	return len;
}
string midtobeh(string s){	
	string temp = "";	
	map<char, int> op;	
	stack<char> stk;	
	op['('] = 0;	
	op[')'] = 0;	
	op['+'] = 1;	
	op['-'] = 1;	
	op['*'] = 2;	
	op['/'] = 2;	
	for (int i = 0; i < GetLength(s); i++)	{		
		if (op.count(s[i])==1)	{			
			if (s[i] == ')'){				
				while (stk.top() != '('){					
					temp += stk.top();					
					stk.pop();				
				}				
				stk.pop();			
			}			
			else if (stk.empty() || s[i] == '(' || op[s[i]] > op[stk.top()]){				
				stk.push(s[i]);			
			}			
			else if (op[s[i]] <= op[stk.top()]){				
				while (op[s[i]] <= op[stk.top()] && (!stk.empty())){					
					temp += stk.top();					
					stk.pop();					
					if (stk.empty())						
						break;				
				}				
				stk.push(s[i]);			
			}		
		}		
		else{			
			temp += s[i];		
		}				/*cout<<temp<<"\t";		
				stk1 = stk;		
				while(!stk1.empty()){			
				cout<<stk1.top();			
				stk1.pop();		
				}		
				cout<<endl;		*/		
		if (i == GetLength(s) - 1)	{			
			while (!stk.empty()){				
				temp += stk.top();				
				stk.pop();			
			}			
			break;		
		}	
	}	
	return temp;
}
struct Node{	
	char c;	
	Node* left;	
	Node* right;	
	Node(char ch = 0)	{		
		c = ch;		
		left = NULL;		
		right = NULL;	
	}
};
Node *buildtree(string s){	
	stack<Node *> stk;	
	Node *n,*n1,*n2;	
	for(int i=0;i<GetLength(s);i++)	{		
		if((s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z'))		{			
			n = new Node(s[i]);			
			stk.push(n);			
		}			
		else		{			
			n = new Node(s[i]);			
			n1 = stk.top();			
			stk.pop();			
			n2 = stk.top();			
			stk.pop();			
			n->left = n2;			
			n->right = n1;			
			stk.push(n);		
		}	
	}	
	n = stk.top();	
	stk.pop();	
	return n;
}
void visit(Node* temproot, int level) {	
	if (temproot->right != NULL)	{		
		visit(temproot->right, ++level);		
		--level;	
	}	
	for (int k = 0; k < 2 * level; k++)		
		cout << ' ';	
	cout << temproot->c << endl;	
	if (temproot->left != NULL)	{		
		visit(temproot->left, ++level);		
		--level;	
	}
}
void output(Node* root){	
	Node* temp = root;	
	int level = 0;	
	if(root->right!=NULL)		
		visit(root->right, ++level);	
	--level;	
	cout << root->c << endl;	
	if(root->left!=NULL)		
		visit(root->left, ++level);	
	--level;
}

int main(){	
	string s,data;	
	s="a+b";
	data = midtobeh(s);	
	Node* n = buildtree(data);	
	output(n);	
	return 0;
}
