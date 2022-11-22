#include <iostream>
#include<string>
using namespace std;
string cmd[10] = {"End","AddLeft","AddRight","DeleteLeft","DeleteRight","IsFull","IsEmpty","Left","Right"};
int which_cmd(string s){//定义一个函数将输入命令转换为int数值	
	int temp = -1;	
	int i;	
	for(i=0;i<=8;i++){		
		if(cmd[i]==s){			
			temp = i;		
		}	
	}	
	return temp;	
} 
template <class T>
struct Node{	
	T data;
	Node<T>* left;	
	Node<T>* right;
	Node(){		
		left = NULL;		
		right = NULL;	
	}	
	Node(T d){		
		data = d;		
		left = NULL;		
		right = NULL;		
	}	
};
template <class T>
struct Deque{
private:	
	int MaxLength;	
	int Length;	
	Node<T>* L;	
	Node<T>* R;
public:	
	Deque(int s = 5){		
		MaxLength = s;		
		Length = 0;		
		L = new Node<T>();		
		R = new Node<T>();		
	}		
	bool IsEmpty()	{		
		return Length==0;	
	}	
	bool IsFull()	{		
		return Length==MaxLength;	
	}	
	void LeftPrint(){		
		if(IsEmpty()){			
			cout<<"EMPTY"<<endl;			
			return;		
	   }		
		Node<T>* Z = L;		
		for(int i=1;i<Length;i++){			
			cout<<Z->data<<" ";			
			Z = Z->right;			
		}				
		cout<<R->data<<endl;	
	} 	
	void RightPrint(){		
		if(IsEmpty()){			
			cout<<"EMPTY"<<endl;			
			return;		
		}		
		Node<T>* Z = R;		
		for(int i=1;i<Length;i++){			
			cout<<Z->data<<" ";			
			Z = Z->left;			
		}	
		cout<<L->data<<endl;
	}
	void AddLeft(T data){		
		Node<T>* temp = new Node<T>(data);		
		if(IsFull()){			
			cout<<"FULL"<<endl;			
			return;		
		}		
		if(IsEmpty()){			
			L = temp;			
			R = temp;			
			Length++;			
			LeftPrint();					
			return;		
		}		
		L->left = temp;		
		temp->right = L;		
		L = temp;		
		Length++;		
		LeftPrint();	
	}	
	void AddRight(T data)	{		
		Node<T>* temp = new Node<T>(data);		
		if(IsFull()){			
			cout<<"FULL"<<endl;			
			return;
		}		
		if(IsEmpty()){			
			L = temp;			
			R = temp;			
			Length++;			
			LeftPrint();			
			return;		
		}		
		R->right = temp;		
		temp->left = R;		
		R = temp;		
		Length++;		
		LeftPrint();	
	}	
	bool DeleteLeft(){		
		if(IsEmpty()){			
			return false;		
		}		
		if(Length==1){		
			Length = 0;			
			cout<<"Empty"<<endl;			
			return true;		
		}		
		Node<T>* temp = L->right;		
		temp->left = NULL;		
		L = temp;		
		Length--;		
		LeftPrint(); 		
		return true;	
	}	
	bool DeleteRight(){		
		if(IsEmpty()){			
			return false;		
		}		
		if(Length==1){			
			Length = 0;			
			cout<<"Empty"<<endl;			
			return true;		
		}		
		Node<T>* temp = R->left;
		temp->right = NULL;		
		R = temp;		
		Length--;		
		LeftPrint();		
		return true;	
	}
};
//int main(){	
//	Deque<int> dq;	
//	string s;	
//	int temp;	
//	while(cin>>s)	{		
//		int flag = which_cmd(s);		
//		switch(flag)		{			
//		case 0:				
//			return 0;			
//		case -1:				
//			cout<<"WRONG"<<endl;				
//			break;			
//		case 1:				
//			cin>>temp;				
//			dq.AddLeft(temp);				
//			break;			
//		case 2:				
//			cin>>temp;				
//			dq.AddRight(temp);				
//			break;			
//		case 3:				
//			if(dq.DeleteLeft()==false)	{					
//				cout<<"EMPTY"<<endl;				
//			}				
//			break;			
//		case 4:				
//			if(dq.DeleteRight()==false)						
//				cout<<"EMPTY"<<endl;				
//			break;			
//		case 5:				
//			if(dq.IsFull())	{					
//				cout<<"YES"<<endl;			
//			}				
//			else{				
//				cout<<"NO"<<endl;				
//			}				
//			break;			
//		case 6:				
//			if(dq.IsEmpty()){					
//				cout<<"YES"<<endl;			
//			}				
//			else{					
//				cout<<"NO"<<endl;				
//			}				
//			break;			
//		case 7:				
//			dq.LeftPrint();				
//			break;			
//		case 8:				
//			dq.RightPrint();				
//			break;		
//		}	
//	}	
//	return 0;
//}