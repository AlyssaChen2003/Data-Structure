#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


const int RED = 1;
const int BLACK = -1;

template<class T>
struct Node {
    T data;
    Node* lchild;
    Node* rchild;
    Node* parent;
    int color;
    Node(T e, int col, Node* p, Node* l, Node* r) :
        data(e), color(BLACK), parent(NULL), lchild(NULL), rchild(NULL) {}
};
template<class T>
class BSTree {
public:
    Node<T>* root;
    BSTree<T>() {
    }
    ~BSTree() {
    }
    virtual void preorder() = 0; //ǰ��
    virtual void ascend() = 0;   //����
    virtual void postorder() = 0;//����
    virtual Node<T>* find(T e) = 0;//Ѱ��Ԫ��
    virtual void erase(T e) = 0;//ɾ��Ԫ��
    virtual void insert(T e) = 0;//����Ԫ��
};
template<class T>
class redBlackTree :public BSTree<T> {
public:
    Node<T>* root;
    Node<T>* successor(Node<T>* x);
    bool is_empty();
    void preorder(Node<T>* t);
    void ascend(Node<T>* t);
    void postorder(Node<T>* t);
    void insert_fix_up(Node<T>* x);
    void erase_fix_up(Node<T>* x);
    void erase(Node<T>* x);
    int get_color(Node<T>* p) {
        return p == NULL ? BLACK : p->color;
    }
public:
    redBlackTree() {
        root = NULL;
    }
    ~redBlackTree() {
        set_empty(root);
    }
    void preorder();
    void ascend();
    void postorder();
    void rotate_left(Node<T>* x);
    void rotate_right(Node<T>* y);
    Node<T>* find(T e);
    T get_min();
    T get_max();
    void erase(T e);
    void insert(T e);
    void set_empty(Node<T>*& t);
    void show(Node<T>* root, int k) {
        if (root)
        {
            show(root->rchild, k + 1);
            for (int i = 0; i < k; i++)
            {
                cout << '\t';
            }
            visit(root);
            cout << endl;
            show(root->lchild, k + 1);
        }
    }
    void visit(Node<T>* t) {
        if (t)
        {
           cout<< t->data<<" ";
           if (t->color == RED)cout << "R" << endl;
           else cout << "B" << endl;
        }
       
    }
};
template<class T>
bool redBlackTree<T>::is_empty() {
    return root == NULL;
}
template<class T>
void redBlackTree<T>::set_empty(Node<T>*& t) {
    if (t == NULL)return;
    if (t->lchild != NULL)
        set_empty(t->lchild);
    if (t->rchild != NULL)
        set_empty(t->rchild);
    delete t;
    t = NULL;
}
template<class T>
void redBlackTree<T>::preorder(Node<T>* t) {
    if (t != NULL) {
        cout << t->data <<" "<<t->color<< " ";
        preorder(t->lchild);
        preorder(t->rchild);
    }

}
template<class T>
void redBlackTree<T>::preorder() {//�޲���ʱĬ�ϱ�����
    preorder(root);
}
template<class T>
void redBlackTree<T>::ascend(Node<T>* t) {
    if (t != NULL) {
        ascend(t->lchild);
        cout << t->data << " " << t->color << " ";
        ascend(t->rchild);
    }
}
template<class T>
void redBlackTree<T>::ascend() {
    ascend(root);
}
template<class T>
void redBlackTree<T>::postorder(Node<T>* t) {
    if (t != NULL) {
        postorder(t->lchild);
        postorder(t->rchild);
        cout << t->data << " " << t->color << " ";
    }
}
template<class T>
void redBlackTree<T>::postorder() {
    postorder(root);
}
template<class T>
T redBlackTree<T>::get_min() {
    if (is_empty())return 0;
    Node<T>* p = root;
    while (p->lchild != NULL)
        p = p->lchild;
    cout << "min:" << p->data << endl;//һֱ���������������СԪ��
    return p->data;
}
template<class T>
T redBlackTree<T>::get_max() {
    if (is_empty())return 0;
    Node<T>* p = root;
    while (p->rchild != NULL)
        p = p->rchild;
    cout << "max:" << p->data << endl;//һֱ���������ұ������Ԫ��
    return p->data;
}
template<class T>
void redBlackTree<T>::rotate_left(Node<T>* x) {//����
    if (x == NULL)return;
    Node<T>* y = x->rchild;
    x->rchild = y->lchild;
    if (y->lchild != NULL)
        y->lchild->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else {
        if (x->parent->lchild == x)
            x->parent->lchild = y;
        else
            x->parent->rchild = y;
    }
    y->lchild = x;
    x->parent = y;
}
template<class T>
void redBlackTree<T>::rotate_right(Node<T>* y) {//����
    if (y == NULL)return;
    Node<T>* x = y->lchild;
    y->lchild = x->rchild;
    if (x->rchild != NULL)
        x->rchild->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        root = x;
    else {
        if (y->parent->rchild == y)
            y->parent->rchild = x;
        else
            y->parent->lchild = x;
    }
    x->rchild = y;
    y->parent = x;
}
template<class T>
void redBlackTree<T>::insert(T e) {
    if (root == NULL) {//�����������Ϊ��ɫ
        root = new Node<T>(e, BLACK, NULL, NULL, NULL);
        return;
    }
    Node<T>* pa = NULL;
    Node<T>* x = root;
    while (x != NULL) {
        pa = x;
        if (e < x->data)
            x = x->lchild;
        else if (e > x->data)x = x->rchild;
        else if (e == x->data) {
            //cout<<"�ظ���"<<endl;
            return;
        }
    }//�ҵ���Ҫ����ĵط�

    Node<T>* z = new Node<T>(e, BLACK, NULL, NULL, NULL);
    z->parent = pa;//paΪ�²���ڵ�ĸ��ڵ�
    if (e < pa->data)
        pa->lchild = z;
    else
        pa->rchild = z;
    insert_fix_up(z);//�������
}
template<class T>
void redBlackTree<T>::insert_fix_up(Node<T>* x) {
    x->color = RED;//�²����Ϊ��ɫ
    while (x != NULL && x != root && get_color(x->parent) == RED) {//��Ҫ���������
        if (x->parent == x->parent->parent->lchild) {
            //�������游������ӣ��������Ҷ���
            Node<T>* uncle = x->parent->parent->rchild;
            if (get_color(uncle) == RED) {
                //1�������Ǻ�ɫ XYr
                x->parent->color = BLACK;
                uncle->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else {// XYb


                //2�������Ǻ�ɫ��x�Ǹ����Ҷ��� 
                if (x == x->parent->rchild) {
                  

                    x = x->parent;
                    rotate_left(x);//��x�ĸ��׽ڵ�Ϊ��������
                }
                //3�������Ǻ�ɫ��x�Ǹ��������
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotate_right(x->parent->parent);//��x���游�ڵ�Ϊ��������
            }
        }
        //�Գ�
        else {
            //�������游���Ҷ��ӣ������������
            Node<T>* uncle = x->parent->parent->lchild;


            if (get_color(uncle) == RED) {
                //4�������Ǻ�ɫ
                x->parent->color = BLACK;
                uncle->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else {
                //5�������Ǻ�ɫ���������游�����
                if (x == x->parent->lchild) {
                    
                    x = x->parent;
                    rotate_right(x);
                }
                //6�������Ǻ�ɫ���������游�Ҷ���
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotate_left(x->parent->parent);
            }
        }
    }
    root->color = BLACK;
}
template<class T>
Node<T>* redBlackTree<T>::successor(Node<T>* x) {
    //Ѱ����������ĺ�̽ڵ�
    //��ɾ�������д��汻ɾ��Ԫ��
    //�ͽ�ԭ��

    if (x == NULL)return NULL;
    if (x->rchild != NULL) {
        Node<T>* p = x->rchild;
        while (p->lchild != NULL)
            p = p->lchild;
        return p;
    }
    else {
        Node<T>* pa = x->parent;
        Node<T>* ch = x;
        while (pa != NULL && ch == pa->rchild) {
            ch = pa;
            pa = pa->parent;
        }
        return pa;
    }
}
template<class T>
Node<T>* redBlackTree<T>::find(T e) {
    Node<T>* p = root;
    while (p != NULL) {
        if (e < p->data)
            p = p->lchild;
        else if (e > p->data)
            p = p->rchild;
        else {
            // cout<<"find it!"<<endl;
            return p;
        }
    }
    // cout<<"can't find it."<<endl;
    return NULL;
}
template<class T>
void redBlackTree<T>::erase(T e) {
    Node<T>* p = find(e);
    if (p != NULL)erase(p);
}
//�������ڵ�xΪ��ɫ����x��Ϊ��ɫ������������
//
//2.�������x��Ϊ��ɫ
//
//case1 ��x���ֵܽڵ�wΪ��ɫ
//
//case2  ��x���ֵܽڵ�wΪ��ɫ
//
//case2.1  w�������ӽڵ㶼Ϊ��
//
//case2.2  ��wΪ������ʱ��w����ڵ�Ϊ�죨���ߵ�wΪ������ʱ��w�����ӽڵ�Ϊ�죩
//
//case2.3  ��wΪ������ʱ��w���ҽڵ�Ϊ�ڣ���ڵ�϶�Ϊ�죬��Ȼ����case2.1�����ߵ�wΪ������ʱ��w�����ӽڵ�Ϊ�ڣ�

template<class T>
void redBlackTree<T>::erase(Node<T>* x) {
    if (x->lchild != NULL && x->rchild != NULL) {//����Ҷ�ڵ������������ĺ�̽ڵ㽻��
        Node<T>* s = successor(x);
        x->data = s->data;
        x = s;
    }
    Node<T>* tmp = (x->lchild != NULL ? x->lchild : x->rchild);
    if (tmp != NULL) {//����Ҷ�ڵ�
        tmp->parent = x->parent;
        if (x->parent == NULL)
            root = tmp;
        else if (x == x->parent->lchild)
            x->parent->lchild = tmp;
        else
            x->parent->rchild = tmp;
        x->lchild = x->rchild = x->parent = NULL;
        if (get_color(x) == BLACK)erase_fix_up(tmp);//�Ǻڽڵ� ��������
    }
    else if (x->parent == NULL) {//����Ϊ��
        root = NULL;
    }
    else {//��Ҷ�ڵ�
        if (get_color(x) == BLACK)
            erase_fix_up(x);//�Ǻڽڵ� ����
        if (x->parent != NULL) {
            if (x == x->parent->lchild)
                x->parent->lchild = NULL;
            else if (x == x->parent->rchild)
                x->parent->rchild = NULL;
            x->parent = NULL;
        }
    }
}
template<class T>
void redBlackTree<T>::erase_fix_up(Node<T>* x) {
    while (x != root && get_color(x) == BLACK) {
        if (x == x->parent->lchild) {//�Ǹ��׵�����
            Node<T>* bro = x->parent->rchild;//broΪ�����Һ���
            if (get_color(bro) == RED) {
                bro->color = BLACK;//���ֵܽڵ��Ϊ��ɫ��x�ĸ���13���Ϊ��ɫ����x�ĸ��ڵ�����
                x->parent->color = RED;//��ת��x���ֵܽڵ��Ϊ��ɫ
                rotate_left(x->parent);
                bro = x->parent->rchild;
            }
            if (get_color(bro->lchild) == BLACK && get_color(bro->rchild) == BLACK) {//case2.1  w�������ӽڵ㶼Ϊ��
                bro->color = RED;//��wΪ�죬x=x.parent,Ȼ��ͼ���ѭ������
                x = x->parent;
            }
            else {
                if (get_color(bro->rchild) == BLACK) {//case2.3  ��wΪ������ʱ��w���ҽڵ�Ϊ�ڣ���ڵ�϶�Ϊ��
                    bro->lchild->color = BLACK;//��Ŀ���ǰ�������case2.2����
                    //��wΪ�죬w����ڵ�Ϊ�ڣ�����w���ҽڵ�Ϊ�ڣ�����W�������������������õ����case2.2
                    bro->color = RED;
                    rotate_right(bro);
                    bro = x->parent->rchild;
                }
                bro->color = get_color(x->parent);
                x->parent->color = BLACK;
                bro->rchild->color = BLACK;
                rotate_left(x->parent);
                x = root;
            }
        }
        else {//�Ǹ����Һ���
            Node<T>* bro = x->parent->lchild;
            if (get_color(bro) == RED) {
                bro->color = BLACK;
                x->parent->color = RED;
                rotate_right(x->parent);
                bro = x->parent->lchild;
            }
            if (get_color(bro->rchild) == BLACK && get_color(bro->lchild) == BLACK) {
                bro->color = RED;
                x = x->parent;
            }
            else {

                //��wΪ������ʱ��w�����ӽڵ�Ϊ��
                if (get_color(bro->lchild) == BLACK) {//��w��������Ϊ�ڣ�������w��������Ϊ�ڣ�
                    //����w��w���ڵ����ɫ���Ը��ڵ����������������ﵽƽ�⣬��x = root����ѭ����
                    bro->rchild->color = BLACK;
                    bro->color = RED;
                    rotate_left(bro);
                    bro = x->parent->lchild;
                }//��wΪ������ʱ��w����ڵ�Ϊ��
                bro->color = get_color(x->parent);
                x->parent->color = BLACK;
                bro->lchild->color = BLACK;
                rotate_right(x->parent);
                x = root;
            }
        }
        x->color = BLACK;
    }
}
template<class T>
class dredBlackTree :public BSTree<T> {
public:
    Node<T>* root;
    Node<T>* successor(Node<T>* x);
    bool is_empty();
    void preorder(Node<T>* t);
    void ascend(Node<T>* t);
    void postorder(Node<T>* t);
    void insert_fix_up(Node<T>* x);
    void erase_fix_up(Node<T>* x);
    void erase(Node<T>* x);
    int get_color(Node<T>* p) {
        return p == NULL ? BLACK : p->color;
    }
public:
    dredBlackTree() {
        root = NULL;
    }
    ~dredBlackTree() {
        set_empty(root);
    }
    void preorder();
    void ascend();
    void postorder();
    void rotate_left(Node<T>* x);
    void rotate_right(Node<T>* y);
    Node<T>* find(T e);
    T get_min();
    T get_max();
    void erase(T e);
    void insert(T e);
    void set_empty(Node<T>*& t);
    void show(Node<T>* root, int k) {
        if (root)
        {
            show(root->rchild, k + 1);
            for (int i = 0; i < k; i++)
            {
                cout << '\t';
            }
            visit(root);
            cout << endl;
            show(root->lchild, k + 1);
        }
    }
    void visit(Node<T>* t) {
        if (t)
        {
            cout << t->data << " ";
            if (t->color == RED)cout << "R" << endl;
            else cout << "B" << endl;
        }

    }
};
template<class T>
bool dredBlackTree<T>::is_empty() {
    return root == NULL;
}
template<class T>
void dredBlackTree<T>::set_empty(Node<T>*& t) {
    if (t == NULL)return;
    if (t->lchild != NULL)
        set_empty(t->lchild);
    if (t->rchild != NULL)
        set_empty(t->rchild);
    delete t;
    t = NULL;
}
template<class T>
void dredBlackTree<T>::preorder(Node<T>* t) {
    if (t != NULL) {
        cout << t->data << " ";
        preorder(t->lchild);
        preorder(t->rchild);
    }
}
template<class T>
void dredBlackTree<T>::preorder() {
    preorder(root);
}
template<class T>
void dredBlackTree<T>::ascend(Node<T>* t) {
    if (t != NULL) {
        ascend(t->lchild);
        cout << t->data << " ";
        ascend(t->rchild);
    }
}
template<class T>
void dredBlackTree<T>::ascend() {
    ascend(root);
}
template<class T>
void dredBlackTree<T>::postorder(Node<T>* t) {
    if (t != NULL) {
        postorder(t->lchild);
        postorder(t->rchild);
        cout << t->data << " ";
    }
}
template<class T>
void dredBlackTree<T>::postorder() {
    postorder(root);
}
template<class T>
T dredBlackTree<T>::get_min() {
    if (is_empty())return 0;
    Node<T>* p = root;
    while (p->lchild != NULL)
        p = p->lchild;
    cout << "min:" << p->data << endl;
    return p->data;
}
template<class T>
T dredBlackTree<T>::get_max() {
    if (is_empty())return 0;
    Node<T>* p = root;
    while (p->rchild != NULL)
        p = p->rchild;
    cout << "max:" << p->data << endl;
    return p->data;
}
template<class T>
void dredBlackTree<T>::rotate_left(Node<T>* x) {
    if (x == NULL)return;
    Node<T>* y = x->rchild;
    x->rchild = y->lchild;
    if (y->lchild != NULL)
        y->lchild->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else {
        if (x->parent->lchild == x)
            x->parent->lchild = y;
        else
            x->parent->rchild = y;
    }
    y->lchild = x;
    x->parent = y;
}
template<class T>
void dredBlackTree<T>::rotate_right(Node<T>* y) {
    if (y == NULL)return;
    Node<T>* x = y->lchild;
    y->lchild = x->rchild;
    if (x->rchild != NULL)
        x->rchild->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        root = x;
    else {
        if (y->parent->rchild == y)
            y->parent->rchild = x;
        else
            y->parent->lchild = x;
    }
    x->rchild = y;
    y->parent = x;
}
template<class T>
void dredBlackTree<T>::insert(T e) {
    if (root == NULL) {
        root = new Node<T>(e, BLACK, NULL, NULL, NULL);
        return;
    }
    Node<T>* pa = NULL;
    Node<T>* x = root;
    while (x != NULL) {
        pa = x;
        if (e < x->data)
            x = x->lchild;
        else x = x->rchild;
    }
    Node<T>* z = new Node<T>(e, BLACK, NULL, NULL, NULL);
    z->parent = pa;
    if (e < pa->data)
        pa->lchild = z;
    else
        pa->rchild = z;
    insert_fix_up(z);
}
template<class T>
void dredBlackTree<T>::insert_fix_up(Node<T>* x) {
    x->color = RED;
    while (x != NULL && x != root && get_color(x->parent) == RED) {
        if (x->parent == x->parent->parent->lchild) {
            //�������游���Ҷ��ӣ������������
            Node<T>* uncle = x->parent->parent->rchild;
            if (get_color(uncle) == RED) {
                //1�������Ǻ�ɫ
                x->parent->color = BLACK;
                uncle->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else {
                //2�������Ǻ�ɫ��x�Ǹ����Ҷ���
                if (x == x->parent->rchild) {
                    x = x->parent;
                    rotate_left(x);
                }
                //3�������Ǻ�ɫ��x�Ǹ��������
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotate_right(x->parent->parent);
            }
        }
        else {
            //�������游���Ҷ��ӣ������������
            Node<T>* uncle = x->parent->parent->lchild;
            if (get_color(uncle) == RED) {
                //4�������Ǻ�ɫ
                x->parent->color = BLACK;
                uncle->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else {
                //5�������Ǻ�ɫ���������游�����
                if (x == x->parent->lchild) {
                    x = x->parent;
                    rotate_right(x);
                }
                //6�������Ǻ�ɫ���������游�Ҷ���
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotate_left(x->parent->parent);
            }
        }
    }
    root->color = BLACK;
}
template<class T>
Node<T>* dredBlackTree<T>::successor(Node<T>* x) {
    if (x == NULL)return NULL;
    if (x->rchild != NULL) {
        Node<T>* p = x->rchild;
        while (p->lchild != NULL)
            p = p->lchild;
        return p;
    }
    else {
        Node<T>* pa = x->parent;
        Node<T>* ch = x;
        while (pa != NULL && ch == pa->rchild) {
            ch = pa;
            pa = pa->parent;
        }
        return pa;
    }
}
template<class T>
Node<T>* dredBlackTree<T>::find(T e) {
    Node<T>* p = root;
    while (p != NULL) {
        if (e < p->data)
            p = p->lchild;
        else if (e > p->data)
            p = p->rchild;
        else {
            // cout<<"find it!"<<endl;
            return p;
        }
    }
    // cout<<"can't find it."<<endl;
    return NULL;
}
template<class T>
void dredBlackTree<T>::erase(T e) {
    Node<T>* p = find(e);
    while (p != NULL) {
        erase(p);
        p = find(e);
    }
}
template<class T>
void dredBlackTree<T>::erase(Node<T>* x) {
    if (x->lchild != NULL && x->rchild != NULL) {
        Node<T>* s = successor(x);
        x->data = s->data;
        x = s;
    }
    Node<T>* tmp = (x->lchild != NULL ? x->lchild : x->rchild);
    if (tmp != NULL) {
        tmp->parent = x->parent;
        if (x->parent == NULL)
            root = tmp;
        else if (x == x->parent->lchild)
            x->parent->lchild = tmp;
        else
            x->parent->rchild = tmp;
        x->lchild = x->rchild = x->parent = NULL;
        if (get_color(x) == BLACK)erase_fix_up(tmp);
    }
    else if (x->parent == NULL) {
        root = NULL;
    }
    else {
        if (get_color(x) == BLACK)erase_fix_up(x);
        if (x->parent != NULL) {
            if (x == x->parent->lchild)
                x->parent->lchild = NULL;
            else if (x == x->parent->rchild)
                x->parent->rchild = NULL;
            x->parent = NULL;
        }
    }
}
template<class T>
void dredBlackTree<T>::erase_fix_up(Node<T>* x) {
    while (x != root && get_color(x) == BLACK) {
        if (x == x->parent->lchild) {
            Node<T>* bro = x->parent->rchild;
            if (get_color(bro) == RED) {
                bro->color = BLACK;
                x->parent->color = RED;
                rotate_left(x->parent);
                bro = x->parent->rchild;
            }
            if (get_color(bro->lchild) == BLACK && get_color(bro->rchild) == BLACK) {
                bro->color = RED;
                x = x->parent;
            }
            else {
                if (get_color(bro->rchild) == BLACK) {
                    bro->lchild->color = BLACK;
                    bro->color = RED;
                    rotate_right(bro);
                    bro = x->parent->rchild;
                }
                bro->color = get_color(x->parent);
                x->parent->color = BLACK;
                bro->rchild->color = BLACK;
                rotate_left(x->parent);
                x = root;
            }
        }
        else {
            Node<T>* bro = x->parent->lchild;
            if (get_color(bro) == RED) {
                bro->color = BLACK;
                x->parent->color = RED;
                rotate_right(x->parent);
                bro = x->parent->lchild;
            }
            if (get_color(bro->rchild) == BLACK && get_color(bro->lchild) == BLACK) {
                bro->color = RED;
                x = x->parent;
            }
            else {
                if (get_color(bro->lchild) == BLACK) {
                    bro->rchild->color = BLACK;
                    bro->color = RED;
                    rotate_left(bro);
                    bro = x->parent->lchild;
                }
                bro->color = get_color(x->parent);
                x->parent->color = BLACK;
                bro->lchild->color = BLACK;
                rotate_right(x->parent);
                x = root;
            }
        }
        x->color = BLACK;
    }
}
int main() {
    BSTree<int>* p;
    redBlackTree<int> A;
    dredBlackTree<int> B;
    p = &A;
    srand(time(NULL));
    int tmp;
    cout << "-----��������-----" << endl << endl;
    for (int i = 0; i < 10; i++) {
        tmp = i + 1;
        cout << tmp << " ";
        A.insert(tmp);
        B.insert(tmp);
    }
    for (int i = 0; i < 15; i++) {
        tmp = rand() % 10;
        cout << tmp << " ";
        A.insert(tmp);
        B.insert(tmp);
    }
        cout << endl;
    A.show(A.root, 0);
    cout << endl << endl << "-----�����������-----" << endl << endl;
    cout << "redBlackTree:" << endl; 
    A.ascend(); cout << endl;
    A.show(A.root, 0);

    cout << "dredBlackTree:" << endl; 
    B.ascend(); cout << endl;
    B.show(B.root, 0);

    cout << endl << endl << "-----ɾ��3-----" << endl << endl;
    A.erase(3);
    B.erase(3);


    cout << "redBlackTree:" << endl;
    A.ascend(); cout << endl;
    A.show(A.root, 0);
    cout << "dredBlackTree:" << endl;
    B.ascend(); cout << endl;
    B.show(B.root, 0);

    cout << endl << endl << "-----ɾ��5-----" << endl << endl;
    A.erase(5);
    B.erase(5);

    cout << "redBlackTree:" << endl;
    A.ascend(); cout << endl;
    A.show(A.root, 0);

    cout << "dredBlackTree:" << endl;
    B.ascend(); cout << endl;
    B.show(B.root, 0);

    return 0;
}
