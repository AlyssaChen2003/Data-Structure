//#include<iostream>
//#include <cstdio>
//#include <cstring>
//using namespace std;
//template <class T>
//class ChainNode{
//public:
//    T data;
//    ChainNode<T> *next;
//};
//template<class T>
//class extendedChain{
//    public:
//    extendedChain(){first=NULL;last=NULL;}
//    bool IsEmpty() const{return first==NULL;}
//	int Length()const{
//		ChainNode<T> *p=first;
//		int len=0;
//		while(p){
//		len++;
//		p=p->next;
//		}
//		return len;
//}
//	bool Find(int k, T& x)const{
//	if(k<1)return false;
//	ChainNode<T> *p=first;
//	int i=1;
//	while(i<=k&&p){
//	  p=p->next;
//	  i++
//	}
//	if(p){
//		x=p->data;
//		return true;
//	}
//	else
//		return false;
//	
//}
//	int Search(const T& x)const{
//    ChainNode<T> *p=first;
//	int i=1;
//	while(p&&p->data!=x){
//		i++;
//		p=p->next;
//	}
//	if(p)
//		return i;
//	return 0;
//	
//} 
//	extendedChain<T>& Delete(int k,T& x){
//	if(k<1||!first)
//		cout<<"wrong!"<<endl;
//	ChainNode<T> *p=first;
//	int i=1;
//	if(k==1)first=first->next;
//    else{
//        ChainNode<T> *q=first;
//        for(int i=1;i<k-1&&q;i++)
//			q=q->next;
//        if(!q||!q->next)cout<<"wrong!"<<endl;
//        p=q->next;
//        q->next=p->next;
//    }
//    x=p->data;
//    delete p;
//    return *this;	
//}
//    extendedChain<T>& Insert(int k,const T& x){
//		ChainNode<T> *p=first;
//		ChainNode<T> *y=new ChainNode<T>;
//		int i=1;
//		for(i=1;i<k&&y;i++){
//			p=p->next;
//		}
//		if(k&&p->next==NULL){//Ìí¼Óµ½Î²²¿
//        y->next=NULL;
//        p->next=y;
//        last=y;
//    }
//    else if(k){
//        y->next=p->next;
//        p->next=y;
//    }
//    else{
//        y->next=first;
//        first=y;
//        last=y;
//    }
//    return *this;
//}
//
//    void Output(ostream& out)const{
//		for(ChainNode<T> *current=first;current;current=current->next)
//			out<<current->data<<" ";
//	}
//	
//    void Erase(){
//		while(first!=NULL){
//			ChainNode<T>* nextnode=first->next;
//			delete first;
//			first=nextnode;
//		}
//		this->Length()=0;
//	}
// 
//    extendedChain<T>& Append(const T& x){
//		ChainNode<T> *y=new ChainNode<T>;
//    y->data=x;
//    y->next=NULL;
//    if(first!=NULL){
//        last->next=y;
//        last=y;
//    }
//    else{
//		first=y;
//	    last=y;
//	}
//    return *this;
//}
//    public:
//        ChainNode<T> *first,*last;
//};
//template <class T> 
//extendedChain<T> meld(extendedChain<T> A,extendedChain<T> B){
//	extendedChain<T> C;
//    ChainNode<T> *a,*b,*c;
//    a=A.first;
//	b=B.first;
//	while(a&&b){
//		C.Append(a->data);
//		a=a->next;
//		C.Append(b->data);
//		b=b->next;
//	}
//	if(!a&&b){
//		while(b){
//		C.Append(b->data);
//		b=b->next;
//		}
//	}
//	if(a&&!b){
//		while(a){
//		C.Append(a->data);
//		a=a->next;
//		}
//	}
//	return C;
//}
//template <class T> ostream& operator<<(ostream& out, const extendedChain<T>& x){
//		x.Output(out);
//		return out;
//	}
//template <class T> 
//void split(extendedChain<T> &A,extendedChain<T> &B,extendedChain<T> C){
//	ChainNode<T> *a,*b,*c;
//	a=A.first;
//	b=B.first;
//	c=C.first;
//	while(c){
//		A.Append(c->data);
//		c=c->next;
//		if(!c)break;
//		B.Append(c->data);
//		c=c->next;
//	}
//}
//
//int main(){
//	 
//	extendedChain<int> A,B,C;
//	for(int i=1;i<=49;i=i+2)A.Append(i);
//	for(int i=2;i<=30;i=i+2)B.Append(i);
//	cout<<"chain A:"<<endl;
//	A.Output(cout);
//	cout<<endl;
//	cout<<"chain B:"<<endl;
//	B.Output(cout);
//	cout<<endl;
//    C=meld(A,B);
//	cout<<"chain C:"<<endl;
//    C.Output(cout);
//    return 0;
//
//}