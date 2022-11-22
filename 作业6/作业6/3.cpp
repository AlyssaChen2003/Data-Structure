#include<iostream>
using namespace std;
//因为后续层次遍历函数需要用到队列，所以在此需要声明一个队列类
//队列类

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
	void Delete(T& x);//x用来存储删除的数据





public:
	Node<T>* front;//第一个（队首）节点
	Node<T>* rear;//队尾节点
};
//入列操作
template<class T>
LinkedQueue<T>& LinkedQueue<T>::Add(const T& x) {
	Node<T>* p = new Node<T>;
	p->element = x;
	p->next = NULL;//创建一节点并赋值
	if (front)rear->next = p;//不为空队列
	else front  = p;
	rear = p;//新插入的节点一定为尾节点
	return *this;

}
//出列操作
template<class T>
void LinkedQueue<T>::Delete(T& x) {
	if (front == NULL) {
		x = NULL;
		return ;
	}
	x = front->element;//备份队首节点值
	Node<T>* p = front;
	front = front->next;
	delete p;//释放原队首的空间

	return ;


}

//二叉树类

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
	BinaryTreeNode<T>* _left;//左孩子
	BinaryTreeNode<T>* _right;//右孩子
	template<class T>
	friend class BinaryTree;
};
template<class T>
class BinaryTree {
public:
	BinaryTreeNode<T>* root;//指向根的指针
	int treeSize;//树的节点个数
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
	void Swaprlchild(BinaryTreeNode<T>*U);//交换二叉树中节点的的左右子树
	int LeavesSize(BinaryTreeNode<T>*t,int &num);//统计二叉树中所有叶节点的个数
	int AllLeavesSize(BinaryTreeNode<T>* t);//借助上一个函数求全部叶节点个数
	void levelOrder(BinaryTreeNode<T>* u);//按层次顺序遍历二叉树
	int widthofTree(BinaryTreeNode<T>* u,int deep);//求二叉树的宽度
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
//获取根节点数据
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
//创建树
template<class T>
void BinaryTree<T>::MakeTree(const T& element, BinaryTree<T>& left, BinaryTree<T>& right) {

	root = new BinaryTreeNode<T>(element, left.root, right.root);
	left.root = right.root = NULL;
}
//利用递归的思想完成先序遍历，中序遍历，后序遍历以及逐层遍历
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
//逐层遍历，根-》叶，从左至右
template<class T>
void BinaryTree<T>::levelOrder(BinaryTreeNode<T>* t) {
	LinkedQueue<BinaryTreeNode<T>*>Q;
	while (t)
	{
		cout<<t->data<<" ";
		//将t的左孩子右孩子分别插入入队列
		if (t->_left) Q.Add(t->_left);//跳到这并没有把f加入到Q中，f时c的左孩子
		if (t->_right) Q.Add(t->_right);
		Q.Delete(t);
	}//t=NULL时退出循环

}

//int YeSize();//统计二叉树中所有叶节点的个数

/*int BinaryTree<T>::YeSize() {
	BinaryTreeNode<T>* t;//t是树的根
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

//完成一个节点的左右孩子交换
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
//利用递归完成所有节点左右孩子的交换
template<class T>
void BinaryTree<T>::Swaprlchild(BinaryTreeNode<T>*root) {
	if (root) {
		change(root);
		Swaprlchild(root->_left);
		Swaprlchild(root->_right);
	}
}


//求二叉树的宽度，即同一层次上最多的节点数
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