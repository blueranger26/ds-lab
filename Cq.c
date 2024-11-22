#include <stdio.h>
#include <stdlib.h>

#define MAX 5 // Define maximum size of the queue

// Circular Queue structure
struct CircularQueue {
    int arr[MAX];
    int front, rear;
};

// Function to initialize the circular queue
void initQueue(struct CircularQueue *q) {
    q->front = q->rear = -1;
}

// Function to check if the queue is full
int isFull(struct CircularQueue *q) {
    return (q->rear + 1) % MAX == q->front;
}

// Function to check if the queue is empty
int isEmpty(struct CircularQueue *q) {
    return q->front == -1;
}

// Function to add an element to the queue (Addq)
void Addq(struct CircularQueue *q, int value) {
    if (isFull(q)) {
        printf("Queue is Full. Cannot add element.\n");
    } else {
        if (q->front == -1) {  // If queue is empty, set both front and rear to 0
            q->front = 0;
        }
        q->rear = (q->rear + 1) % MAX;  // Circular increment
        q->arr[q->rear] = value;
        printf("Added %d to the queue.\n", value);
    }
}

// Function to delete an element from the queue (Delq)
void Delq(struct CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is Empty. Cannot delete element.\n");
    } else {
        int deletedValue = q->arr[q->front];
        if (q->front == q->rear) {  // If there's only one element in the queue
            q->front = q->rear = -1;
        } else {
            q->front = (q->front + 1) % MAX;  // Circular increment
        }
        printf("Deleted %d from the queue.\n", deletedValue);
    }
}

// Function to display the entire queue
void displayQueue(struct CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is Empty.\n");
    } else {
        printf("Queue elements: ");
        int i = q->front;
        while (i != q->rear) {
            printf("%d ", q->arr[i]);
            i = (i + 1) % MAX;  // Circular increment
        }
        printf("%d\n", q->arr[q->rear]);  // Print the last element
    }
}

int main() {
    struct CircularQueue q;
    initQueue(&q);

    int choice, value;

    do {
        printf("\nCircular Queue Operations:\n");
        printf("1. Addq (Add element)\n");
        printf("2. Delq (Delete element)\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to add: ");
                scanf("%d", &value);
                Addq(&q, value);
                break;
            case 2:
                Delq(&q);
                break;
            case 3:
                displayQueue(&q);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
