#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 20
#define QUEUE_SIZE 50

// Adjacency matrix representation of the graph
int adjMatrix[MAX_VERTICES][MAX_VERTICES];

// Visited array to keep track of visited nodes
bool visited[MAX_VERTICES];

// Queue for BFS
int queue[QUEUE_SIZE];
int front = 0, rear = -1;

// Function to add an element to the queue
void enqueue(int vertex) {
    if (rear == QUEUE_SIZE - 1) {
        printf("Queue is full\n");
        return;
    }
    queue[++rear] = vertex;
}

// Function to remove an element from the queue
int dequeue() {
    if (front > rear) {
        printf("Queue is empty\n");
        return -1;  // Indicates that the queue is empty
    }
    return queue[front++];
}

// Function to perform BFS traversal
void BFS(int startVertex, int vertices) {
    enqueue(startVertex);
    visited[startVertex] = true;

    printf("\nBFS Traversal Sequence: ");

    while (front <= rear) {  // Continue while the queue is not empty
        int vertex = dequeue();
        printf("%d ", vertex);

        // Check all the adjacent vertices of the dequeued vertex
        for (int i = 0; i < vertices; i++) {
            if (adjMatrix[vertex][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = true;
            }
        }
    }
}

// Function to display the adjacency matrix
void displayAdjMatrix(int vertices) {
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int vertices, edges, u, v;

    // Initialize the adjacency matrix and visited array
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            adjMatrix[i][j] = 0;
        }
        visited[i] = false;
    }

    // Accept number of vertices and edges
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    // Accept edges for the graph
    for (int i = 0; i < edges; i++) {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;  // Since the graph is undirected
    }

    // Display the adjacency matrix
    displayAdjMatrix(vertices);

    // Perform BFS traversal starting from vertex 0
    BFS(0, vertices);

    return 0;
}
