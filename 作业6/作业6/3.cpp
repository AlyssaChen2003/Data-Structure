#include<iostream>
using namespace std;
//��Ϊ������α���������Ҫ�õ����У������ڴ���Ҫ����һ��������
//������

template<class T>
class Node {
public:
	T element;
	Node<T>* next;
	template<class T>
	friend class LinkedQueue;
public:
	Node(const T& t) {
		element = t;
		next = NULL;
	}
	Node() {

		next = NULL;
	}
};
template<class T>
class LinkedQueue {
public:
	LinkedQueue() { 
		front = rear = NULL; }
	LinkedQueue<T>& Add(const T& x);
	void Delete(T& x);//x�����洢ɾ��������





public:
	Node<T>* front;//��һ�������ף��ڵ�
	Node<T>* rear;//��β�ڵ�
};
//���в���
template<class T>
LinkedQueue<T>& LinkedQueue<T>::Add(const T& x) {
	Node<T>* p = new Node<T>;
	p->element = x;
	p->next = NULL;//����һ�ڵ㲢��ֵ
	if (front)rear->next = p;//��Ϊ�ն���
	else front  = p;
	rear = p;//�²���Ľڵ�һ��Ϊβ�ڵ�
	return *this;

}
//���в���
template<class T>
void LinkedQueue<T>::Delete(T& x) {
	if (front == NULL) {
		x = NULL;
		return ;
	}
	x = front->element;//���ݶ��׽ڵ�ֵ
	Node<T>* p = front;
	front = front->next;
	delete p;//�ͷ�ԭ���׵Ŀռ�

	return ;


}

//��������

template<class T>
class BinaryTreeNode {
public:
	BinaryTreeNode(const T& t) {
		data = t;
		_left = NULL;
		_right = NULL;
	}
	BinaryTreeNode(const T& t, BinaryTreeNode<T>* theleft, BinaryTreeNode<T>* theright) {
		data = t;
		_left = theleft;
		_right = theright;
	}
	T visit(BinaryTreeNode<T>* temp) {
		return temp->data;
	}
public:
	T data;
	BinaryTreeNode<T>* _left;//����
	BinaryTreeNode<T>* _right;//�Һ���
	template<class T>
	friend class BinaryTree;
};
template<class T>
class BinaryTree {
public:
	BinaryTreeNode<T>* root;//ָ�����ָ��
	int treeSize;//���Ľڵ����
	int width[100];
public:

	BinaryTree() {
		root = NULL;
		for(int i=0;i<100;i++)
		 width[i]=0;
		treeSize=0;
	}
	bool IsEmpty()const {
		return((root) ? false : true);
	}
	bool Root(T& x)const;
	void MakeTree(const T& element, BinaryTree<T>& left, BinaryTree<T>& right);
	int AllSize(BinaryTreeNode<T>* u,int& size) {
		if (u) {
			size++;
			AllSize(u->_left, size);
			AllSize(u->_right, size);
		}
		return size;
	};
	void preOrder(BinaryTreeNode<T>* u);
	void InOrder(BinaryTreeNode<T>* u);
	void PostOrder(BinaryTreeNode<T>* u);
	void change(BinaryTreeNode<T>* u);
	void Swaprlchild(BinaryTreeNode<T>*U);//�����������нڵ�ĵ���������
	int LeavesSize(BinaryTreeNode<T>*t,int &num);//ͳ�ƶ�����������Ҷ�ڵ�ĸ���
	int AllLeavesSize(BinaryTreeNode<T>* t);//������һ��������ȫ��Ҷ�ڵ����
	void levelOrder(BinaryTreeNode<T>* u);//�����˳�����������
	int widthofTree(BinaryTreeNode<T>* u,int deep);//��������Ŀ��
	void display(BinaryTreeNode<T>*root,int deep) {
		if (root)
		{
			display(root->_right, deep+1);
			for (int i = 1; i <=deep; i++) {
				cout << "\t";
			}
			cout << root->visit(root) << endl;
			display(root->_left, deep + 1);
		}

	}

};
//��ȡ���ڵ�����
template<class T>
bool BinaryTree<T>::Root(T& x)const {
	if (root)
	{
		x = root->data;
		return true;
	}
	else
		return false;
}
//������
template<class T>
void BinaryTree<T>::MakeTree(const T& element, BinaryTree<T>& left, BinaryTree<T>& right) {

	root = new BinaryTreeNode<T>(element, left.root, right.root);
	left.root = right.root = NULL;
}
//���õݹ��˼�������������������������������Լ�������
template<class T>
void BinaryTree<T>::preOrder(BinaryTreeNode<T>* u) {
	if (u != NULL) {
		visit(u);
		preOrder(u->_left);
		preOrder(u->_right);
	}
}
template<class T>
void BinaryTree<T>::InOrder(BinaryTreeNode<T>* u) {
	if (u != NULL) {

		InOrder(u->_left);
		visit(u);
		InOrder(u->_right);
	}
}
template<class T>
void BinaryTree<T>::PostOrder(BinaryTreeNode<T>* u) {
	if (u != NULL) {

		PostOrder(u->_right);
		visit(u);
		PostOrder(u->_left);
	}
}
//����������-��Ҷ����������
template<class T>
void BinaryTree<T>::levelOrder(BinaryTreeNode<T>* t) {
	LinkedQueue<BinaryTreeNode<T>*>Q;
	while (t)
	{
		cout<<t->data<<" ";
		//��t�������Һ��ӷֱ���������
		if (t->_left) Q.Add(t->_left);//�����Ⲣû�а�f���뵽Q�У�fʱc������
		if (t->_right) Q.Add(t->_right);
		Q.Delete(t);
	}//t=NULLʱ�˳�ѭ��

}

