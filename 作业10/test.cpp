//#include<iostream>
//#include<stack>
//using namespace std;
//
//template <class T>
//class Node {
//public:
//
//	Node<T>* lc, * rc;
//	T data;
//
//
//	Node<T>(T x) {
//		this->data = x;
//	}
//	
//	Node<T>() {
//		lc = rc = NULL;
//	}
//};
//template <class T>
//class Tree {
//public:
//	stack<T> s;
//    Node<T> *root;
//	Tree<T>() {
//		root = NULL;
//		root->lc = NULL;
//		root->rc = NULL;
//	}
//    Tree<T>(Node<T>* t, Node<T>* l, Node<T>* r) {
//		root->lc = l;
//		root->rc = r;
//		root = t;
//	}
//	void outputPath(Node<T>* root, Node<T>* p) {
//		if (root == p)
//			s.push(root->data);
//		if (root->lc == p)
//			s.push(root->lc->data);
//		if (root->rc == p)
//			s.push(root->rc->data);
//		if (root->rc != p && root->lc != p && root != p) {
//			if (root->rc != NULL)
//				outputPath(root->rc, p);
//			if (root->lc != NULL)
//				outputPath(root->lc, p);
//
//		}
//	}
//	void output() {
//		while (!s.empty()) {
//			cout << s.top() << " ";
//			s.pop();
//		}
//	}
//	int visit(Node<T>* t)
//	{
//		if (t)
//		{
//			return t->data;
//		}
//		else
//		{
//			return 0;
//		}
//	}
//	void show(Node<T>* root, int k)
//	{
//		if (root)
//		{
//			show(root->rc, k + 1);
//			for (int i = 0; i < k; i++)
//			{
//				cout << '\t';
//			}
//			cout << visit(root) << endl;
//			cout << endl;
//			show(root->lc, k + 1);
//		}
//	}
//
//};
//int main() {
//	
//	Node<char> *a, * b, * d, * e, * g, * h, * j, * k;
//	a->data = 'a';
//	b->data = 'b';
//	d->data = 'd';
//	e->data = 'e';
//	g->data = 'g';
//	h->data = 'h';
//	j->data = 'j';
//	k->data = 'k';
//
//	
//	Tree<char> tree(a,b,NULL);
//	b->lc = d;
//	b->rc = e;
//	d->lc = g;
//	d->rc = h;
//	h->lc = j;
//	h->rc = k;
//	tree.show(a, 0);


	

	




