#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIMULATION_TIME 120  // Total simulation time in minutes
#define REQUEST_INTERVAL 5    // Time interval for requests in minutes
#define LANDING_TIME 15       // Time taken for landing in minutes
#define TAKEOFF_TIME 15       // Time taken for takeoff in minutes
#define MAX_QUEUE_SIZE 100    // Maximum size for landing and takeoff queues

typedef struct {
    int queue[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

// Function to initialize a queue
void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

// Function to check if the queue is full
int isFull(Queue* q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

// Function to check if the queue is empty
int isEmpty(Queue* q) {
    return q->front == -1;
}

// Function to enqueue an element
void enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = value;
}

// Function to dequeue an element
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        return -1; // Queue is empty
    }
    int value = q->queue[q->front];
    if (q->front == q->rear) {
        // Queue has only one element
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    }
    return value;
}

// Function to get the number of elements in the queue
int queueSize(Queue* q) {
    if (isEmpty(q)) {
        return 0;
    }
    return (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE + 1;
}

// Main simulation function
int main() {
    Queue landingQueue, takeoffQueue;
    initQueue(&landingQueue);
    initQueue(&takeoffQueue);

    int landingCompleted = 0;
    int takeoffCompleted = 0;
    int runwayBusyUntil[2] = {0, 0}; // Tracks when each runway will be free
    int currentTime = 0;

    srand(time(NULL)); // Seed for random number generation

    // Run the simulation for the specified time
    while (currentTime < SIMULATION_TIME) {
        // Randomly generate a landing or takeoff request
        if (rand() % 2 == 0) {
            enqueue(&landingQueue, currentTime); // 50% chance for landing
        } else {
            enqueue(&takeoffQueue, currentTime); // 50% chance for takeoff
        }

        // Process runways
        for (int i = 0; i < 2; i++) {
            if (runwayBusyUntil[i] <= currentTime) {
                if (!isEmpty(&landingQueue)) {
                    dequeue(&landingQueue);
                    runwayBusyUntil[i] = currentTime + LANDING_TIME;
                    landingCompleted++;
                } else if (!isEmpty(&takeoffQueue)) {
                    dequeue(&takeoffQueue);
                    runwayBusyUntil[i] = currentTime + TAKEOFF_TIME;
                    takeoffCompleted++;
                }
            }
        }

        currentTime += REQUEST_INTERVAL; // Move to the next time interval
    }

    // Calculate average wait times
    int totalLandingWait = 0;
    int totalTakeoffWait = 0;

    while (!isEmpty(&landingQueue)) {
        totalLandingWait += currentTime - dequeue(&landingQueue);
    }

    while (!isEmpty(&takeoffQueue)) {
        totalTakeoffWait += currentTime - dequeue(&takeoffQueue);
    }

    double avgLandingWait = landingCompleted > 0 ? (double)totalLandingWait / landingCompleted : 0;
    double avgTakeoffWait = takeoffCompleted > 0 ? (double)totalTakeoffWait / takeoffCompleted : 0;

    // Output results
    printf("Number of Landings Completed: %d\n", landingCompleted);
    printf("Number of Takeoffs Completed: %d\n", takeoffCompleted);
    printf("Average Minutes in Landing Queue : %.2f\n", avgLandingWait);
    printf("Average Minutes in Takeoff Queue: %.2f\n", avgTakeoffWait);

    return 0;
}