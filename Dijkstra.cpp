#include <iostream>
using namespace std;

const int INF = 999999; 

struct Graph {
    int V;
    int** adj;
    int** weight; 
    int* size;
    int* capacity;

    Graph(int vertices) {
        V = vertices;
        adj = new int*[V];
        weight = new int*[V];
        size = new int[V]();
        capacity = new int[V];

        for (int i = 0; i < V; i++) {
            capacity[i] = 2; 
            adj[i] = new int[capacity[i]];
            weight[i] = new int[capacity[i]];
        }
    }

    ~Graph() {
        for (int i = 0; i < V; i++) {
            delete[] adj[i];
            delete[] weight[i];
        }
        delete[] adj;
        delete[] weight;
        delete[] size;
        delete[] capacity;
    }

    void addEdge(int u, int v, int w) {
        if (size[u] == capacity[u]) {
            capacity[u] *= 2;
            int* tempAdj = new int[capacity[u]];
            int* tempWt = new int[capacity[u]];
            for (int i = 0; i < size[u]; i++) {
                tempAdj[i] = adj[u][i];
                tempWt[i] = weight[u][i];
            }
            delete[] adj[u];
            delete[] weight[u];
            adj[u] = tempAdj;
            weight[u] = tempWt;
        }
        adj[u][size[u]] = v;
        weight[u][size[u]++] = w;

        if (size[v] == capacity[v]) {
            capacity[v] *= 2;
            int* tempAdj = new int[capacity[v]];
            int* tempWt = new int[capacity[v]];
            for (int i = 0; i < size[v]; i++) {
                tempAdj[i] = adj[v][i];
                tempWt[i] = weight[v][i];
            }
            delete[] adj[v];
            delete[] weight[v];
            adj[v] = tempAdj;
            weight[v] = tempWt;
        }
        adj[v][size[v]] = u;
        weight[v][size[v]++] = w;
    }
};


int* dijkstra(Graph& graph, int src, int& resSize) {
    int V = graph.V;
    int* dist = new int[V];
    bool* visited = new bool[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {

        int minDist = INF, u = -1;
        for (int i = 0; i < V; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1) break;

        visited[u] = true;

        for (int i = 0; i < graph.size[u]; i++) {
            int v = graph.adj[u][i];
            int w = graph.weight[u][i];

            if (!visited[v] && dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    resSize = V;
    delete[] visited;
    return dist;
}

int main() {
    int V = 5;
    Graph graph(V);
    
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 8);
    graph.addEdge(1, 4, 6);
    graph.addEdge(1, 2, 3);
    graph.addEdge(2, 3, 2);
    graph.addEdge(3, 4, 10);

    int resSize = 0;
    int* result = dijkstra(graph, 0, resSize);

    cout << "Shortest distances from source 0:\n";
    for (int i = 0; i < resSize; i++) {
        cout << result[i] << " ";
    }
    cout << "\n";

    delete[] result;
    return 0;
}