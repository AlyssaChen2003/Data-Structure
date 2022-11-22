#include<iostream>
#include<fstream>
using namespace std;
template<class T>
class Node {
public:	
	T item;	
	Node<T>*next;	
	Node(T t = 0, Node<T>*temp = NULL){		
		item = t; next = temp;	
	}
};
template<class T>
class Chain {
private:	
	Node<T>*tail;	
	Node<T>*head;
public:	
	Chain(Node<T>*temp = NULL) { 
		head = tail = temp; 
	}	
	~Chain() {		
		Node<T>*temp = head;		
		while (temp != tail) {			
			head = head->next;			
			delete temp;			
			temp = head;		
		}	
	}	
	bool isempty() {		
		if (head == tail)
			return true;		
		return false;	
	}	
	void insert(T t) {		
		if (head == NULL) {			
			head = new Node<T>(t,tail);			
			return;		
		}		
		Node<T>*temp = new Node<T>(t);		
		Node<T>*curr = head;		
		while (curr != NULL) {			
			if ((curr->item<t) && (curr->next->item>t)) { 				
				temp->next = curr->next;				
				curr->next = temp;				
				return;			
			}			
			curr = curr->next;		
		}	
	}	
	void erase(T t) {				
		if (head == NULL) {			
			cout << "该元素不存在" << endl;			
			return;		
		}		
		if (head->item == t) {			
			Node<T>*temp = head;			
			head = head->next;			
			delete temp;			
			return;		
		}		
		int i = tail->item;		
		tail->item = t;		
		Node<T>*curr = head->next;		
		while (1) {			
			if (curr->next->item == t)				
				break;			
			curr = curr->next;		
		}		
		if (curr->next == tail) {			
			cout << "该元素不存在" << endl; 			
			return;		
		}		
		Node<T>*temp = curr->next;		
		curr->next = curr->next->next;		
		delete temp;		
		tail->item = i;		
		return;	
	}	
	void output() {		
		Node<T>*curr = head;		
		if (head == NULL) {			
			cout <<"NULL"<< endl; 			
			return;		
		}		
		while (curr != tail) {			
			cout << curr->item << " ";			
			curr = curr->next;		
		}		
		cout << endl;	
	}	
	template<typename T>	
	friend class HashChain;
};
template<class T>
class HashChain {
private:	
	int size;	
	Chain<T> *chain;	
	T Max;	
	Node<T> *theOnlyTail;
public:	HashChain(int n = 11, int m = 100) {
			size = n;		
			Max = m;		
			theOnlyTail = new Node<T>(Max);		
			chain = new Chain<T>[size];		
			for (int k = 0; k < size; k++)			
				chain[k].tail = theOnlyTail;	
		}	
		int hash(const T &t) {		
			return 3 * int(t) + 7;	
		}	
		int search(const T &t) {		
			int i = hash(t) % size;		
			return i;	
		}	
		void insert(T t) {		
			int i = search(t);		
			chain[i].insert(t);
		}	
		void erase(T t) {		
			int i = search(t);		
			chain[i].erase(t);	
		}	
		void output() {		
			cout <<"输出哈希散列" << endl;		
			for (int k = 0; k < size; k++)			
				chain[k].output();	
		}
};
//int main() {
//	int size;
//	cout << "请输入哈希表长度：" << endl;
//	cin >> size;
//	HashChain<int> t(size,100);
//	int temp;
//	cout << "请输入散表元素" << endl;
//	for (int i = 0; i < size; i++) {
//		cin >> temp;
//		t.insert(temp);
//	}
//	t.output();
//	int a;
//	cout << "想要删除的元素为：" << endl;
//	cin >> a;
//	t.erase(a);
//	t.output();
//	cout << "想要删除的元素为：" << endl;
//	cin >> a;
//	t.erase(a);
//	t.output();
//	cout << "想要插入的元素为：" << endl;
//	cin >> a;
//	t.insert(a);
//	t.output();
//}