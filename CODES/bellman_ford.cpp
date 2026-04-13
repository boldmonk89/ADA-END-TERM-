#include <iostream>
#include <vector>
#include <climits>
#include <string>

using namespace std;
 
struct Edge { int u, v, w; };
 
void bellmanFord(int V, int E, vector<Edge>& edges, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;
 
    // Relax all edges V-1 times
    for (int i = 1; i <= V-1; i++)
        for (auto& e : edges)
            if (dist[e.u] != INT_MAX && dist[e.u]+e.w < dist[e.v])
                dist[e.v] = dist[e.u] + e.w;
 
    // Check for negative weight cycle
    for (auto& e : edges)
        if (dist[e.u] != INT_MAX && dist[e.u]+e.w < dist[e.v]) {
            cout << "Negative weight cycle detected!" << endl;
            return;
        }
 
    cout << "Vertex  Distance from Source (" << src << ")" << endl;
    cout << string(35, '-') << endl;
    for (int i = 0; i < V; i++)
        cout << "  " << i << "       "
             << (dist[i]==INT_MAX ? "INF" : to_string(dist[i])) << endl;
}
 
int main() {
    int V=5, E=8;
    vector<Edge> edges = {
        {0,1,-1},{0,2,4},{1,2,3},{1,3,2},{1,4,2},
        {3,2,5},{3,1,1},{4,3,-3}
    };
    bellmanFord(V, E, edges, 0);
    return 0;
}
