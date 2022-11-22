#include<iostream>
using namespace std;
template<typename T>
class HashTable {
private:	int size;	
			T* items;	
			bool * neverused;
public:	
	HashTable(int n) {		
			size = n; 		
			items = new T[size];		
			neverused = new bool[size];		
			for (int k = 0; k < size; k++) {			
				items[k] = 0;			
				neverused[k] = 1;//��ʼ��ʱneverusedΪtrue		
			}	
		}	
		HashTable(const HashTable<T>&target) {//��������		
			size = target.size;		
			items = new T[size];		
			neverused = new bool[size];		
			for (int k = 0; k < size; k++) {			
				items[k] = target.items[k];			
				neverused[k] = target.neverused[k];		
			}	
		}	
		~HashTable() {		
			delete[]items;		
			delete[]neverused;	
		}	
		void operator =(HashTable<T> target) {		
			delete[]items;		
			delete[]neverused;		
			size = target.size;		
			items = new T[size];		
			neverused = new bool[size];		
			for (int k = 0; k < size; k++) {			
				items[k] = target.items[k];			
				neverused[k] = target.neverused[k];		
			}	
		}	
		int hash(const T &t) {//�趨�Ĺ�ϣ����		
			return t%10;	
		}	
		int search(const T &t) {
			int i = hash(t) % size;	//�ڹ�ϣ���е�λ�ã�Ͱ��
			int j = 0;	//ȷ��Ͱ֮��Ĳ���	
			while (true) 		{			
				if (neverused[(i + j) % size] == 1 || items[(i + j) % size] == t)	//����һ����Ͱ���߹ؼ������ҵ�			
					return (i + j)%size;			
				j++;			
				if (((i + j) % size) == i)	//�ص���ʼͰ			
					break;		
			}		
			return ((i + j) % size);	
		}	
		bool find(const T&t) {		
			int n = search(t);		
			if (neverused[n] == 1 || items[n] != t)//��Ͱ���Ͱ��ֵ����Ӧ
				return false;		
			return true;	
		}
		bool needReset() {		
			int n = 0;		
			for (int k = 0; k < size; k++) {			
				if (neverused[k] == 0)n++;	//����ɢ�б����ĳ̶�	
			}		
			if (double(n) / double(size) >= 0.6)
				return true;		
			return false;	
		}	
		void insert(T t) 	{		
			int n = search(t);		
			if (neverused[n] == 1) {//�ҿ�Ͱ����			
				neverused[n] = 0;			
				items[n] = t;		
			}	
		}	
		void erase(T t) {		
			int n = search(t);		
			if (neverused[n] == 1 || items[n] != t)
				cout << "��Ԫ�ز�����" << endl;		
			else items[n] = 0;		
			if (needReset())reset();	
		}	
		void output() {		
			cout << "�����ϣ��" << endl;		
			for (int k = 0; k < size; k++)			
				cout << items[k] << " ";		
			cout << endl;		
			for (int k = 0; k < size; k++)			
				cout << neverused[k] << " ";		
			cout << endl;	
		}	
		void reset() {		
			HashTable<T> temp(size);		
			for (int k = 0; k < size; k++) {			
				if (items[k] != 0) {				
					temp.insert(items[k]);	//������֯ɢ�б�ʹ��neverusedֵ����		
				}		
			}		
			*this = temp;	
		}
};
int main() {	
	int n;	
	cin >> n;	
	cout << n << endl;	
	HashTable<int> table(n);	
	table.output();	
	int *temp = new int [n];	
	for(int i=0;i<n;i++)	{		
		cin>>temp[i];		
		table.insert(temp[i]);	
	}	
	table.output();	
	int t = 0;	
	cout << "������Ҫɾ������" << endl;	
	cin >> t;	
	table.erase(t);	
	table.output();	
	cout << "������Ҫ��ӵ���" << endl;	
	cin >> t;	
	table.insert(t);	
	cout << "������Ҫ��ӵ���" << endl;	
	cin >> t;	
	table.insert(t);	
	cout << "������Ҫ��ӵ���" << endl;	
	cin >> t;	
	table.insert(t);	
	table.output();	
	cout << "������Ҫɾ������" << endl;	
	cin >> t;	
	table.erase(t);	
	table.output();	
	cout << "������Ҫɾ������" << endl;	
	cin >> t;	
	table.erase(t);	
	table.output();	

}
//9
//11 24 73 26 35 94 26 47 62
//26
//47
//25
//34
//94
//47




