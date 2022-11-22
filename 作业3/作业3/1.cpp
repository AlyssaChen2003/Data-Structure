#include<iostream>
using namespace std;
template<class T>
class upperTrianglularMatrix{
private:
	int n;
	T *t;
public:
	upperTrianglularMatrix(int s){
		n=s;
		t=new T[n*(n-1)/2+1];
	}
	void setofupper(int i,int j,  T x){
		if(i<=j)
			t[((i-1)*(n+n-i+2)/2)+j-i]=x;
		else
			t[((i-1)*(n+n-i+2)/2)+j-i]=0;
	}
	T getofupper(int i,int j){
		if(i>j){
			return 0;
		}
		else{
			return t[((i-1)*(n+n-i+2)/2)+j-i];
		}
	}
		void printofupper(){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)
				cout<<this->getofupper(i,j)<<" ";
			cout<<endl;
		}
		cout<<endl;
	}
};
	
template <class T>
class lowerTrianglularMatrix{
private:
	int n;
	T *t;
public:
	lowerTrianglularMatrix(int s){
		n=s;
		t=new T[n*(n-1)/2];
	}
	void setoflower(int i,int j,  T x){
		if(i>=j)
			t[i*(i-1)/2+j-1]=x;
		else
			t[i*(i-1)/2+j-1]=0;

	}
	
	T getoflower(int i,int j){
		if(i<j)
			return 0;
		else
			return t[i*(i-1)/2+j-1];
	}
	void printoflower(){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)
				cout<<this->getoflower(i,j)<<" ";
			cout<<endl;
		}
		cout<<endl;
	}

      upperTrianglularMatrix<T> trans(){
		upperTrianglularMatrix<T> m(this->n);
	
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
			    T temp=this->getoflower(i,j);
				m.setofupper(j,i,temp);
			
			}
		
		}
		return m;
	}
};
//int main(){
//	lowerTrianglularMatrix<int> A(4);
//	upperTrianglularMatrix<int> B(4);
//	 for(int i=1;i<=4;i++){
//		for(int j=1;j<=i;j++){
//			int temp;
//			cin>>temp;
//              A.setoflower(i,j,temp);
//			 
//			  	
//		}
//	 }
//    A.printoflower();
//	B=A.trans();
//	B.printofupper();
//}


