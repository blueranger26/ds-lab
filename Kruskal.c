#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 20
#define INF 99999999  // A large number representing infinity

// Structure for a graph edge
struct Edge {
    int u, v, weight;
};

// Function prototypes
void kruskal(int graph[MAX_VERTICES][MAX_VERTICES], int vertices);
int find(int parent[], int i);
void union_sets(int parent[], int rank[], int x, int y);

int main() {
    int vertices, graph[MAX_VERTICES][MAX_VERTICES];
    
    // Input the number of vertices
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    // Input the adjacency matrix (weights of edges)
    printf("Enter the adjacency matrix (enter INF for no edge):\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == 0 && i != j) {
                graph[i][j] = INF;  // No edge
            }
        }
    }

    // Run Kruskal's algorithm to find the Minimum Spanning Tree
    kruskal(graph, vertices);

    return 0;
}

// Function to implement Kruskal's Algorithm
void kruskal(int graph[MAX_VERTICES][MAX_VERTICES], int vertices) {
    struct Edge edges[MAX_VERTICES * MAX_VERTICES];
    int edgeCount = 0;
    
    // Create an array of edges from the adjacency matrix
    for (int i = 0; i < vertices; i++) {
        for (int j = i + 1; j < vertices; j++) {
            if (graph[i][j] != INF) {
                edges[edgeCount].u = i;
                edges[edgeCount].v = j;
                edges[edgeCount].weight = graph[i][j];
                edgeCount++;
            }
        }
    }

    // Sort edges based on their weights
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                struct Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    // Initialize the disjoint-set (union-find) structures
    int parent[MAX_VERTICES], rank[MAX_VERTICES];
    for (int i = 0; i < vertices; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    printf("\nMinimum Spanning Tree (MST):\n");
    int mstWeight = 0;
    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        
        // Check if including this edge forms a cycle
        int setU = find(parent, u);
        int setV = find(parent, v);
        
        if (setU != setV) {
            printf("%d -- %d = %d\n", u, v, edges[i].weight);
            mstWeight += edges[i].weight;
            union_sets(parent, rank, setU, setV);
        }
    }

    printf("\nTotal weight of MST: %d\n", mstWeight);
}

// Function to find the representative of the set containing 'i'
int find(int parent[], int i) {
    if (parent[i] == i) {
        return i;
    }
    return find(parent, parent[i]);  // Path compression
}

// Function to perform union of two sets (union by rank)
void union_sets(int parent[], int rank[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);

    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}
