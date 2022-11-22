#include<iostream>
#include<iomanip>
#include<queue>
#include<ctime>
#include<stack>
using namespace std;
struct Node {
	int data;
	int bf;//ƽ������
	Node* left;
	Node* right;
	Node() {
		data = 0;
		bf = 0;
		left = right = NULL;
	}
	Node(int x, int y = 0) {
		data = x;
		bf = y;
		left = right = NULL;
	}
	Node(int x, Node* L, Node* R, int y = 0)
	{
		data = x;
		bf = y;
		left = L;
		right = R;
	}
};

class avlTree {
	Node* root;
	stack<int> s;

public:
	avlTree() {
		root = NULL;
	}
	Node* getRoot()
	{
		return root;
	}
	bool find(int& x)
	{
		Node* tmp = root;
		while (tmp) {
			if (tmp->data = x)
				return true;
			if (x < tmp->data)
			{
				tmp = tmp->left;
			}
			if (x > tmp->data)
			{
				tmp = tmp->right;
			}
		}
		return false;
	}
	bool insert(int& x)
	{
		Node* Aroot = root;//
		Node* A = NULL;//ƽ�����Ӿ���ֵΪ2�Ľڵ�
		Node* p = NULL;
		Node* q = root;
		while (q)
		{
			if (q->bf == -1 || q->bf == 1)//��ƽ��,while����aroot��ָ������Ŀ��ɲ�ƽ��Ľڵ�ĸ���Aָ����ɲ�ƽ��ڵ�
			{
				A = q;
				if (p)
				{
					Aroot = p;
				}
			}
			p = q;//�����ƶ�
			if (x == q->data)
				return false;//�ҵ�Ҫ�����ֵ������ʧ��

			if (x < q->data)//�൱�ڲ���x
			{
				q = q->left;
				continue;
			}
			if (x > q->data)
			{
				q = q->right;
				continue;
			}
		}//��ʱӦ���ҵ���Ӧ��λ����


		Node* tmp = new Node(x);
		if (root) {
			if (x < p->data)
			{
				p->left = tmp;
			}
			else
				p->right = tmp;
		}
		else
		{
			root = tmp;
			return true;
		}

		if (A == NULL) //˵��û�г��ֹ���ƽ�����󣬾�����ֱ�ӷ���
		{
			correctbf(root);
			return true;
		}
		else
		{
			if ((x < A->data && A->bf == -1) || (x > A->data && A->bf == 1))//�����ƽ�����ӱ�Ϊ0����������ᵼ�²�ƽ��ĳ���
			{
				correctbf(root);
				return true;
			}
			else
			{
				int flag = 0;
				if (Aroot == A)//������ƽ��
					flag = 3;
				if (Aroot->left == A)//�������Ӳ�ƽ��
					flag = 1;
				if (Aroot->right == A)//�����Һ��Ӳ�ƽ��
					flag = 2;
				if (x < A->data && x < A->left->data)
				{
					//LL
					Node* At = A->left;//ָ��ƽ��ڵ������
					Node* Atr = At->right;//ָ��ƽ��ڵ�����ӵ��Һ���
					A->left = Atr;
					At->right = A;
					switch (flag) {

					case 1:
						Aroot->left = At;
						break;
					case 2:
						Aroot->right = At;
						break;
					case 3:
						root = At;
						break;
					}
					correctbf(root);
					return true;
				}
				if (x < A->data && x > A->left->data)
				{//LR
					Node* B = A->left;//BΪ����ת����
					//��BΪ��ת��������
					Node* Bt = B->right;
					Node* Btl = Bt->left;
					B->right = Btl;
					Bt->left = B;
					B = Bt;


					//��AΪ��ת��������
					A->left = B;
					Node* At = A->left;
					Node* Atr = At->right;
					A->left = Atr;
					At->right = A;
					A = At;
					switch (flag) {

					case 1:
						Aroot->left = A;
						break;
					case 2:
						Aroot->right = A;
						break;
					case 3:
						root = A;
						break;
					}

					correctbf(root);
					return true;
				}
				//R����L�Ͳ�ƽ����������Գ�
				if (x > A->data && x < A->right->data) {
					//RL
					Node* B = A->right;//BΪ����ת����
					//��BΪ��ת��������
					Node* Bt = B->left;
					Node* Btr = Bt->right;
					B->left = Btr;
					Bt->right = B;
					B = Bt;
					//��AΪ��ת��������
					A->right = B;
					Node* At = A->right;
					Node* Atl = At->left;
					A->right = Atl;
					At->left = A;
					A = At;
					switch (flag) {

					case 1:
						Aroot->left = A;
						break;
					case 2:
						Aroot->right = A;
						break;
					case 3:
						root = A;
						break;
					}

					correctbf(root);
					return true;
				}
				if (x > A->data && x > A->right->data) {
					//RR
					//��AΪ��ת��������
					Node* At = A->right;
					Node* Atl = At->left;
					A->right = Atl;
					At->left = A;
					A = At;

					switch (flag) {

					case 1:
						Aroot->left = A;
						break;
					case 2:
						Aroot->right = A;
						break;
					case 3:
						root = A;
						break;
					}

					correctbf(root);
					return true;
				}
			}
		}
		return false;
	}
	void correctbf(Node* t) //��������
	{
		if (t)
		{
			int HL = getHeight(t->left);
			int HR = getHeight(t->right);
			if (HL - HR < -2 || HL - HR > 2) {
				cout << "WRONG" << endl;
			}
			t->bf = HL - HR;
			correctbf(t->left);
			correctbf(t->right);
		}
	}
	int getHeight(Node* t)//����ֲ����߼����
	{
		Node* tmp = t;
		if (tmp) {
			int HL = getHeight(tmp->left);
			int HR = getHeight(tmp->right);
			return  (HL >= HR) ? (HL + 1) : (HR + 1);//����tmp�Լ�Ҫ��һ
		}
		else
		{
			return 0;
		}
	}
	int visit(Node* t)
	{
		if (t)
		{
			return t->data;
		}
		else
		{
			return 0;
		}
	}
	void show(Node* root, int k)
	{
		if (root)
		{
			show(root->right, k + 1);
			for (int i = 0; i < k; i++)
			{
				cout << '\t';
			}
			cout << visit(root) << endl;
			cout << endl;
			show(root->left, k + 1);
		}
	}
	void outputPath(Node* root, Node* p) {
		if (root == p)
			s.push(root->data);
		if (root->left == p)
			s.push(root->left->data);
		if (root->right == p)
			s.push(root->right->data);
		if (root->right != p && root->left != p && root != p) {
			if (root->right != NULL)
				outputPath(root->right, p);
			if (root->left != NULL)
				outputPath(root->left, p);

		}
	}
	void output() {
		while (!s.empty()) {
			cout << s.top() << " ";
			s.pop();
		}
	}
	Node* getCloestLeaf()//���ڲ�����͵�Ҷ�ڵ�
	{
		queue<Node*> q;
		q.push(root);
		while (!q.empty())
		{
			if (q.front()->left)
			{
				q.push(q.front()->left);
			}

			if (q.front()->right)
			{
				q.push(q.front()->right);
			}

			if (!q.front()->left && !q.front()->right)//����
			{
				return q.front();
			}

			q.pop();
		}
	}
	int getheight()//û�е��õݹ麯�������Ӷ�Ϊ���Լ���
	{
		int height = 0;
		Node* t = root;
		while (t)
		{
			height++;
			if (t->bf == 0 || t->bf == 1)//��߲������ұ�
			{
				t = t->left;
			}
			else
			{
				t = t->right;
			}
		}
		return height;
	}
};

int main()
{
	srand((int)time(0));
	int n;
	cin >> n;
	avlTree tree;
	for (int i = 0; i < n; i++)
	{
		int x = rand() % 100;
		cout << x << " ";
		tree.insert(x);
	}
	cout << endl;
	tree.show(tree.getRoot(), 0);
	cout << endl;

	tree.outputPath(tree.getRoot(), tree.getCloestLeaf());
	tree.output();
}