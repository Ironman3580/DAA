#include <iostream>
using namespace std;
const int MAX = 100;

int minKey(int key[], bool mstSet[], int V) {
    int min = 999999, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

int main() {
    int V = 4; 

    int graph[MAX][MAX] = {
        {0, 10, 6, 5},
        {10, 0, 0, 15},
        {6, 0, 0, 4},
        {5, 15, 4, 0}
    };

    int parent[MAX];
    int key[MAX];
    bool mstSet[MAX];

    for (int i = 0; i < V; i++) {
        key[i] = 999999;
        mstSet[i] = false;
    }

    key[0] = 0; 
    parent[0] = -1; 

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);
        mstSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    cout << "--- Prim's Algorithm MST ---\n";
    int mstCost = 0;
    for (int i = 1; i < V; i++) {
        cout << "Edge " << parent[i] << " - " << i << " : " << graph[i][parent[i]] << "\n";
        mstCost += graph[i][parent[i]];
    }
    cout << "Total Weight (Prim): " << mstCost << "\n";

    return 0;
}