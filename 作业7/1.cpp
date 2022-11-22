#include<iostream>
#include<string>
#include<limits>
#include<ctime>
using namespace std;
class Empty
{
public:

	Empty(string theMessage = "Empty!")
	{
		message = theMessage;
	}
	void output()
	{
		cout << message << endl;
	}
	string message;
};
template<class T>
class MaxHeap
{
public:
	MaxHeap(int MaxHeapSize, T minElement, T maxElement);
	~MaxHeap() { delete[] heap; }
	int Size()const
	{
		return CurrentSize;
	}
	T Max()const
	{
		if (CurrentSize == 0)
			throw Empty();
		return heap[1];
	}
	MaxHeap<T>& Insert(const T& x);
	MaxHeap<T>& DeleteMax(T& x);
	void Initialize(T a[], int size, int minElement, int maxElement);
	void output(ostream& out);
	void deActivateArray()//重置清零堆
	{
		heap = NULL; MaxSize = CurrentSize = 0;
	}
	int MaxSize, CurrentSize;
	T MaxElement,  // all must be <= MaxElement
		MinElement;  // all must be >= MinElement
	T* heap;
};
template<class T>
void MaxHeap<T>::output(ostream& out)
{
	for (int i = 1; i <= CurrentSize; i++)
		out << heap[i] << " ";
	out << endl;
}

template<class T>
MaxHeap<T>::MaxHeap(int MaxHeapSize, T maxElement,T minElement)  //(1)
{
	MaxSize = MaxHeapSize;
	MinElement = minElement;
	MaxElement = maxElement;
	CurrentSize = 0;
	heap = new T[2 * (MaxSize + 1)];                            //(2)
}
template<class T>
MaxHeap<T>& MaxHeap<T>::Insert(const T& x)
{
	int i = ++CurrentSize;
	while (x > heap[i / 2])  //不用再比较是否到根
	{
		heap[i] = heap[i / 2];//把元素向下移动
		i /= 2;//i移向父亲节点
	}
	heap[i] = x;
	return*this;
}

template<class T>
MaxHeap<T>& MaxHeap<T>::DeleteMax(T& x)
{
	x = heap[1];//头
	T y = heap[CurrentSize];//尾
	heap[CurrentSize--] = MinElement;
	int i = 1, ci = 2;
	while (ci <= CurrentSize)//区间里循环
	{
		if (heap[ci] < heap[ci + 1])  //不用再判断是否为最后一个叶子节点
			ci++;
		if (y >= heap[ci])
			break;
		heap[i] = heap[ci];
		//向子树继续遍历
		i = ci;
		ci *= 2;
	}
	heap[i] = y;
	return *this;
}
template<class T>
void MaxHeap<T>::Initialize(T a[], int size, int minElement, int maxElement)
{
	//初始化一个完全二叉树
	delete[]heap;
	heap = a;
	MaxElement = maxElement;
	MinElement = minElement;
	CurrentSize = size;
	heap[0] = MaxElement;//(4)
	for (int i = size + 1; i <= 2 * size + 1; i++)                  //(5)
		heap[i] = MinElement;
	MaxSize = 2 * size + 1;
	//从最后一个内部节点开始，一直到根，对每个子树进行堆重整
	for (int i = CurrentSize / 2; i >= 1; i--)                     //(3)
	{
		T y = heap[i]; 
		
		//为该元素寻找位置
		int c = 2 * i; //孩子c的双亲是元素y的位置
		while (c <= CurrentSize)
		{
			//heap[c]应该是兄弟中较大者
			if (c < CurrentSize && heap[c] < heap[c + 1])
				c++;


			//是否能将元素y放在heap[child/2]的位置
			if (y >= heap[c])
				break;//是
			//否
			heap[c / 2] = heap[c];//把孩子上移一层
			c *= 2;//移到下一层
		}
		heap[c / 2] = y;
	}
}

template<class T>
ostream& operator<<(ostream& out, MaxHeap<T>& x)
{
	x.output(out);
	return out;
}
template<class T>
void heapsort(T a[], int n, T min, T max)
{
	MaxHeap<T> H(n, min, max);//创建新堆放排序好的元素
	H.Initialize(a, n, min, max);
	T x;
	for (int i = n - 1; i >= 1; i--)
	{
		H.DeleteMax(x);
		H.heap[i + 1] = x;//最大的元素往后排列
	}
	H.deActivateArray();
}
//int main()
//{
//	int n, i;
//	cin >> n;
//	srand((int)time(0));
//	int* a = new int[2 * (n + 1)];
//	int min = INT_MAX;
//	int max = INT_MIN;
//	for (i = 1; i <= n; i++)
//	{
//		a[i] = rand() % 100;
//		if (min > a[i])
//			min = a[i];
//		if (max < a[i])
//			max = a[i];
//	}
//	heapsort<int>(a, n, min, max);
//	for (i = 1; i <= n; i++)
//		cout << a[i] << " ";
//}
