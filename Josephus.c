#include <stdio.h>
#include <stdlib.h>

// Define the structure for a queue
typedef struct Queue {
    int *arr;           // Array to store the elements (people)
    int front;          // Front index of the queue
    int rear;           // Rear index of the queue
    int size;           // Size of the queue
    int capacity;       // Maximum capacity of the queue
} Queue;

// Function to create a queue
Queue* createQueue(int capacity) {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->capacity = capacity;
    q->size = 0;
    q->front = 0;
    q->rear = capacity - 1;
    q->arr = (int*)malloc(capacity * sizeof(int));
    return q;
}

// Function to check if the queue is full
int isFull(Queue *q) {
    return (q->size == q->capacity);
}

// Function to check if the queue is empty
int isEmpty(Queue *q) {
    return (q->size == 0);
}

// Function to enqueue a person into the queue
void enqueue(Queue *q, int person) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return;
    }
    q->rear = (q->rear + 1) % q->capacity;
    q->arr[q->rear] = person;
    q->size++;
}

// Function to dequeue a person from the queue
int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    int person = q->arr[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return person;
}

// Function to solve the Josephus problem using a queue
int josephus(int n, int k) {
    // Create a queue and enqueue all people
    Queue *q = createQueue(n);
    for (int i = 1; i <= n; i++) {
        enqueue(q, i);
    }

    // Process the queue until only one person remains
    while (q->size > 1) {
        // Dequeue k-1 people (skip them)
        for (int i = 1; i < k; i++) {
            int person = dequeue(q);
            enqueue(q, person);  // Enqueue back to the queue
        }

        // Dequeue the k-th person (eliminate them)
        int eliminated = dequeue(q);
        printf("Person %d is eliminated\n", eliminated);
    }

    // The last remaining person is the winner
    int winner = dequeue(q);
    free(q->arr);
    free(q);
    return winner;
}

int main() {
    int n, k;

    // Read the number of people and step size
    printf("Enter the number of people (n): ");
    scanf("%d", &n);
    printf("Enter the step size (k): ");
    scanf("%d", &k);

    // Solve the Josephus problem and print the winner
    int winner = josephus(n, k);
    printf("\nThe last remaining person is: %d\n", winner);

    return 0;
}
