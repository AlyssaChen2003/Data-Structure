#include<iostream>
#include<iomanip>
#include<queue>
#include<ctime>
#include<stack>
using namespace std;
struct Node {
	int data;
	int bf;//平衡因子
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
		Node* A = NULL;//平衡因子绝对值为2的节点
		Node* p = NULL;
		Node* q = root;
		while (q)
		{
			if (q->bf == -1 || q->bf == 1)//不平衡,while过后aroot将指向最近的可疑不平衡的节点的根，A指向可疑不平衡节点
			{
				A = q;
				if (p)
				{
					Aroot = p;
				}
			}
			p = q;//向下移动
			if (x == q->data)
				return false;//找到要插入的值，返回失败

			if (x < q->data)//相当于查找x
			{
				q = q->left;
				continue;
			}
			if (x > q->data)
			{
				q = q->right;
				continue;
			}
		}//此时应该找到对应的位置了


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

		if (A == NULL) //说明没有出现过不平衡现象，纠正后直接返回
		{
			correctbf(root);
			return true;
		}
		else
		{
			if ((x < A->data && A->bf == -1) || (x > A->data && A->bf == 1))//插入后平衡因子变为0的情况，不会导致不平衡的出现
			{
				correctbf(root);
				return true;
			}
			else
			{
				int flag = 0;
				if (Aroot == A)//根处不平衡
					flag = 3;
				if (Aroot->left == A)//根的左孩子不平衡
					flag = 1;
				if (Aroot->right == A)//根的右孩子不平衡
					flag = 2;
				if (x < A->data && x < A->left->data)
				{
					//LL
					Node* At = A->left;//指向不平衡节点的左孩子
					Node* Atr = At->right;//指向不平衡节点的左孩子的右孩子
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
					Node* B = A->left;//B为次旋转中心
					//以B为旋转中心左旋
					Node* Bt = B->right;
					Node* Btl = Bt->left;
					B->right = Btl;
					Bt->left = B;
					B = Bt;


					//以A为旋转中心右旋
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
				//R型与L型不平衡纠正方法对称
				if (x > A->data && x < A->right->data) {
					//RL
					Node* B = A->right;//B为次旋转中心
					//以B为旋转中心右旋
					Node* Bt = B->left;
					Node* Btr = Bt->right;
					B->left = Btr;
					Bt->right = B;
					B = Bt;
					//以A为旋转中心左旋
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
					//以A为旋转中心左旋
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
	void correctbf(Node* t) //纠正树高
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
	int getHeight(Node* t)//计算局部树高即深度
	{
		Node* tmp = t;
		if (tmp) {
			int HL = getHeight(tmp->left);
			int HR = getHeight(tmp->right);
			return  (HL >= HR) ? (HL + 1) : (HR + 1);//算上tmp自己要加一
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
	Node* getCloestLeaf()//所在层数最低的叶节点
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

			if (!q.front()->left && !q.front()->right)//到顶
			{
				return q.front();
			}

			q.pop();
		}
	}
	int getheight()//没有调用递归函数，复杂度为线性级别
	{
		int height = 0;
		Node* t = root;
		while (t)
		{
			height++;
			if (t->bf == 0 || t->bf == 1)//左边不低于右边
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