#include <iostream>
#include <vector>
#include <list>
using namespace std;


void add_edge(vector<int> adj[], int src, int dest)//加边
{
	adj[src].push_back(dest);
	adj[dest].push_back(src);
}


bool BFS(vector<int> adj[], int src, int dest, int v,
	int pred[], int dist[])
{

	list<int> queue;
	bool* visited = new bool[v];


	for (int i = 0; i < v; i++) {
		visited[i] = false;
		dist[i] = INT_MAX;
		pred[i] = -1;
	}

	visited[src] = true;
	dist[src] = 0;
	queue.push_back(src);

	// BFS
	while (!queue.empty()) {
		int u = queue.front();
		queue.pop_front();
		for (int i = 0; i < adj[u].size(); i++) {//计算路径
			if (visited[adj[u][i]] == false) {
				visited[adj[u][i]] = true;
				dist[adj[u][i]] = dist[u] + 1;
				pred[adj[u][i]] = u;
				queue.push_back(adj[u][i]);
				if (adj[u][i] == dest)
					return true;
			}
		}
	}

	return false;
}
void printShortestDistance(vector<int> adj[], int s,
	int dest, int v)
{

	int* pred = new int[v];
	int* dist = new int[v];

	if (BFS(adj, s, dest, v, pred, dist) == false) {
		cout << "所给的两个点没有可通的路径" << endl;
		return;
	}


	vector<int> path;
	int crawl = dest;
	path.push_back(crawl);
	while (pred[crawl] != -1) {
		path.push_back(pred[crawl]);
		crawl = pred[crawl];
	}

	cout << "S最短路径长度为: "
		<< dist[dest];


	cout << "\n最短路径为:\n";
	for (int i = path.size() - 1; i >= 0; i--)
		cout << path[i] << " ";
	cout << endl;
}

int main()
{
	int v = 9;
	vector<int>* adj = new vector<int>[v];
	add_edge(adj, 2, 5);
	add_edge(adj, 5, 8);
	add_edge(adj, 8, 6);
	add_edge(adj, 6, 4);
	add_edge(adj, 5, 6);
	add_edge(adj, 2, 3);
	add_edge(adj, 3, 4);

	printShortestDistance(adj, 4,2 , v);

	return 0;
}