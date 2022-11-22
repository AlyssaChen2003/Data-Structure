//#include<iostream>
//using namespace std;
//template<class T>
//class Node {
//public:
//	T data;
//	Node<T>* next;
//	Node() {
//		data = 0;
//	}
//	Node(T data) {
//		this->data = data;
//	}
//};
//template<class T>
//class LinkedList :public Node<T> {
//public:
//	Node<T>* first, * end;
//	LinkedList() {
//		first =end= nullptr;
//	}
//	~LinkedList();
//	bool isempty();
//};
//
//template<class T>
//LinkedList<T>::~LinkedList()
//{
//	Node<T>* p = first;
//	while (p != end) {
//		first = first->next;
//		delete p;
//		p = first;
//	}
//}
//
//template<class T>
//bool LinkedList<T>::isempty()
//{
//	if (first == nullptr)
//		return true;
//	return false;
//}
//
//template<class T>
//class hashChainsWithTail {
//private:
//	int size;//��ϣ����
//	LinkedList<T>* chain;//��ϣ��
//	Node<T>* theonlyTail;//��ͬ��β�ڵ�
//	int Max;//�ؼ���Ϊ����ֵ���ڱ�
//public:
//	hashChainsWithTail(int n = 11, int max = 100);
//	~hashChainsWithTail();
//	int hash(T& t);
//	int search( T& t);
//	void insert( T& t);
//	void erase( T& t);
//	void output();
//
//};
//
//
//template<class T>
//hashChainsWithTail<T>::hashChainsWithTail(int n, int max)
//{
//	size = n;
//	Max = max;
//	chain = new LinkedList<T>[size];
//	theonlyTail = new Node<T>(Max);
//	for (int i = 0; i < size; i++)
//		chain[i].end = theonlyTail;
//}
//
//template<class T>
//hashChainsWithTail<T>::~hashChainsWithTail()
//{
//	delete[] chain;
//}
//
//template<class T>
//int hashChainsWithTail<T>::hash(T& t)
//{
//	return t*3+7;
//}
//
//template<class T>
//int hashChainsWithTail<T>::search( T& t)//�ҵ���ű��
//{
//	int i = hash(t) % size;
//	return i;
//}
//
//template<class T>
//void hashChainsWithTail<T>::insert( T& t)
//{
//	int i = search(t);
//	if (chain[i].first == nullptr) {//��
//		chain[i].first = new Node<T>(t);
//		chain[i].first->next = chain[i].end;
//	}
//	else {
//		Node<T>* temp = new Node<T>(t);
//		Node<T>* cur = chain[i].first;
//		while (cur != nullptr) {
//			if (cur->data<t && cur->next->data>t) {//����С����
//				temp->next = cur->next;
//				cur->next = temp;
//				break;
//			}
//			cur = cur->next;
//		}
//	}
//}
//
//template<class T>
//void hashChainsWithTail<T>::erase( T& t)
//{
//	int i = search(t);
//	if (chain[i].first == nullptr) {
//		cout << "��Ԫ�ز�����" << endl;
//		return;
//	}
//	if (chain[i].first->data == t) {//��һ��Ԫ�ؾ���
//		Node<T>* temp = chain[i].first;
//		chain[i].first = chain[i].first->next;
//		delete temp;
//	}
//	else {
//		int k = chain[i].end->data;
//		chain[i].end->data = t;
//		Node<T>* cur = chain[i].first;
//		while (true) {
//			if (cur->next->data == t)
//				break;
//			cur = cur->next;
//		}
//		if (cur->next == chain[i].end) {
//			cout<< "��Ԫ�ز�����" << endl;
//		}
//		else {
//			Node<T>* temp = cur->next;
//			cur->next = cur->next->next;
//			delete temp;
//		}
//		chain[i].end->data = k;
//	}
//}
//
//template<class T>
//void hashChainsWithTail<T>::output()
//{
//	cout << "���ɢ�У�" << endl;
//	for (int i = 0; i < size; i++) {
//		cout << i << ":";
//		Node<T>* cur = chain[i].first;
//		if (chain[i].first == nullptr) {
//			cout << endl;
//			continue;
//		}
//		while (cur != chain[i].end) {
//			cout << cur->data << " ";
//			cur = cur->next;
//		}
//		cout << endl;
//	}
//}
//
//int main() {
//	int size;
//	cout << "�������ϣ���ȣ�" << endl;
//	cin >> size;
//	hashChainsWithTail<int> t(size,100);
//	int temp;
//	cout << "������ɢ��Ԫ��" << endl;
//	for (int i = 0; i < size; i++) {
//		cin >> temp;
//		t.insert(temp);
//	}
//	t.output();
//	int a;
//	cout << "��Ҫɾ����Ԫ��Ϊ��" << endl;
//	cin >> a;
//	t.erase(a);
//	t.output();
//	cout << "��Ҫɾ����Ԫ��Ϊ��" << endl;
//	cin >> a;
//	t.erase(a);
//	t.output();
//	cout << "��Ҫ�����Ԫ��Ϊ��" << endl;
//	cin >> a;
//	t.insert(a);
//	t.output();
//}