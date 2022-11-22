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
	void deActivateArray()//���������
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
	while (x > heap[i / 2])  //�����ٱȽ��Ƿ񵽸�
	{
		heap[i] = heap[i / 2];//��Ԫ�������ƶ�
		i /= 2;//i�����׽ڵ�
	}
	heap[i] = x;
	return*this;
}

template<class T>
MaxHeap<T>& MaxHeap<T>::DeleteMax(T& x)
{
	x = heap[1];//ͷ
	T y = heap[CurrentSize];//β
	heap[CurrentSize--] = MinElement;
	int i = 1, ci = 2;
	while (ci <= CurrentSize)//������ѭ��
	{
		if (heap[ci] < heap[ci + 1])  //�������ж��Ƿ�Ϊ���һ��Ҷ�ӽڵ�
			ci++;
		if (y >= heap[ci])
			break;
		heap[i] = heap[ci];
		//��������������
		i = ci;
		ci *= 2;
	}
	heap[i] = y;
	return *this;
}
template<class T>
void MaxHeap<T>::Initialize(T a[], int size, int minElement, int maxElement)
{
	//��ʼ��һ����ȫ������
	delete[]heap;
	heap = a;
	MaxElement = maxElement;
	MinElement = minElement;
	CurrentSize = size;
	heap[0] = MaxElement;//(4)
	for (int i = size + 1; i <= 2 * size + 1; i++)                  //(5)
		heap[i] = MinElement;
	MaxSize = 2 * size + 1;
	//�����һ���ڲ��ڵ㿪ʼ��һֱ��������ÿ���������ж�����
	for (int i = CurrentSize / 2; i >= 1; i--)                     //(3)
	{
		T y = heap[i]; 
		
		//Ϊ��Ԫ��Ѱ��λ��
		int c = 2 * i; //����c��˫����Ԫ��y��λ��
		while (c <= CurrentSize)
		{
			//heap[c]Ӧ�����ֵ��нϴ���
			if (c < CurrentSize && heap[c] < heap[c + 1])
				c++;


			//�Ƿ��ܽ�Ԫ��y����heap[child/2]��λ��
			if (y >= heap[c])
				break;//��
			//��
			heap[c / 2] = heap[c];//�Ѻ�������һ��
			c *= 2;//�Ƶ���һ��
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
	MaxHeap<T> H(n, min, max);//�����¶ѷ�����õ�Ԫ��
	H.Initialize(a, n, min, max);
	T x;
	for (int i = n - 1; i >= 1; i--)
	{
		H.DeleteMax(x);
		H.heap[i + 1] = x;//����Ԫ����������
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
