//#include<iostream>
//#include<fstream>
//using namespace std;
//void Print(char *a,bool *b,int m,int n)
//{
//	if(m==n){
//		for(int i=0;i<n;i++){
//			if(b[i]){
//				if(i==n-1){
//					cout<<a[i];
//				}
//				else{
//					cout<<a[i]<<" ";
//				}
//			}
//		}
//		cout<<endl;
//	}
//	else
//	{
//		b[m] = true;
//		Print(a,b,m + 1,n);
//		b[m] = false;
//		Print(a,b,m + 1,n);
//	}
//}
//int main()
//{
//	int num;
//	cin>>num;
//	char a[26];
//	for(int i=0;i<26;i++)
//	{
//		a[i] = 'a' + i;
//	}
//	bool *b = new bool(num);
//	Print(a,b,0,num);
//
//}