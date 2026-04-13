#include <iostream>
#include <vector>
#include <queue>

using namespace std;
 
class Graph {
    int V;
    vector<vector<int>> adj;
public:
    Graph(int v) : V(v), adj(v) {}
    void addEdge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }
 
    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);
        cout << "BFS: ";
        while (!q.empty()) {
            int u = q.front(); q.pop();
            cout << u << " ";
            for (int v : adj[u])
                if (!visited[v]) { visited[v]=true; q.push(v); }
        }
        cout << endl;
    }
 
    void DFSUtil(int u, vector<bool>& visited) {
        visited[u] = true;
        cout << u << " ";
        for (int v : adj[u])
            if (!visited[v]) DFSUtil(v, visited);
    }
    void DFS(int start) {
        vector<bool> visited(V, false);
        cout << "DFS: ";
        DFSUtil(start, visited);
        cout << endl;
    }
};
 
int main() {
    Graph g(6);
    g.addEdge(0,1); g.addEdge(0,2);
    g.addEdge(1,3); g.addEdge(1,4);
    g.addEdge(2,5);
    g.BFS(0);
    g.DFS(0);
    return 0;
}
