#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>  // Add this to enable 'bool'

#define MAX_VERTICES 20

// Structure for an edge in the adjacency list
struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

// Function prototypes
void addEdge(struct Node* adjList[], int u, int v, int weight);
void primMST(struct Node* adjList[], int vertices);
void displayAdjList(struct Node* adjList[], int vertices);
int minKey(int key[], bool mstSet[], int vertices);

int main() {
    int vertices, edges, u, v, weight;
    struct Node* adjList[MAX_VERTICES];
    
    // Initialize adjacency list
    for (int i = 0; i < MAX_VERTICES; i++) {
        adjList[i] = NULL;
    }

    // Input the number of vertices and edges
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    // Input edges and weights
    for (int i = 0; i < edges; i++) {
        printf("Enter edge (u v weight): ");
        scanf("%d %d %d", &u, &v, &weight);
        addEdge(adjList, u, v, weight);
    }

    // Display adjacency list
    displayAdjList(adjList, vertices);

    // Perform Prim's Algorithm to find MST
    primMST(adjList, vertices);

    return 0;
}

// Function to add an edge to the adjacency list
void addEdge(struct Node* adjList[], int u, int v, int weight) {
    // Add edge u-v
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = adjList[u];
    adjList[u] = newNode;

    // Add edge v-u (since the graph is undirected)
    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = u;
    newNode->weight = weight;
    newNode->next = adjList[v];
    adjList[v] = newNode;
}

// Function to display the adjacency list
void displayAdjList(struct Node* adjList[], int vertices) {
    printf("\nAdjacency List:\n");
    for (int i = 0; i < vertices; i++) {
        printf("%d: ", i);
        struct Node* temp = adjList[i];
        while (temp != NULL) {
            printf("(%d, %d) ", temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Function to implement Prim's algorithm for MST
void primMST(struct Node* adjList[], int vertices) {
    int parent[MAX_VERTICES];  // Array to store the MST
    int key[MAX_VERTICES];     // Key values to pick the minimum weight edge
    bool mstSet[MAX_VERTICES]; // To represent the vertices included in MST

    // Initialize key values to infinity and mstSet[] to false
    for (int i = 0; i < vertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    // Start from vertex 0
    key[0] = 0;
    parent[0] = -1;  // No parent for the first vertex

    // Iterate over all vertices
    for (int count = 0; count < vertices - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, mstSet, vertices);

        // Include vertex u in MST
        mstSet[u] = 1;

        // Update the key and parent values of the adjacent vertices
        struct Node* temp = adjList[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;

            // If v is not in MST and weight of (u, v) is smaller than the current key[v], update key[v]
            if (mstSet[v] == 0 && key[v] > weight) {
                key[v] = weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }

    // Print the constructed MST
    printf("\nMinimum Spanning Tree (MST):\n");
    int mstWeight = 0;
    for (int i = 1; i < vertices; i++) {
        printf("%d -- %d = %d\n", parent[i], i, key[i]);
        mstWeight += key[i];
    }
    printf("\nTotal weight of MST: %d\n", mstWeight);
}

// Function to find the vertex with the minimum key value
int minKey(int key[], bool mstSet[], int vertices) {
    int min = INT_MAX, minIndex;

    for (int v = 0; v < vertices; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}
