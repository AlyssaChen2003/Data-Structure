#include <iostream>
#include <string>
#include <cstring>
using namespace std;

struct HuffmanNode {//霍夫曼节点类
    int weight; // 权重，出现的次数或者频率
    char ch; // 存储符号
    string code; // 存储该符号对应的编码
    int leftChild, rightChild, parent; // 左、右孩子，父结点
};

class HuffmanCode {
public:
    HuffmanCode(string str); // 构造函数
    ~HuffmanCode(); // 析构函数
    void getMin(int& first, int& second, int parent); // 选取两个较小的元素
    void Merge(int first, int second, int parent); // 合并
    void Encode(); // 编码:利用哈夫曼编码原理对数据进行加密
    void Decode(string str); // 解码
private:
    HuffmanNode* HuffmanTree; // 数组
    int leafSize; // 统计不同字符的个数
};

// 构造函数
HuffmanCode::HuffmanCode(string str) {
    int len = (int)str.size(); // 字符串的长度
    int arr[256], i; // 存储字符串各个字符的个数
    HuffmanTree = new HuffmanNode[256]; // 动态分配空间

    // 1.初始化HuffmanTree数组
    for (i = 0; i < (2 * len - 1); i++) { // huffmantree叶子结点均为各字符出现次数，为len,则树最多有2*len-1个结点
        HuffmanTree[i].leftChild = HuffmanTree[i].rightChild = HuffmanTree[i].parent = -1;
        HuffmanTree[i].code = "";
    }


    // 2.统计输入的字符串的各个字符出现的个数
    memset(arr, 0, sizeof(arr)); // 清零
    for (i = 0; i < len; i++) // 统计次数
        arr[str[i]]++; // str[i] -> 转成对应的ASCII码


    leafSize = 0; // 字符的种数
    for (i = 0; i < 256; i++) {
        if (arr[i] != 0) { // 有出现的字符
            
            HuffmanTree[leafSize].ch = (char)i; // 将int型数字转成char型字符
            HuffmanTree[leafSize].weight = arr[i]; // 权重
            leafSize++;
        }
    }


    // 3.选取两个较小值合并
    int first, second; // 两个较小的结点
    for (i = leafSize; i < (2 * leafSize - 1); i++) { // 做leafSize-1次
        getMin(first, second, i); // 选取两个较小的元素
        Merge(first, second, i); // 合并
    }
}

// 析构函数
HuffmanCode::~HuffmanCode() {
    delete[]HuffmanTree;
}

// 选取权值两个较小的元素
void HuffmanCode::getMin(int& first, int& second, int parent) {
    double weight = 0;
    int i;

    // 找first
    for (i = 0; i < parent; i++) {
        if (HuffmanTree[i].parent != -1) // 已选过，直接跳过
            continue;
        if (weight == 0) { // 第一次找到没选过的结点
            weight = HuffmanTree[i].weight;
            first = i;
        }
        else if (HuffmanTree[i].weight < weight) { // 权值更小
            weight = HuffmanTree[i].weight;
            first = i;
        }
    }
    // 找second
    weight = 0;
    for (i = 0; i < parent; i++) {
        if (HuffmanTree[i].parent != -1 || i == first) // 已选过，直接跳过
            continue;
        if (weight == 0) { // 第一次找到没选过的结点
            weight = HuffmanTree[i].weight;
            second = i;
        }
        else if (HuffmanTree[i].weight < weight) { // 权值更小
            weight = HuffmanTree[i].weight;
            second = i;
        }
    }
}

// 合并
void HuffmanCode::Merge(int first, int second, int parent) {
    HuffmanTree[first].parent = HuffmanTree[second].parent = parent; // 父结点
    HuffmanTree[parent].leftChild = first; // 左孩子
    HuffmanTree[parent].rightChild = second; // 右孩子
    HuffmanTree[parent].weight = HuffmanTree[first].weight + HuffmanTree[second].weight; // 权值
}

// 编码
void HuffmanCode::Encode() {
    string code; // 存储符号的不定长二进制编码
    int i, j, k, parent;

    for (i = 0; i < leafSize; i++) { // 从叶子结点出发
        j = i;
        code = ""; // 初始化为空
        while (HuffmanTree[j].parent != -1) { // 往上找到根结点
            parent = HuffmanTree[j].parent; // 父结点
            if (j == HuffmanTree[parent].leftChild) // 如果是左孩子，则记为0
                code += "0";
            else // 右孩子，记为1
                code += "1";
            j = parent; // 上移到父结点
        }
        // 编码要倒过来：因为是从叶子往上走到根，而编码是要从根走到叶子结点
        for (k = (int)code.size() - 1; k >= 0; k--)
            HuffmanTree[i].code += code[k]; // 保存编码
        cout << "字符：" << HuffmanTree[i].ch << "的编码为：" << HuffmanTree[i].code << endl;
    }
}

// 解码
void HuffmanCode::Decode(string str) {
    string decode, temp; // decode保存整个解码, temp保存每一个解码
    int len = (int)str.size(); // 编码的长度
    int i, j;

    decode = temp = ""; // 初始化为空
    for (i = 0; i < len; i++) {
        temp += str[i]; // 加一个编码
        for (j = 0; j < leafSize; j++) {
            if (HuffmanTree[j].code == temp) { // 在叶子结点中找到对应的编码
                decode += HuffmanTree[j].ch; // 转成对应的字符
                temp = "";
                break;
            }
        }
        if (i == len - 1 && j == leafSize) { // 遍历完都没找到对应的编码
            cout << "解码出错！" << endl;
            return;
        }
    }
    cout << decode << endl;
}
int main() {
    string str;

    cout << "请输入字符串进行编码：" << endl;
    cin >> str; // 输入要加密的字符串
    HuffmanCode st(str); // 对象
    cout << "对字符串编码情况如下：" << endl;
    st.Encode(); // 编码
    cout << endl;
    cout << "请输入要解码的二进制编码:" << endl;
    cin >> str;
    cout << "解码如下：" << endl;
    st.Decode(str); // 解码
    return 0;
}


