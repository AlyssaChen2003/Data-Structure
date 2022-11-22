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
    int rows, cols;  // �����ά��
    int terms;  // ���з���Ԫ����Ŀ
    Term<T>* a;   // ����
    int MaxTerms;//�����С
    SparseMatrix(int maxTerms);
    SparseMatrix<T>& multiply(SparseMatrix<T>b, SparseMatrix<T>c);
    void output();
	int getterms(){
	 return terms;
	}

};

template<class T>
void SparseMatrix<T>::Append(const Term<T>& t)//term�����������
{
    if (terms > MaxTerms)
        cout << "WRONG!" << endl;
    a[terms] = t;
    terms++;
}

template<class T>
SparseMatrix<T>::SparseMatrix(int maxTerms)//�ɸ��������С����ϡ�������
{
    if (maxTerms < 1)
        cout << "WRONG!" << endl;
    MaxTerms = maxTerms;
    a = new Term<T>[MaxTerms];
    terms = rows = cols = 0;
}

template<class T>
SparseMatrix<T>& SparseMatrix<T>::multiply(SparseMatrix<T> b, SparseMatrix<T> c)//����b��c���
{
    //��ʼ���������
    rows = b.rows;
    cols = c.cols;
    int count = 0;//��ǽ���������Ԫ��
    this->a = new Term<T>[b.rows * c.cols];//��������Ԫ�ظ���
    terms=0;
    //
    int* rownums = new int[rows + 1];//a��i�з���Ԫ�صĸ���
    int* rowfirst = new int[rows + 1];//��i�е�һ������Ԫ���ڱ��е�λ��

    //��ʼ��rownums����
    for (int i = 0; i <= rows; i++) {
        rownums[i] = 0;
    }
    for (int i = 0; i <b.terms; i++) {
        rownums[b.a[i].row]++;
        //cout << rownums[i] << " ";
    }

    //��ʼ��rowfirst����
    for (int i = 0; i <= rows; i++) {
        rowfirst[i] = -1;//����i��û�з�0Ԫ�أ���Ϊ-1
    }

    rowfirst[1] = 0;
    for (int i = 2; i <= rows; i++) {
        rowfirst[i] = rowfirst[i - 1] + rownums[i - 1]; //��i�е�һ������Ԫ���ڱ��е�λ��Ϊ��һ�з���Ԫ�ظ���+��һ����0Ԫ��λ��
    }
    T* accumulator = new T[c.cols + 1];//����c.cols��С���ۼ���
    for (int i = 0; i <= c.cols; i++)
        accumulator[i] = 0;//��ʼ���ۼ������ֱ��ʾ������

    for (int i = 1; i <= rows; i++) {//����b�����ÿһ��
        if (rowfirst[i] != -1) {//������b��i�в�Ϊ�գ���Ҫ��ʼ����c����Ԫ�������ۼ����д�ֵ
            for (int k = 1; k <= rownums[k]; k++) {//����b�����i�е�ÿһ��Ԫ��
                Term<T>& rownum = b.a[rowfirst[i]];//ȡ��i�е�һ����0Ԫ�ص���Ϣ
                for (int j = 0; j < c.terms; j++) {//����b����i�е�ÿһ��Ԫ�أ�������һ��c����
                    Term<T>& colnum = c.a[j];//c�����Ԫ��
                    if (rownum.row == i && rownum.col == colnum.row)//ȷ�����ڵ�ǰ�У���Ϊ��ӦԪ��
                        accumulator[colnum.col] += rownum.value * colnum.value;
                }
                rowfirst[i]++;
            }
            for (int k = 1; k <= c.cols; k++) {
                if (accumulator[k] != 0) {//����ĵ�i�е�k����ֵ,��ֵ���������
                    this->terms++;
                    this->a[count].row = i;
                    this->a[count].col = k;
                    this->a[count].value = accumulator[k];
                    count++;
                }
            }
            for (int k = 1; k <= c.cols; k++)
                accumulator[k] = 0;//�ۼ�����0
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
//    cout << "����s��������Ϣ" << endl;
//    cin >> a.rows >> a.cols;//33
//   
//    cout << "����s��Ԫ����Ϣ" << endl;
//    for (int i = 0; i < 5; i++) {
//        Term<int> t;
//        cin >> t.row >> t.col >> t.value;
//        a.Append(t);
//    }
//     cout << "����p��������Ϣ" << endl;
//    cin >> b.rows >> b.cols;//33
//    cout << "����p��Ԫ����Ϣ" << endl;
//    for (int i = 0; i < 5; i++) {
//        Term<int> t;
//        cin >> t.row >> t.col >> t.value;
//        b.Append(t);
//    }
//
//    c.multiply(a, b);
//    c.output();
//	cout<<"c����Ԫ���Ԫ�ظ�����"<<c.getterms()<<endl;
//}


