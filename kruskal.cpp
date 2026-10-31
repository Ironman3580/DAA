#include <iostream>

using namespace std;

const int MAX = 100;

struct Edge {
    int u, v, weight;
};

void sortEdges(Edge edges[], int E) {
    for (int i = 0; i < E - 1; i++) {
        for (int j = 0; j < E - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

int findRoot(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = findRoot(parent, parent[i]);
}

void unionSets(int parent[], int rank[], int x, int y) {
    int rootX = findRoot(parent, x);
    int rootY = findRoot(parent, y);

    if (rootX != rootY) {
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int main() {
    int V = 4; 
    int E = 5; 

    Edge edges[MAX] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    sortEdges(edges, E);

    int parent[MAX];
    int rank[MAX];
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    cout << "--- Kruskal's Algorithm MST ---\n";
    int mstCost = 0;
    int edgeCount = 0;

    for (int i = 0; i < E && edgeCount < V - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;

        int rootU = findRoot(parent, u);
        int rootV = findRoot(parent, v);

    
        if (rootU != rootV) {
            cout << "Edge " << u << " - " << v << " : " << weight << "\n";
            mstCost += weight;
            unionSets(parent, rank, rootU, rootV);
            edgeCount++;
        }
    }
    cout << "Total Weight (Kruskal): " << mstCost << "\n";

    return 0;
}