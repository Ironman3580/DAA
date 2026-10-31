//dfs
#include <iostream>
#include <stack>
using namespace std;

struct Graph {
    int V;
    int** adj;
    int* size;
    int* capacity;

    Graph(int vertices) {
        V = vertices;
        adj = new int*[V];
        size = new int[V]();
        capacity = new int[V];

        for (int i = 0; i < V; i++) {
            capacity[i] = 2; 
            adj[i] = new int[capacity[i]];
        }
    }

    ~Graph() {
        for (int i = 0; i < V; i++) {
            delete[] adj[i];
        }
        delete[] adj;
        delete[] size;
        delete[] capacity;
    }

    void addEdge(int u, int v) {
        if (size[u] == capacity[u]) {
            capacity[u] *= 2;
            int* temp = new int[capacity[u]];
            for (int i = 0; i < size[u]; i++) temp[i] = adj[u][i];
            delete[] adj[u];
            adj[u] = temp;
        }
        adj[u][size[u]++] = v;

        if (size[v] == capacity[v]) {
            capacity[v] *= 2;
            int* temp = new int[capacity[v]];
            for (int i = 0; i < size[v]; i++) temp[i] = adj[v][i];
            delete[] adj[v];
            adj[v] = temp;
        }
        adj[v][size[v]++] = u;
    }
};

// Iterative DFS helper for a connected component using std::stack
void dfsIterativeConnected(Graph& graph, int src, bool visited[], int res[], int& resSize) {
    stack<int> s;
    s.push(src);

    while (!s.empty()) {
        int curr = s.top();
        s.pop();

        if (!visited[curr]) {
            visited[curr] = true;
            res[resSize++] = curr;

 
            for (int i = graph.size[curr] - 1; i >= 0; i--) {
                int neighbor = graph.adj[curr][i];
                if (!visited[neighbor]) {
                    s.push(neighbor);
                }
            }
        }
    }
}


int* dfsIterative(Graph& graph, int& resSize) {
    int V = graph.V;
    bool* visited = new bool[V]();
    int* res = new int[V];
    resSize = 0;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfsIterativeConnected(graph, i, visited, res, resSize);
        }
    }

    delete[] visited;
    return res;
}

int main() {
    int V = 6;
    Graph graph(V);
    
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(0, 3);
    graph.addEdge(4, 5);

    int resSize = 0;
    int* res = dfsIterative(graph, resSize);

    cout << "Iterative DFS traversal result: ";
    for (int i = 0; i < resSize; i++) {
        cout << res[i] << " ";
    }
    cout << "\n";

    delete[] res;
    return 0;
}