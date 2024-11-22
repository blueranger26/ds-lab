#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a passenger
typedef struct Passenger {
    int passengerID;  // Unique ID for each passenger
    char name[50];    // Name of the passenger
} Passenger;

// Define the structure for the queue (linear queue)
typedef struct Queue {
    Passenger *passengers;  // Array to hold the passengers
    int front;              // Index for the front of the queue
    int rear;               // Index for the rear of the queue
    int size;               // Current number of passengers in the queue
    int capacity;           // Maximum capacity of the queue
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

// Function to enqueue a new passenger
void enqueue(Queue *q, Passenger p) {
    if (isFull(q)) {
        printf("Queue is full. Cannot add more passengers.\n");
        return;
    }

    q->rear = (q->rear + 1) % q->capacity;
    q->passengers[q->rear] = p;
    q->size++;
}

// Function to dequeue a passenger (issue ticket and remove from the queue)
Passenger dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty. No passengers to issue tickets to.\n");
        Passenger emptyPassenger = {0, ""};  // Return empty passenger if queue is empty
        return emptyPassenger;
    }

    Passenger p = q->passengers[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return p;
}

// Function to display the passenger at the front of the queue
void displayFront(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty. No passengers in the queue.\n");
    } else {
        printf("Passenger at the front: %d, %s\n", q->passengers[q->front].passengerID, q->passengers[q->front].name);
    }
}

// Function to display the number of passengers left in the queue
void displaySize(Queue *q) {
    printf("Number of passengers left in the queue: %d\n", q->size);
}

// Function to display the entire queue (optional)
void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    
    printf("\nCurrent passengers in the queue:\n");
    int i = q->front;
    while (i != q->rear) {
        printf("Passenger ID: %d, Name: %s\n", q->passengers[i].passengerID, q->passengers[i].name);
        i = (i + 1) % q->capacity;
    }
    printf("Passenger ID: %d, Name: %s\n", q->passengers[q->rear].passengerID, q->passengers[q->rear].name);
}

// Main function
int main() {
    int capacity = 5;  // Set a maximum queue capacity of 5 passengers
    Queue *q = createQueue(capacity);
    int choice;
    Passenger p;
    
    do {
        // Menu for the user to choose actions
        printf("\nTicket Agent Queue System:\n");
        printf("1. Insert a new passenger\n");
        printf("2. Display the passenger at the front\n");
        printf("3. Issue ticket and remove passenger from the front\n");
        printf("4. Display number of passengers left in the queue\n");
        printf("5. Display all passengers in the queue\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Insert a new passenger
                if (isFull(q)) {
                    printf("Queue is full, cannot add more passengers.\n");
                } else {
                    printf("Enter Passenger ID: ");
                    scanf("%d", &p.passengerID);
                    printf("Enter Passenger Name: ");
                    getchar();  // Consume the newline character left by scanf
                    fgets(p.name, 50, stdin);
                    p.name[strcspn(p.name, "\n")] = 0;  // Remove the newline character from the input
                    enqueue(q, p);
                    printf("Passenger added successfully.\n");
                }
                break;
            case 2:
                // Display the passenger at the front
                displayFront(q);
                break;
            case 3:
                // Issue ticket and remove passenger from the front
                p = dequeue(q);
                if (p.passengerID != 0) {
                    printf("Ticket issued to Passenger ID: %d, Name: %s\n", p.passengerID, p.name);
                }
                break;
            case 4:
                // Display the number of passengers left in the queue
                displaySize(q);
                break;
            case 5:
                // Display all passengers in the queue
                displayQueue(q);
                break;
            case 6:
                // Exit
                printf("Exiting the system...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    // Free memory
    free(q->passengers);
    free(q);
    
    return 0;
}
