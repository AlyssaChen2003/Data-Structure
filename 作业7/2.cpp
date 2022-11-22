#include <iostream>
#include <string>
#include <cstring>
using namespace std;

struct HuffmanNode {//�������ڵ���
    int weight; // Ȩ�أ����ֵĴ�������Ƶ��
    char ch; // �洢����
    string code; // �洢�÷��Ŷ�Ӧ�ı���
    int leftChild, rightChild, parent; // ���Һ��ӣ������
};

class HuffmanCode {
public:
    HuffmanCode(string str); // ���캯��
    ~HuffmanCode(); // ��������
    void getMin(int& first, int& second, int parent); // ѡȡ������С��Ԫ��
    void Merge(int first, int second, int parent); // �ϲ�
    void Encode(); // ����:���ù���������ԭ������ݽ��м���
    void Decode(string str); // ����
private:
    HuffmanNode* HuffmanTree; // ����
    int leafSize; // ͳ�Ʋ�ͬ�ַ��ĸ���
};

// ���캯��
HuffmanCode::HuffmanCode(string str) {
    int len = (int)str.size(); // �ַ����ĳ���
    int arr[256], i; // �洢�ַ��������ַ��ĸ���
    HuffmanTree = new HuffmanNode[256]; // ��̬����ռ�

    // 1.��ʼ��HuffmanTree����
    for (i = 0; i < (2 * len - 1); i++) { // huffmantreeҶ�ӽ���Ϊ���ַ����ִ�����Ϊlen,���������2*len-1�����
        HuffmanTree[i].leftChild = HuffmanTree[i].rightChild = HuffmanTree[i].parent = -1;
        HuffmanTree[i].code = "";
    }


    // 2.ͳ��������ַ����ĸ����ַ����ֵĸ���
    memset(arr, 0, sizeof(arr)); // ����
    for (i = 0; i < len; i++) // ͳ�ƴ���
        arr[str[i]]++; // str[i] -> ת�ɶ�Ӧ��ASCII��


    leafSize = 0; // �ַ�������
    for (i = 0; i < 256; i++) {
        if (arr[i] != 0) { // �г��ֵ��ַ�
            
            HuffmanTree[leafSize].ch = (char)i; // ��int������ת��char���ַ�
            HuffmanTree[leafSize].weight = arr[i]; // Ȩ��
            leafSize++;
        }
    }


    // 3.ѡȡ������Сֵ�ϲ�
    int first, second; // ������С�Ľ��
    for (i = leafSize; i < (2 * leafSize - 1); i++) { // ��leafSize-1��
        getMin(first, second, i); // ѡȡ������С��Ԫ��
        Merge(first, second, i); // �ϲ�
    }
}

// ��������
HuffmanCode::~HuffmanCode() {
    delete[]HuffmanTree;
}

// ѡȡȨֵ������С��Ԫ��
void HuffmanCode::getMin(int& first, int& second, int parent) {
    double weight = 0;
    int i;

    // ��first
    for (i = 0; i < parent; i++) {
        if (HuffmanTree[i].parent != -1) // ��ѡ����ֱ������
            continue;
        if (weight == 0) { // ��һ���ҵ�ûѡ���Ľ��
            weight = HuffmanTree[i].weight;
            first = i;
        }
        else if (HuffmanTree[i].weight < weight) { // Ȩֵ��С
            weight = HuffmanTree[i].weight;
            first = i;
        }
    }
    // ��second
    weight = 0;
    for (i = 0; i < parent; i++) {
        if (HuffmanTree[i].parent != -1 || i == first) // ��ѡ����ֱ������
            continue;
        if (weight == 0) { // ��һ���ҵ�ûѡ���Ľ��
            weight = HuffmanTree[i].weight;
            second = i;
        }
        else if (HuffmanTree[i].weight < weight) { // Ȩֵ��С
            weight = HuffmanTree[i].weight;
            second = i;
        }
    }
}

// �ϲ�
void HuffmanCode::Merge(int first, int second, int parent) {
    HuffmanTree[first].parent = HuffmanTree[second].parent = parent; // �����
    HuffmanTree[parent].leftChild = first; // ����
    HuffmanTree[parent].rightChild = second; // �Һ���
    HuffmanTree[parent].weight = HuffmanTree[first].weight + HuffmanTree[second].weight; // Ȩֵ
}

// ����
void HuffmanCode::Encode() {
    string code; // �洢���ŵĲ����������Ʊ���
    int i, j, k, parent;

    for (i = 0; i < leafSize; i++) { // ��Ҷ�ӽ�����
        j = i;
        code = ""; // ��ʼ��Ϊ��
        while (HuffmanTree[j].parent != -1) { // �����ҵ������
            parent = HuffmanTree[j].parent; // �����
            if (j == HuffmanTree[parent].leftChild) // ��������ӣ����Ϊ0
                code += "0";
            else // �Һ��ӣ���Ϊ1
                code += "1";
            j = parent; // ���Ƶ������
        }
        // ����Ҫ����������Ϊ�Ǵ�Ҷ�������ߵ�������������Ҫ�Ӹ��ߵ�Ҷ�ӽ��
        for (k = (int)code.size() - 1; k >= 0; k--)
            HuffmanTree[i].code += code[k]; // �������
        cout << "�ַ���" << HuffmanTree[i].ch << "�ı���Ϊ��" << HuffmanTree[i].code << endl;
    }
}

// ����
void HuffmanCode::Decode(string str) {
    string decode, temp; // decode������������, temp����ÿһ������
    int len = (int)str.size(); // ����ĳ���
    int i, j;

    decode = temp = ""; // ��ʼ��Ϊ��
    for (i = 0; i < len; i++) {
        temp += str[i]; // ��һ������
        for (j = 0; j < leafSize; j++) {
            if (HuffmanTree[j].code == temp) { // ��Ҷ�ӽ�����ҵ���Ӧ�ı���
                decode += HuffmanTree[j].ch; // ת�ɶ�Ӧ���ַ�
                temp = "";
                break;
            }
        }
        if (i == len - 1 && j == leafSize) { // �����궼û�ҵ���Ӧ�ı���
            cout << "�������" << endl;
            return;
        }
    }
    cout << decode << endl;
}
int main() {
    string str;

    cout << "�������ַ������б��룺" << endl;
    cin >> str; // ����Ҫ���ܵ��ַ���
    HuffmanCode st(str); // ����
    cout << "���ַ�������������£�" << endl;
    st.Encode(); // ����
    cout << endl;
    cout << "������Ҫ����Ķ����Ʊ���:" << endl;
    cin >> str;
    cout << "�������£�" << endl;
    st.Decode(str); // ����
    return 0;
}


