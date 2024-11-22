#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 20

int adjMatrix[MAX_VERTICES][MAX_VERTICES];
bool visited[MAX_VERTICES];
int vertices;

// Function to perform DFS traversal
void DFS(int v) {
    // Mark the node as visited
    visited[v] = true;
    printf("%d ", v);  // Print the visited node

    // Visit all the adjacent nodes of the current node
    for (int i = 0; i < vertices; i++) {
        if (adjMatrix[v][i] == 1 && !visited[i]) {
            DFS(i);
        }
    }
}

// Function to display the adjacency matrix
void displayAdjMatrix() {
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int edges, u, v;

    // Accept number of vertices and edges
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    // Initialize adjacency matrix and visited array
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            adjMatrix[i][j] = 0;
        }
        visited[i] = false;
    }

    // Accept edges for the graph
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; // For undirected graph
    }

    // Display the adjacency matrix
    displayAdjMatrix();

    // Perform DFS starting from the first vertex (0)
    printf("\nDFS Traversal Sequence: ");
    DFS(0);

    return 0;
}
