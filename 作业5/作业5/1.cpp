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
				neverused[k] = 1;//初始化时neverused为true		
			}	
		}	
		HashTable(const HashTable<T>&target) {//拷贝构造		
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
		int hash(const T &t) {//设定的哈希函数		
			return t%10;	
		}	
		int search(const T &t) {
			int i = hash(t) % size;	//在哈希表中的位置（桶）
			int j = 0;	//确定桶之后的查找	
			while (true) 		{			
				if (neverused[(i + j) % size] == 1 || items[(i + j) % size] == t)	//到达一个空桶或者关键字已找到			
					return (i + j)%size;			
				j++;			
				if (((i + j) % size) == i)	//回到起始桶			
					break;		
			}		
			return ((i + j) % size);	
		}	
		bool find(const T&t) {		
			int n = search(t);		
			if (neverused[n] == 1 || items[n] != t)//空桶或该桶数值不对应
				return false;		
			return true;	
		}
		bool needReset() {		
			int n = 0;		
			for (int k = 0; k < size; k++) {			
				if (neverused[k] == 0)n++;	//计算散列表满的程度	
			}		
			if (double(n) / double(size) >= 0.6)
				return true;		
			return false;	
		}	
		void insert(T t) 	{		
			int n = search(t);		
			if (neverused[n] == 1) {//找空桶插入			
				neverused[n] = 0;			
				items[n] = t;		
			}	
		}	
		void erase(T t) {		
			int n = search(t);		
			if (neverused[n] == 1 || items[n] != t)
				cout << "该元素不存在" << endl;		
			else items[n] = 0;		
			if (needReset())reset();	
		}	
		void output() {		
			cout << "输出哈希表" << endl;		
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
					temp.insert(items[k]);	//重新组织散列表使得neverused值重置		
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
	cout << "请输入要删除的数" << endl;	
	cin >> t;	
	table.erase(t);	
	table.output();	
	cout << "请输入要添加的数" << endl;	
	cin >> t;	
	table.insert(t);	
	cout << "请输入要添加的数" << endl;	
	cin >> t;	
	table.insert(t);	
	cout << "请输入要添加的数" << endl;	
	cin >> t;	
	table.insert(t);	
	table.output();	
	cout << "请输入要删除的数" << endl;	
	cin >> t;	
	table.erase(t);	
	table.output();	
	cout << "请输入要删除的数" << endl;	
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




