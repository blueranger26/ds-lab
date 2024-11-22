#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 20

// Structure for adjacency list node
struct Node {
    int vertex;
    struct Node* next;
};

// Adjacency list array
struct Node* adjList[MAX_VERTICES];

// Visited array to keep track of visited nodes
int visited[MAX_VERTICES];

// Function to create a new adjacency list node
struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to add an edge in the graph (undirected)
void addEdge(int u, int v) {
    // Add edge from u to v
    struct Node* newNode = createNode(v);
    newNode->next = adjList[u];
    adjList[u] = newNode;
    
    // Add edge from v to u (since the graph is undirected)
    newNode = createNode(u);
    newNode->next = adjList[v];
    adjList[v] = newNode;
}

// Function to perform DFS traversal
void DFS(int v) {
    // Mark the node as visited
    visited[v] = 1;
    printf("%d ", v);  // Print the visited node
    
    // Recur for all the adjacent nodes of the current node
    struct Node* temp = adjList[v];
    while (temp != NULL) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            DFS(adjVertex);
        }
        temp = temp->next;
    }
}

// Function to display the adjacency list
void displayAdjList(int vertices) {
    printf("\nAdjacency List:\n");
    for (int i = 0; i < vertices; i++) {
        printf("%d: ", i);
        struct Node* temp = adjList[i];
        while (temp != NULL) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int vertices, edges, u, v;
    
    // Initialize adjacency list and visited array
    for (int i = 0; i < MAX_VERTICES; i++) {
        adjList[i] = NULL;
        visited[i] = 0;
    }

    // Accept number of vertices and edges
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    // Accept the number of edges
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    // Accept edges for the graph
    for (int i = 0; i < edges; i++) {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    // Display the adjacency list
    displayAdjList(vertices);

    // Perform DFS traversal starting from vertex 0
    printf("\nDFS Traversal Sequence: ");
    DFS(0);

    return 0;
}
