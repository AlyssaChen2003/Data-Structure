#include <iostream>
#include <cstdio>
#include <fstream>
using namespace std;
long long a[91];
long long F(int n){
   	   if(n<3)
		   return 1;
	   if(a[n]!=0)
		   return a[n];
	   a[n]=F(n-1)+F(n-2);
	   return a[n];
}
int main(){
	int n;
	cin>>n;
	if(n>90||n<0){
	   cout<<"WRONG"<<endl;

	}
	else{
		if(n==0){
		cout<<"0"<<endl;
		}
		else{
		cout<<F(n);
		cout<<endl;
		}
	
	}
}
