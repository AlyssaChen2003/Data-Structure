#include<iostream>
using namespace std;

template<class T>
class list {//公式化描述
public:
	T *a;
	int num;
	
	list() {// create a list for players
		a = new T[100];
		for (int i = 1; i < 101; i++)
			a[i - 1] = i;
		num = 100;
	}
	
	list(int n) {
		a = new T[n];
		for (int i = 1; i <n+1; i++)
			a[i - 1] = i;
		num = n;
	}
	~list() {
		delete[]a;
	}
	
	T getElement(int idex) {
		return a[idex];
	}
	
	T outElement(int idex) {//player out
		T m = a[idex];
		a[idex] = 0;
		num--;
		return m;
	}
	
	int getNum() {//numbers of players
		return num;
	}
	
	void  printLastNum(int n) {//print the number of winner
		T sum=0;
		for (int i = 0; i < n; i++)
			sum += a[i];//only the survivor's number is nonzero
		cout << sum<<endl;
	}
};
template<class T>
void f1(int n, int m) {
	list<T> list1(n);
	int flag = 0;
	for (int i = 0; i < n; i++) {
		if (list1.getNum() == 1)//game over and print the winner
		{
			list1.printLastNum(n);
			break;
		}
		if (list1.getElement(i) != 0)//player still alive
			flag++;//count plus one

		if (flag == m)//when every round ends print the loser
		{
			cout << list1.outElement(i) << " ";
			flag = 0;//reset the flag
		}
		if (i == n - 1)
			i = -1;
	}
};
template<class T>
class Node{//链表描述
public:
	T data;
	Node<T>*next;
	
	Node() {
		data = 0;
	}
	
	Node(T data) {
		this->data = data;
	}
};

template <class T>
class ArrayList:public Node<T>{
public:
	Node<T>*first,*end;
	int num;
	ArrayList() {
		first =NULL;
		num = 0;
	}
	ArrayList(int n) {
		first=end=new Node<T>(1);
		for (int i = 2; i < n + 1; i++) {
			Node<T>*p=new Node<T>(i);
			end->next = p;//append players
			end = p;
		}
		num = n;
	}
	int getNum() {
		return num;
	}
	T getElement(int idex) {
		Node<T>*p = first;
		for (int i = 0; i <idex; i++)
			p = p->next;
		return p->data;
	}
	T outElement(int idex) {
		Node<T>*p = first;
		for (int i = 0; i < idex; i++)
			p = p->next;
		T m = p->data;
		p->data = 0;//player out
		num--;
		return m;
	}
	void  printLastNum(int n) {
		T sum = 0;
		Node<T>*p = first;
		for (int i = 0; i < n; i++)
		{
			sum += p->data;
			p = p->next;
		}
		cout << sum<<endl;
	}
};
template<class T>
void f2(int n, int m) {
	ArrayList<int> list1(n);
	int flag = 0;
	for (int i = 0; i < n; i++) {
		if (list1.getNum() == 1)
		{
			list1.printLastNum(n);
			break;
		}
		if (list1.getElement(i) != 0)
			flag++;
		if (flag == m)
		{
			cout << list1.outElement(i) << " ";
			flag = 0;
		}
		if (i == n - 1)
			i = -1;
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	if (n < 3 || n>100)
	{
		cout << "WRONG" << endl;
		return 0;
	}
	if (m < 1)
	{
		cout << "WRONG" << endl;
		return 0;
	}
	f1<int>(n, m);
	f2<int>(n, m);
	return 0;
}
