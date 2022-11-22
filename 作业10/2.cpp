#pragma once
//#ifndef GRAPH_
#define GRAPH_
#include<list>
#include<iostream>
using std::cout;
using std::list;
using std::endl;
class Graph
{
    int V;//ͼ�Ĵ�С
    bool** tc;//���ݱհ�
    list<int>* adj;//�ڽӾ��� �����ʾ
    void undirectedTC(int u, int v);
public:
    Graph(int V);
    void addEdge(int v, int w) { adj[v].push_back(w); }
    void transitiveClosure();
};
Graph::Graph(int V)//��ʼ��ͼ �ͱհ�
{
    this->V = V;
    adj = new list<int>[V];

    tc = new bool* [V];
    for (int i = 0; i < V; i++)
    {
        tc[i] = new bool[V];
        memset(tc[i], false, V * sizeof(bool));//��ַ��ֵ һ��ȫΪ0
    }
}

//��ÿ����ʹ��DFS������ȣ��ҵ�һ���ɵ���ĵ㣬�ʹӸõ�����������ɵ���ĵ�
void Graph::undirectedTC(int s, int v)//sΪ��� vΪ����һ��һ�οɴ��
{
    bool one = false;
    for (list<int>::iterator i = adj[s].begin(); i != adj[s].end(); ++i)
    {
        int tmp = *i;
        if (tmp == v)one = true;
    }
    if (!one)
        tc[s][v] = true;
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (tc[s][*i] == false)
            undirectedTC(s, *i);
}


void Graph::transitiveClosure()
{
    for (int i = 0; i < V; i++)
        undirectedTC(i, i);
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
            if (i != j)
                cout << tc[i][j] << " ";
            else
                cout << 0 << " ";
        cout << endl;
    }
}
int main() {
    Graph g(9);  
    g.addEdge(1, 2);
    g.addEdge(2, 4);
    g.addEdge(3, 2);
    g.addEdge(6, 3);
    g.transitiveClosure();
}