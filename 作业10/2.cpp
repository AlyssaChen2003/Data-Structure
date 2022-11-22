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
    int V;//图的大小
    bool** tc;//传递闭包
    list<int>* adj;//邻接矩阵 链表表示
    void undirectedTC(int u, int v);
public:
    Graph(int V);
    void addEdge(int v, int w) { adj[v].push_back(w); }
    void transitiveClosure();
};
Graph::Graph(int V)//初始化图 和闭包
{
    this->V = V;
    adj = new list<int>[V];

    tc = new bool* [V];
    for (int i = 0; i < V; i++)
    {
        tc[i] = new bool[V];
        memset(tc[i], false, V * sizeof(bool));//地址赋值 一行全为0
    }
}

//对每个点使用DFS深度优先，找到一个可到达的点，就从该点出发找其他可到达的点
void Graph::undirectedTC(int s, int v)//s为起点 v为任意一个一次可达的
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