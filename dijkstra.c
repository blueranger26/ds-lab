#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 20

// Function prototypes
int minDistance(int dist[], int sptSet[], int vertices);
void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int vertices, int source);

int main() {
    int graph[MAX_VERTICES][MAX_VERTICES];
    int vertices, i, j;

    // Input the number of vertices
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    // Input the adjacency matrix (graph representation)
    printf("Enter the adjacency matrix (use 0 for no edge and non-zero for edge weight):\n");
    for (i = 0; i < vertices; i++) {
        for (j = 0; j < vertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Input the source vertex
    int source;
    printf("Enter the source vertex (0 to %d): ", vertices - 1);
    scanf("%d", &source);

    // Run Dijkstra's algorithm
    dijkstra(graph, vertices, source);

    return 0;
}

// Function to find the vertex with the minimum distance value, from the set of vertices not yet processed
int minDistance(int dist[], int sptSet[], int vertices) {
    int min = INT_MAX, minIndex;
    for (int v = 0; v < vertices; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Function to implement Dijkstra's algorithm
void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int vertices, int source) {
    int dist[MAX_VERTICES];   // Array to hold the shortest distance from source
    int sptSet[MAX_VERTICES]; // Shortest Path Tree set (to check if the vertex is processed)

    // Initialize the distance array and sptSet array
    for (int i = 0; i < vertices; i++) {
        dist[i] = INT_MAX;  // Set initial distances to infinity
        sptSet[i] = 0;      // Set all vertices as unprocessed
    }
    dist[source] = 0;  // Distance to the source vertex is 0

    // Find the shortest path for all vertices
    for (int count = 0; count < vertices - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, sptSet, vertices);

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update the dist[] value of the adjacent vertices of the picked vertex
        for (int v = 0; v < vertices; v++) {
            // Update dist[v] if the current vertex is not in the shortest path tree and there is an edge from u to v
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the constructed distance array
    printf("\nShortest distances from source vertex %d:\n", source);
    for (int i = 0; i < vertices; i++) {
        if (dist[i] == INT_MAX) {
            printf("Vertex %d: INF\n", i);
        } else {
            printf("Vertex %d: %d\n", i, dist[i]);
        }
    }
}
