#include<iostream>
using namespace std;
template<class T>
class Term {
public:
    int row, col;
    T value;
};
template<class T>
class SparseMatrix {
public:
    void Append(const Term<T>& t);
    int rows, cols;  // 矩阵的维度
    int terms;  // 现有非零元素数目
    Term<T>* a;   // 数组
    int MaxTerms;//数组大小
    SparseMatrix(int maxTerms);
    SparseMatrix<T>& multiply(SparseMatrix<T>b, SparseMatrix<T>c);
    void output();
	int getterms(){
	 return terms;
	}

};

template<class T>
void SparseMatrix<T>::Append(const Term<T>& t)//term链表向后扩充
{
    if (terms > MaxTerms)
        cout << "WRONG!" << endl;
    a[terms] = t;
    terms++;
}

template<class T>
SparseMatrix<T>::SparseMatrix(int maxTerms)//由给出数组大小构造稀疏矩阵类
{
    if (maxTerms < 1)
        cout << "WRONG!" << endl;
    MaxTerms = maxTerms;
    a = new Term<T>[MaxTerms];
    terms = rows = cols = 0;
}

template<class T>
SparseMatrix<T>& SparseMatrix<T>::multiply(SparseMatrix<T> b, SparseMatrix<T> c)//矩阵b、c相乘
{
    //初始化结果矩阵
    rows = b.rows;
    cols = c.cols;
    int count = 0;//标记结果矩阵的三元表
    this->a = new Term<T>[b.rows * c.cols];//结果矩阵的元素个数
    terms=0;
    //
    int* rownums = new int[rows + 1];//a第i行非零元素的个数
    int* rowfirst = new int[rows + 1];//第i行第一个非零元素在表中的位置

    //初始化rownums数组
    for (int i = 0; i <= rows; i++) {
        rownums[i] = 0;
    }
    for (int i = 0; i <b.terms; i++) {
        rownums[b.a[i].row]++;
        //cout << rownums[i] << " ";
    }

    //初始化rowfirst数组
    for (int i = 0; i <= rows; i++) {
        rowfirst[i] = -1;//若第i行没有非0元素，置为-1
    }

    rowfirst[1] = 0;
    for (int i = 2; i <= rows; i++) {
        rowfirst[i] = rowfirst[i - 1] + rownums[i - 1]; //第i行第一个非零元素在表中的位置为上一行非零元素个数+第一个非0元素位置
    }
    T* accumulator = new T[c.cols + 1];//定义c.cols大小的累加器
    for (int i = 0; i <= c.cols; i++)
        accumulator[i] = 0;//初始化累加器，分别表示各个列

    for (int i = 1; i <= rows; i++) {//遍历b矩阵的每一行
        if (rowfirst[i] != -1) {//若矩阵b第i行不为空，则要开始遍历c的三元表，并在累加器中存值
            for (int k = 1; k <= rownums[k]; k++) {//遍历b矩阵第i行的每一个元素
                Term<T>& rownum = b.a[rowfirst[i]];//取出i行第一个非0元素的信息
                for (int j = 0; j < c.terms; j++) {//对于b矩阵i行的每一个元素，都遍历一遍c矩阵
                    Term<T>& colnum = c.a[j];//c矩阵的元素
                    if (rownum.row == i && rownum.col == colnum.row)//确保还在当前行，且为对应元素
                        accumulator[colnum.col] += rownum.value * colnum.value;
                }
                rowfirst[i]++;
            }
            for (int k = 1; k <= c.cols; k++) {
                if (accumulator[k] != 0) {//结果的第i行第k列有值,赋值给结果矩阵
                    this->terms++;
                    this->a[count].row = i;
                    this->a[count].col = k;
                    this->a[count].value = accumulator[k];
                    count++;
                }
            }
            for (int k = 1; k <= c.cols; k++)
                accumulator[k] = 0;//累加器清0
        }
    }
    return *this;
}

template<class T>
void SparseMatrix<T>::output()
{
    for (int i = 0; i < terms; i++) {
        cout << "row:" << a[i].row << " " << "col:" << a[i].col << " " << "value:" << a[i].value << endl;
    }
}
//int main() {
//    SparseMatrix<int> a(5);
//    SparseMatrix<int> b(5);
//    SparseMatrix<int> c(9);
//    cout << "输入s的行列信息" << endl;
//    cin >> a.rows >> a.cols;//33
//   
//    cout << "输入s的元素信息" << endl;
//    for (int i = 0; i < 5; i++) {
//        Term<int> t;
//        cin >> t.row >> t.col >> t.value;
//        a.Append(t);
//    }
//     cout << "输入p的行列信息" << endl;
//    cin >> b.rows >> b.cols;//33
//    cout << "输入p的元素信息" << endl;
//    for (int i = 0; i < 5; i++) {
//        Term<int> t;
//        cin >> t.row >> t.col >> t.value;
//        b.Append(t);
//    }
//
//    c.multiply(a, b);
//    c.output();
//	cout<<"c中三元表的元素个数："<<c.getterms()<<endl;
//}