//int YeSize();//ͳ�ƶ�����������Ҷ�ڵ�ĸ���

/*int BinaryTree<T>::YeSize() {
	BinaryTreeNode<T>* t;//t�����ĸ�
	int count = 0;
	LinkedQueue<BinaryTreeNode<T>*>Q;
	while (t) {
		bool f = false, g = false;
		if (t->_left) Q.Add(t->_left);
		else f = true;
		if (t->_right) Q.Add(t->_right);
		else g = true;
		if (f && g) {
			count++;
		}
		Q.Delete(t);
	}
}*/
template<class T>
int BinaryTree<T>::LeavesSize(BinaryTreeNode<T>*t,int& num) {
	if (t && (!t->_left) && (!t->_right)) {
		num++;
	}
	return num;
}
template<class T>
int BinaryTree<T>::AllLeavesSize(BinaryTreeNode<T>* root) {
	if (root) {
		LeavesSize(root,treeSize);
		AllLeavesSize(root->_left);
		AllLeavesSize(root->_right);
	}
	return treeSize;
}

//���һ���ڵ�����Һ��ӽ���
template<class T>
void BinaryTree<T>::change(BinaryTreeNode<T>* root)
{
	BinaryTreeNode<T>* temp;
	if (root) {
		temp = root->_left;
		root->_left = root->_right;
		root->_right = temp;
	}
}
//���õݹ�������нڵ����Һ��ӵĽ���
template<class T>
void BinaryTree<T>::Swaprlchild(BinaryTreeNode<T>*root) {
	if (root) {
		change(root);
		Swaprlchild(root->_left);
		Swaprlchild(root->_right);
	}
}


//��������Ŀ�ȣ���ͬһ��������Ľڵ���
template<class T>
int BinaryTree<T>::widthofTree(BinaryTreeNode<T>* u,int deep) {

	if (u) {
		width[deep]++;
		widthofTree(u->_left, deep+1);
		widthofTree(u->_right, deep+1);

	}
	int count = 0;
	int Size=0;
	int _s = AllSize( u, Size);
	for (int i = 1; i <=_s ; i++) {
		if (count <= width[i])
			count = width[i];
	}
	return count;
}
//int main() {
//	BinaryTree<char>tree;
//	BinaryTreeNode<char>* j = new BinaryTreeNode<char>('j');
//	BinaryTreeNode<char>* i = new BinaryTreeNode<char>('i');
//	BinaryTreeNode<char>* h = new BinaryTreeNode<char>('h');
//	BinaryTreeNode<char> * g = new BinaryTreeNode<char>('g',i,j);
//	BinaryTreeNode<char>* f = new BinaryTreeNode<char>('f', g, h);
//	BinaryTreeNode<char>* e = new BinaryTreeNode<char>('e');
//	BinaryTreeNode<char>* d = new BinaryTreeNode<char>('d');
//	BinaryTreeNode<char>* c = new BinaryTreeNode<char>('c', NULL, f);
//	BinaryTreeNode<char>* b = new BinaryTreeNode<char>('b', d, e);
//	BinaryTreeNode<char>* a = new BinaryTreeNode<char>('a', b, c);
//	tree.root = a;
//	cout<<tree.AllLeavesSize(a);
//	cout << endl;
//	int deep = 1;
//	tree.display(a, deep);
//	cout << endl;
//	cout << endl;
//	cout <<"------------------------------------------------------------" <<endl;
//	tree.Swaprlchild(a);
//
//	tree.display(a, deep);
//	cout << endl;
//
//	cout << tree.widthofTree(a, deep);
//	cout << endl;
//
//	tree.levelOrder(a);
//	cout<<endl;
//
//	int size=0;
//	cout<<tree.AllSize(a,size)<<endl;
//
//
//}