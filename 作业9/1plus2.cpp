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
    virtual void preorder() = 0; //前序
    virtual void ascend() = 0;   //中序
    virtual void postorder() = 0;//后序
    virtual Node<T>* find(T e) = 0;//寻找元素
    virtual void erase(T e) = 0;//删除元素
    virtual void insert(T e) = 0;//插入元素
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
void redBlackTree<T>::preorder() {//无参数时默认遍历根
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
    cout << "min:" << p->data << endl;//一直遍历到最左边是最小元素
    return p->data;
}
template<class T>
T redBlackTree<T>::get_max() {
    if (is_empty())return 0;
    Node<T>* p = root;
    while (p->rchild != NULL)
        p = p->rchild;
    cout << "max:" << p->data << endl;//一直遍历到最右边是最大元素
    return p->data;
}
template<class T>
void redBlackTree<T>::rotate_left(Node<T>* x) {//左旋
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
void redBlackTree<T>::rotate_right(Node<T>* y) {//右旋
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
    if (root == NULL) {//创建红黑树根为黑色
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
            //cout<<"重复！"<<endl;
            return;
        }
    }//找到需要插入的地方

    Node<T>* z = new Node<T>(e, BLACK, NULL, NULL, NULL);
    z->parent = pa;//pa为新插入节点的父节点
    if (e < pa->data)
        pa->lchild = z;
    else
        pa->rchild = z;
    insert_fix_up(z);//纠正红黑
}
template<class T>
void redBlackTree<T>::insert_fix_up(Node<T>* x) {
    x->color = RED;//新插入的为红色
    while (x != NULL && x != root && get_color(x->parent) == RED) {//需要调整的情况
        if (x->parent == x->parent->parent->lchild) {
            //父亲是祖父的左儿子，叔叔是右儿子
            Node<T>* uncle = x->parent->parent->rchild;
            if (get_color(uncle) == RED) {
                //1）叔叔是红色 XYr
                x->parent->color = BLACK;
                uncle->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else {// XYb


                //2）叔叔是黑色，x是父亲右儿子 
                if (x == x->parent->rchild) {
                  

                    x = x->parent;
                    rotate_left(x);//以x的父亲节点为中心左旋
                }
                //3）叔叔是黑色，x是父亲左儿子
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotate_right(x->parent->parent);//以x的祖父节点为中心右旋
            }
        }
        //对称
        else {
            //父亲是祖父的右儿子，叔叔是左儿子
            Node<T>* uncle = x->parent->parent->lchild;


            if (get_color(uncle) == RED) {
                //4）叔叔是红色
                x->parent->color = BLACK;
                uncle->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else {
                //5）叔叔是黑色，父亲是祖父左儿子
                if (x == x->parent->lchild) {
                    
                    x = x->parent;
                    rotate_right(x);
                }
                //6）叔叔是黑色，父亲是祖父右儿子
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
    //寻找中序遍历的后继节点
    //在删除操作中代替被删除元素
    //就近原则

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
//如果顶替节点x为红色，则将x变为黑色，调整结束。
//
//2.若顶替节x点为黑色
//
//case1 若x的兄弟节点w为红色
//
//case2  若x的兄弟节点w为黑色
//
//case2.1  w的左右子节点都为黑
//
//case2.2  当w为左子树时，w的左节点为红（或者当w为右子树时，w的右子节点为红）
//
//case2.3  当w为右子树时，w的右节点为黑，左节点肯定为红，不然就是case2.1（或者当w为左子树时，w的左子节点为黑）

template<class T>
void redBlackTree<T>::erase(Node<T>* x) {
    if (x->lchild != NULL && x->rchild != NULL) {//不是叶节点的与中序遍历的后继节点交换
        Node<T>* s = successor(x);
        x->data = s->data;
        x = s;
    }
    Node<T>* tmp = (x->lchild != NULL ? x->lchild : x->rchild);
    if (tmp != NULL) {//不是叶节点
        tmp->parent = x->parent;
        if (x->parent == NULL)
            root = tmp;
        else if (x == x->parent->lchild)
            x->parent->lchild = tmp;
        else
            x->parent->rchild = tmp;
        x->lchild = x->rchild = x->parent = NULL;
        if (get_color(x) == BLACK)erase_fix_up(tmp);//是黑节点 调整孩子
    }
    else if (x->parent == NULL) {//父亲为根
        root = NULL;
    }
    else {//是叶节点
        if (get_color(x) == BLACK)
            erase_fix_up(x);//是黑节点 调整
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
        if (x == x->parent->lchild) {//是父亲的左孩子
            Node<T>* bro = x->parent->rchild;//bro为父亲右孩子
            if (get_color(bro) == RED) {
                bro->color = BLACK;//将兄弟节点变为黑色，x的父节13点变为红色，以x的父节点右旋
                x->parent->color = RED;//旋转后，x的兄弟节点变为黑色
                rotate_left(x->parent);
                bro = x->parent->rchild;
            }
            if (get_color(bro->lchild) == BLACK && get_color(bro->rchild) == BLACK) {//case2.1  w的左右子节点都为黑
                bro->color = RED;//令w为红，x=x.parent,然后就继续循环迭代
                x = x->parent;
            }
            else {
                if (get_color(bro->rchild) == BLACK) {//case2.3  当w为右子树时，w的右节点为黑，左节点肯定为红
                    bro->lchild->color = BLACK;//（目的是把情况搞成case2.2），
                    //令w为红，w的左节点为黑（或者w的右节点为黑），以W右旋（或者左旋）。得到情况case2.2
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
        else {//是父亲右孩子
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

                //当w为右子树时，w的右子节点为红
                if (get_color(bro->lchild) == BLACK) {//令w的左子树为黑（或者令w的右子树为黑）
                    //交换w和w父节点的颜色，以父节点右旋（左旋），达到平衡，令x = root跳出循环。
                    bro->rchild->color = BLACK;
                    bro->color = RED;
                    rotate_left(bro);
                    bro = x->parent->lchild;
                }//当w为左子树时，w的左节点为红
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
            //父亲是祖父的右儿子，叔叔是左儿子
            Node<T>* uncle = x->parent->parent->rchild;
            if (get_color(uncle) == RED) {
                //1）叔叔是红色
                x->parent->color = BLACK;
                uncle->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else {
                //2）叔叔是黑色，x是父亲右儿子
                if (x == x->parent->rchild) {
                    x = x->parent;
                    rotate_left(x);
                }
                //3）叔叔是黑色，x是父亲左儿子
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotate_right(x->parent->parent);
            }
        }
        else {
            //父亲是祖父的右儿子，叔叔是左儿子
            Node<T>* uncle = x->parent->parent->lchild;
            if (get_color(uncle) == RED) {
                //4）叔叔是红色
                x->parent->color = BLACK;
                uncle->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else {
                //5）叔叔是黑色，父亲是祖父左儿子
                if (x == x->parent->lchild) {
                    x = x->parent;
                    rotate_right(x);
                }
                //6）叔叔是黑色，父亲是祖父右儿子
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
    cout << "-----插入数据-----" << endl << endl;
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
    cout << endl << endl << "-----中序（升序）输出-----" << endl << endl;
    cout << "redBlackTree:" << endl; 
    A.ascend(); cout << endl;
    A.show(A.root, 0);

    cout << "dredBlackTree:" << endl; 
    B.ascend(); cout << endl;
    B.show(B.root, 0);

    cout << endl << endl << "-----删除3-----" << endl << endl;
    A.erase(3);
    B.erase(3);


    cout << "redBlackTree:" << endl;
    A.ascend(); cout << endl;
    A.show(A.root, 0);
    cout << "dredBlackTree:" << endl;
    B.ascend(); cout << endl;
    B.show(B.root, 0);

    cout << endl << endl << "-----删除5-----" << endl << endl;
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
