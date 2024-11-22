#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 20

// Structure for a node in the adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Array of adjacency list for graph
struct Node* adjList[MAX_VERTICES];

// Visited array to keep track of visited nodes
bool visited[MAX_VERTICES];

// Queue for BFS traversal
int queue[MAX_VERTICES];
int front = 0, rear = 0;  // Initialize front and rear indices to 0

// Function prototypes
void enqueue(int vertex);
int dequeue();
void addEdge(int u, int v);
void BFS(int startVertex, int vertices);
void displayAdjList(int vertices);
struct Node* createNode(int vertex);

int main() {
    int vertices, edges, u, v;

    // Initialize the adjacency list and visited array
    for (int i = 0; i < MAX_VERTICES; i++) {
        adjList[i] = NULL;
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
        addEdge(u, v);
    }

    // Display the adjacency list
    displayAdjList(vertices);

    // Perform BFS traversal starting from vertex 0
    BFS(0, vertices);

    return 0;
}

// Function to create a new adjacency list node
struct Node* createNode(int vertex) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to add an edge to the adjacency list
void addEdge(int u, int v) {
    struct Node* newNode = createNode(v);
    newNode->next = adjList[u];
    adjList[u] = newNode;
    
    // Since the graph is undirected, add the reverse edge
    newNode = createNode(u);
    newNode->next = adjList[v];
    adjList[v] = newNode;
}

// Function to perform BFS traversal
void BFS(int startVertex, int vertices) {
    visited[startVertex] = true;
    enqueue(startVertex);

    printf("\nBFS Traversal Sequence: ");

    while (front != rear) {  // While there are elements in the queue
        int currentVertex = dequeue();
        printf("%d ", currentVertex);

        // Traverse the adjacency list of the current vertex
        struct Node* temp = adjList[currentVertex];
        while (temp != NULL) {
            int adjacentVertex = temp->vertex;
            if (!visited[adjacentVertex]) {
                visited[adjacentVertex] = true;
                enqueue(adjacentVertex);
            }
            temp = temp->next;
        }
    }
}

// Function to enqueue a vertex into the queue
void enqueue(int vertex) {
    if (rear == MAX_VERTICES) {
        printf("Queue is full\n");
        return;
    }
    queue[rear++] = vertex;
}

// Function to dequeue a vertex from the queue
int dequeue() {
    if (front == rear) {
        printf("Queue is empty\n");
        return -1;  // Return -1 if the queue is empty
    }
    return queue[front++];  // Return the element and increment front
}

// Function to display the adjacency list
void displayAdjList(int vertices) {
    printf("\nAdjacency List:\n");
    for (int i = 0; i < vertices; i++) {
        printf("%d: ", i);
        struct Node* temp = adjList[i];
        while (temp != NULL) {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}
