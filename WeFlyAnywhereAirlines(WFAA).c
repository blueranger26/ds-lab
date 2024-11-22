#include <stdio.h>
#include <stdlib.h>

// Define the structure for a passenger
typedef struct Passenger {
    int id;
    int arrivalTime;  // Time when the passenger arrived in the queue
    int waitTime;     // Time spent waiting in the queue
} Passenger;

// Define the structure for the queue (circular queue)
typedef struct Queue {
    Passenger *passengers;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

// Function to create a queue
Queue* createQueue(int capacity) {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->capacity = capacity;
    q->size = 0;
    q->front = 0;
    q->rear = capacity - 1;
    q->passengers = (Passenger*)malloc(capacity * sizeof(Passenger));
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

// Function to enqueue a passenger
void enqueue(Queue *q, Passenger p) {
    if (isFull(q)) {
        printf("Queue is full. Cannot add more passengers.\n");
        return;
    }

    q->rear = (q->rear + 1) % q->capacity;
    q->passengers[q->rear] = p;
    q->size++;
}

// Function to dequeue a passenger
Passenger dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty. No passengers to serve.\n");
        Passenger emptyPassenger = {0, 0, 0};
        return emptyPassenger;
    }

    Passenger p = q->passengers[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return p;
}

// Function to calculate the average waiting time
double calculateAverageWaitTime(Queue *q) {
    if (isEmpty(q)) {
        return 0.0;
    }

    int totalWaitTime = 0;
    int count = q->size;
    int currentTime = 0;  // Start at time 0

    // Traverse through the queue and calculate wait time for each passenger
    for (int i = 0; i < count; i++) {
        Passenger p = dequeue(q);  // Get the passenger
        // Update current time as passengers are served
        currentTime = currentTime > p.arrivalTime ? currentTime : p.arrivalTime; 
        p.waitTime = currentTime - p.arrivalTime;
        totalWaitTime += p.waitTime;  // Accumulate the wait time
    }

    return (double)totalWaitTime / count;
}

// Function to display passengers in the queue (for debugging)
void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }

    int i = q->front;
    while (i != q->rear) {
        printf("Passenger ID: %d, Arrival Time: %d, Wait Time: %d\n", q->passengers[i].id, q->passengers[i].arrivalTime, q->passengers[i].waitTime);
        i = (i + 1) % q->capacity;
    }
    printf("Passenger ID: %d, Arrival Time: %d, Wait Time: %d\n", q->passengers[q->rear].id, q->passengers[q->rear].arrivalTime, q->passengers[q->rear].waitTime);
}

// Main function
int main() {
    int regularCapacity = 5;
    int frequentFlyerCapacity = 5;

    // Create two queues: one for regular customers and one for frequent flyers
    Queue *regularQueue = createQueue(regularCapacity);
    Queue *frequentFlyerQueue = createQueue(frequentFlyerCapacity);

    int choice;
    Passenger p;
    int passengerID = 1;

    // Simulation loop
    do {
        printf("\nTicket Counter Simulation:\n");
        printf("1. Add Regular Customer\n");
        printf("2. Add Frequent Flyer\n");
        printf("3. Serve Regular Customer\n");
        printf("4. Serve Frequent Flyer\n");
        printf("5. Calculate Average Wait Time\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Add a regular customer
                if (isFull(regularQueue)) {
                    printf("Regular customer queue is full.\n");
                } else {
                    p.id = passengerID++;
                    printf("Enter Arrival Time for Regular Customer: ");
                    scanf("%d", &p.arrivalTime);
                    enqueue(regularQueue, p);
                    printf("Regular Customer added.\n");
                }
                break;

            case 2:
                // Add a frequent flyer
                if (isFull(frequentFlyerQueue)) {
                    printf("Frequent flyer queue is full.\n");
                } else {
                    p.id = passengerID++;
                    printf("Enter Arrival Time for Frequent Flyer: ");
                    scanf("%d", &p.arrivalTime);
                    enqueue(frequentFlyerQueue, p);
                    printf("Frequent Flyer added.\n");
                }
                break;

            case 3:
                // Serve a regular customer
                if (isEmpty(regularQueue)) {
                    printf("No regular customers in the queue.\n");
                } else {
                    p = dequeue(regularQueue);
                    printf("Served Regular Customer ID: %d, Arrival Time: %d\n", p.id, p.arrivalTime);
                }
                break;

            case 4:
                // Serve a frequent flyer
                if (isEmpty(frequentFlyerQueue)) {
                    printf("No frequent flyers in the queue.\n");
                } else {
                    p = dequeue(frequentFlyerQueue);
                    printf("Served Frequent Flyer ID: %d, Arrival Time: %d\n", p.id, p.arrivalTime);
                }
                break;

            case 5:
                // Calculate and display average waiting time for both queues
                printf("\nAverage Wait Time for Regular Customers: %.2f\n", calculateAverageWaitTime(regularQueue));
                printf("Average Wait Time for Frequent Flyers: %.2f\n", calculateAverageWaitTime(frequentFlyerQueue));
                break;

            case 6:
                // Exit the simulation
                printf("Exiting the system...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    // Free memory
    free(regularQueue->passengers);
    free(regularQueue);
    free(frequentFlyerQueue->passengers);
    free(frequentFlyerQueue);

    return 0;
}
