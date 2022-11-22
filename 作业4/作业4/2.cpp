#include <stack>
#include <iostream>
#include <fstream>
using namespace std;
template <class T>
void delete_all(stack<T> &s,const T& x){
	if(s.empty()){
		cout<<"Stack is empty!"<<endl;		
		return;	
	}	
	stack<T> temp;	
	while(!s.empty()){
		if(s.top()==x){
			s.pop();	//��ɾ��Ԫ��ֱ�ӳ�ջ	
		}		
		else{			
			temp.push(s.top());//��ջ�ڵ�Ԫ�ظ��ƴ�����ʱջ			
			s.pop();	//��ջ	
		}	
	}	
	while(!temp.empty()){		
		s.push(temp.top());	//��Ԫ�ط���ԭջ	
		temp.pop();	
	}
}
//int main(){	
//	stack<char> m;	
//	char a;
//	cin>>a;
//	
//	while(cin){
//      char t;
//	  cin>>t;
//	  m.push(t);
//	  if(cin.get()=='\n') break;
//	}
//
//	delete_all<char> (m,a);	
//	while(!m.empty())	{		
//		cout<<m.top();		
//		m.pop();		
//		if(!m.empty())			
//			cout<<" ";	
//	}	
//	cout<<endl;	
//	return 0;
//}