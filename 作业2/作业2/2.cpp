#include<iostream>
#include <cstdio>
#include <cstring>
using namespace std;
template <class T>
class DoubleNode {
    public:
        T data;
        DoubleNode<T> *left,*right;
};
template<class T>
class DoubleChain {
    public:
        DoubleChain() {LeftEnd=RightEnd=NULL;};   
        int Length() const{
			DoubleChain<T> *p=LeftEnd;
			int index=0;
			while(p!=RightEnd){
				index++;
				p=p->right;
			}
			return index+1;
		}

        bool Find(int k, T& x) const{
			if(k<1)return false;
			DoubleChain<T> *p=LeftEnd;
			int index=1;
			while(index<=k&&p){
				p=p->right;
			}
			if(p){
				x=p->data;
				return true;
			}
			else
				return false;
		}


        int Search(const T& x) const{
			DoubleChain<T> *p=LeftEnd;
			int index=1;
			while(p&&p->data!=x){
				p=p->right;
				index++;
			}
			return index+1;
		}
        DoubleChain<T>& Delete(int k,T& x){
			if(k<1||!LeftEnd)
				cout<<"wrong!";
			DoubleChain<T> *p=LeftEnd;
			int index=1;
			while(index<k-1&&p){
				p=p->right;
				index++;
			}
			DoubleChain<T> *q=new DoubleChain<T>;
			q=p->right;
			x=q->data;
			p->right=q->right;
			DoubleChain<T> *r=new DoubleChain<T>;
			r=q->right;
			r->left=p;
			delete q;
		}
        DoubleChain<T>& Insert(int k,const T& x){
			if(k<0)cout<<"wrong!"<<endl;
			DoubleChain<T> *p=LeftEnd;
			int index=1;
			DoubleNode<T> *y=new DoubleNode<T>;
            y->data=x;
    if(k&&p->right==NULL){
        y->right=NULL;
        y->left=p;
        p->right=y;
        RightEnd=y;
    }
    else if(k){
        y->left=p->left;
        p->left->right=y;
        y->right=p;
        p->left=y;
    }
    else{
        y->left=NULL;
        y->right=p;
        p->left=y;
        LeftEnd=y;
    }
    return *this;
}

        void Output(ostream& out) const{
       DoubleNode<T> *current;
    for(current=LeftEnd;current;current=current->right)
        out<<current->data<<"  ";
}
        DoubleChain<T>& Append(const T& x){
			DoubleNode<T> *y=new DoubleNode<T>;
			y->right=NULL;
			y->data=x;
			if(LeftEnd!=NULL){
				RightEnd->right=y;
				y->left=RightEnd;
				RightEnd=y;
			}
			else{
				LeftEnd=y;
				RightEnd=y;
				y->left=NULL;
			}
			return *this;
		}
    //test22
   /* void split(DoubleChain<T> &A,DoubleChain<T> &B){
		DoubleNode<T> *c;
	    c=this->LeftEnd;
	while(c){
		A.Append(c->data);
		c=c->right;
		if(!c)break;
		B.Append(c->data);
		c=c->right;    
    
	}
	}*/

    public:
        DoubleNode<T> *LeftEnd,*RightEnd;
}; 
template <class T>
ostream& operator<<(ostream& out, const DoubleChain<T>& x){
    x.Output(out);
    return out;
}

template<class T>
void split(DoubleChain<T> &A,DoubleChain<T> &B,DoubleChain<T> C){
	DoubleNode<T> *c;
	c=C.LeftEnd;
	while(c){
		A.Append(c->data);
		c=c->right;
		if(!c)break;
		B.Append(c->data);
		c=c->right;    
    
	}
}

int main(){
	DoubleChain<int> A,B,C;
	for(int i=1;i<=50;i++)C.Append(i);
	cout<<"chain C:"<<endl;
	C.Output(cout);
	cout<<endl;
	split(A,B,C);
	cout<<"chain A:"<<endl;
	A.Output(cout);
	cout<<endl;
	cout<<"chain B:"<<endl;
	B.Output(cout);
	cout<<endl;
	cout<<"current chain C:"<<endl;
	C.Output(cout);
	cout<<endl;
}



