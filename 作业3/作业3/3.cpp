#include<iostream>
#include<istream>
using namespace std;
template <class T>
class Node//定义结点，同时重载符号>、<方便后续类操作
{
public:
	int x;
	int y;
	T data;
	Node *next;
	Node(int a = 0,int b = 0, T t = 0)
	{
		x = a;
		y = b;
		data = t;
		next = NULL;
	}
	Node(Node<T> &t)
	{
		x = t.x;
		y = t.y;
		data = t.data;
		next = t.next;
	}
	bool operator > (Node<T> t)
	{
		if (x < t.x || (x == t.x&&y <= t.y))
			return false;
		else
			return true;
	}
	bool operator < (Node<T> t)
	{
		if (x > t.x || (x == t.x&&y >= t.y))
			return false;
		else
			return true;
	}
	bool operator == (Node<T> t)
	{
		if (x == t.x&&y == t.y)
			return true;
		else
			return false;
	}
	void operator = (Node<T> t)
	{
		x = t.x;
		y = t.x;
		this.data = t.data;
		this.next = t.next;
	}
};
template <class T>//定义链表矩阵
class linkedMatrixs
{
public:
	int xs;
	int ys;
	Node<T> *head;
	linkedMatrixs(int a = 0, int b = 0) 
	{
		xs = a;
		ys = b; 
		head = NULL;
	}

	void clear()
	{
		Node<T>* temp = head;
		while (temp != NULL)//逐个清空结点
		{
			head = head->next;
			delete temp;
			temp = head;
		}
	}
	bool get(int x, int y, T&target) //获得指定位置元素值
	{
		Node<T>* temp = head;
		while (temp != NULL)
		{
			if (temp->x == x && temp->y == y)
			{
				target = temp->data;
				break;
			}
			temp = temp->next;
		}
		if (temp == NULL)
			return false;
		else
			return true;
	}
	void set(int x, int y, T target) //给矩阵对应位置赋值
	{
		Node<T>*temp = new Node<T>(x, y, target);
		if (head == NULL) 
		{
			head = temp;
			return;
		}
		if ((*temp) < (*head)) //存入的元素行列值小于头结点
		{
			temp->next = head;
			head = temp;
			return;
		}
		Node<T>*curr = head;
		while (curr != NULL)
		{
			if ((*curr) == (*temp))
			{
				curr->data = target;
				return;
			}
			if (curr->next == NULL && (*curr) < (*temp)) 
			{
				curr->next = temp;
				return;
			}
			if ((*curr) < (*temp) && (*(curr->next)) > (*temp))
			{
				temp->next = curr->next;
				curr->next = temp;
				return;
			}
			curr = curr->next;
		}
	}
	
	linkedMatrixs<T>& add (linkedMatrixs<T> &m)
	{
		linkedMatrixs<T> result;
		if (xs != m.xs || ys != m.ys)
		{
			cout << "行列不对应" << endl;
			return result;
		}
		result.xs = xs;
		result.ys = ys;
		for (int i = 1; i <= xs; i++) 
		{
			for (int j = 1; j <= ys; j++) 
			{
				T temp1 = 0, temp2 = 0;
				this->get(i, j, temp1);
				m.get(i, j, temp2);
				if (temp1 + temp2 != 0)
					result.set(i, j, temp1 + temp2);
			}
		}
		result.output();
		return result;
	}
	linkedMatrixs<T>& substract (linkedMatrixs<T> &m)
	{
		linkedMatrixs<T> result;
		if (xs != m.xs || ys != m.ys)
		{
			cout << "行列不对应" << endl;
			return result;
		}
		result.xs = xs;
		result.ys = ys;
		for (int i = 1; i <= xs; i++) 
		{
			for (int j = 1; j <= ys; j++) 
			{
				T temp1 = 0, temp2 = 0;
				this->get(i, j, temp1);
				m.get(i, j, temp2);
				if (temp1 - temp2 != 0)
					result.set(i, j, temp1 - temp2);
			}
		}
		result.output();
		return result;
	}
	linkedMatrixs<T>& multiply (linkedMatrixs<T> &m)
	{   
		linkedMatrixs<T> result;
		if (this->ys != m.xs)
		{
			cout << "行列不对应" << endl;
			return result;
		}
		result.xs = ys;
		result.ys = m.xs;
		for (int i = 1; i <= result.xs; i++)
		{
			for (int j = 1; j <= result.ys; j++)
			{
				T temp = 0;
				for (int k = 1; k <= this->ys; k++)
				{
					T item1, item2;
					if (this->get(i, k, item1) && m.get(k, j, item2))
					{
						temp += item1 * item2;
					}
				}
				if (temp != 0)
				{
					result.set(i, j, temp);
				}
			}
		}
		result.output();
		return result;
	}
	
	void output()
	{
		for (int i = 1; i <= xs; i++)
		{
			for (int j = 1; j <= ys; j++)
			{
				T temp;
				if (this->get(i, j, temp))
				{
					cout << temp << " ";
				}
				else
				{
					cout << 0 << " ";
				}
			}
			cout << endl;
		}
	}
	void input() {
		int n;
		cout << "元素个数 ";
		cin >> n;
		for (int k = 0; k < n; k++) {
			int i, j;
			T t;
			cin >> i >> j >> t;
			this->set(i, j, t);

		}
	}
};
template <class T>
istream& operator>>(istream& in,linkedMatrixs<T>& x){
	int numberofterms,row,col;
	cout<<"行，列，元素数目"<<endl;
	in>>row>>col>>numberofterms;
	if(numberofterms<=row*col){
	 x.xs=row;
	 x.ys=col;
	for (int k = 0; k < numberofterms; k++) {
			int row, col;
			T t;
			cout<<"第"<<k+1<<"个元素所在行，列，元素值："<<endl;
			in >>row >> col >> t;
			x.set(row, col, t);
	}
	return in;
	}
}




int main()
{
	linkedMatrixs<int>m, m1;
	cin>>m;
	cin>>m1;
	cout << endl;
	cout<<"matrix m: "<<endl;
	m.output();
	cout<<"matrix m1:"<<endl;
	m1.output();

	cout<<"multiply:"<<endl;
    m.multiply(m1);

	cout<<"add:"<<endl;
	m.add(m1);	

	cout<<"substract:"<<endl;
	m.substract(m1);
	
	}

	

	
//
//3 3 4
//1 1 1
//2 2 2
//2 3 4
//3 1 -4
//3 3 4
//1 3 -2
//2 3 -5
//3 1 8
//3 2 -6